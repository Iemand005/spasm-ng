
#define WIN32

#ifdef WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

void get_cwd(char *buffer, int size) {
#ifdef WIN32
		_getcwd(buffer, size);
#else
		getcwd(buffer, size);
#endif
}