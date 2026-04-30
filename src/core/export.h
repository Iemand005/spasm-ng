#ifndef __EXPORT_H
#define __EXPORT_H

#include "export.h"
#include "spasm.h"
#include "utils.h"
#include "errors.h"

void write_file(const unsigned char *output_contents, int output_len, const char *output_filename);
int findfield( unsigned char byte, const unsigned char* buffer );
int findfield_flex( unsigned char prefix_byte, const unsigned char* buffer, int *buf_field_loc, int *buf_field_size );
int siggen (const unsigned char* hashbuf, unsigned char* sigbuf, int* outf);
void intelhex(FILE * outfile , const unsigned char* buffer, int size, unsigned int address = 0x4000);
void alphanumeric (char* namestring, bool allow_lower);

void make83 (const unsigned char *output_contents, int size, FILE *outfile, const char *prgmname);

#endif