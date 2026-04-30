#ifndef __LIBSPASM_H
#define __LIBSPASM_H

#include "pass_one.h"
#include "pass_two.h"
#include "opcodes.h"
#include "storage.h"
#include "spasm.h"
#include "utils.h"
#include "console.h"
#include "errors.h"
#include "export.h"

#include "filesystem.h"

#define LISTING_BUF_SIZE 65536	//initial size of buffer for output listing


int assemble()
{
	exit_code = EXIT_NORMAL;
	
	/*extern int generic_map[256];
	ZeroMemory(generic_map, 256);*/
	program_counter = 0x0000;
	stats_codesize = stats_datasize = stats_mintime = stats_maxtime = 0;
	last_label = NULL;
	error_occurred = false;
	listing_offset = 0;
	listing_for_line_done = false;
	line_start = NULL;
	old_line_num = 0;
	in_macro = 0;
	line_num = 0;
#ifdef USE_BUILTIN_FCREATE
	cur_buf = 0;
#endif
#ifdef USE_REUSABLES
	curr_reusable = 0;
	total_reusables = 0;
#endif
	
	// assert(curr_input_file != NULL); TODO: aaegh

	//read in the input file
	if (!(mode & MODE_COMMANDLINE))
		input_contents = (char *)get_file_contents(curr_input_file);

	if (!input_contents) {
		puts("Couldn't open input file");
		return EXIT_FATAL_ERROR;
	}
	
	out_ptr = output_contents;

	//along with the listing buffer, if required
	if ((mode & MODE_LIST)) {
		listing_buf = eb_init(LISTING_BUF_SIZE);
		listing_offset = 0;
		listing_on = true;
	}
	
	//find the path of the input file
	if (is_abs_path(curr_input_file)) {
		int i;

		strcpy(temp_path, curr_input_file);
	
		for (i = strlen(temp_path) - 1; 
			temp_path[i] != '\\' && temp_path[i] != '/' && i > 0; i--);
		if (i >= 0)
			temp_path[i] = '\0';
		else
			strcpy(temp_path, ".");
	} else {
    get_cwd(temp_path, sizeof(temp_path));
	}

	//add the the input file's path to the include directories
	include_dirs = list_prepend (include_dirs, strdup (temp_path));

	printf ("Pass one... \n");

	int first_pass_session = StartSPASMErrorSession();
	run_first_pass ((char *) input_contents);
	ReplayFatalSPASMErrorSession(first_pass_session);
	EndSPASMErrorSession(first_pass_session);
	
	
	//free include dirs when done
	if ((mode & MODE_COMMANDLINE) == 0)
	{
		release_file_contents(input_contents);
		input_contents = NULL;
	}
	
	list_free (include_dirs, true, NULL);
	include_dirs = NULL;
	
	//...and if there's output, run the second pass and write it to the output file
	if (mode & MODE_SYMTABLE || mode & MODE_NORMAL || mode & MODE_LIST)
	{
		printf ("Pass two... \n");
		int second_pass_session = StartSPASMErrorSession();
		run_second_pass ();
		ReplaySPASMErrorSession(second_pass_session);
		EndSPASMErrorSession(second_pass_session);

		if (mode & MODE_SYMTABLE) {
			int symtable_session = StartSPASMErrorSession();
			char* fileName = change_extension(output_filename, "lab");
			write_labels (fileName);
			free(fileName);
			ReplayFatalSPASMErrorSession(symtable_session);
			EndSPASMErrorSession(symtable_session);
		}
		
		//run the output through the appropriate program export and write it to a file
		if (mode & MODE_NORMAL && output_filename != NULL)
		{
			int write_session = StartSPASMErrorSession();
			write_file (output_contents, out_ptr - output_contents, output_filename);
			ReplayFatalSPASMErrorSession(write_session);
			EndSPASMErrorSession(write_session);
		}

		//write the listing file if necessary
		if ((mode & MODE_LIST)) {
			FILE *file;
			char *name;

			//get file name
			name = change_extension (output_filename, "lst");
			file = fopen (name, "wb");
			if (!file) {
				printf ("Couldn't open listing file '%s'", name);
				free (name);
				return EXIT_FATAL_ERROR;
			}
			free (name);
			
			if (fwrite (listing_buf->start, 1, listing_offset, file) != listing_offset) {
				puts ("Error writing to listing file");
				fclose (file);
				return EXIT_FATAL_ERROR;
			}

			fclose (file);
			eb_free(listing_buf);
			listing_buf = NULL;
		}
		
		//free the output buffer and all the names of input files
		list_free(input_files, true, NULL);
		input_files = NULL;
	}

	//if there's info to be dumped, do that
	if (mode & MODE_CODE_COUNTER) {
		fprintf (stdout, "Size: %u\nMin. execution time: %u\nMax. execution time: %u\n",
				 stats_codesize, stats_mintime, stats_maxtime);
	}
	
	if (mode & MODE_STATS) {
		fprintf(stdout, "Number of labels: %u\nNumber of defines: %u\nCode size: %u\nData size: %u\nTotal size: %u\n",
				 get_num_labels (), get_num_defines (), stats_codesize, stats_datasize, stats_codesize + stats_datasize);
	}

	return exit_code;
}

#endif