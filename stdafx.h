#pragma once

#ifndef _STDAFX_H
#define _STDAFX_H

#undef WIN32

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <strings.h>
// #include <assert.h>
// #include <unistd.h>
// #include <ctype.h>
// #include <stdarg.h>
#ifndef NO_APPSIGN
#include <gmp.h>
#include <openssl/md5.h>
#endif /* NO_APPSIGN */
// #include <math.h>
// #include <errno.h>
// #include <stdbool.h>
// #include <sys/timeb.h>

// #include <stdint.h>

#define __inout

#define MAX_PATH 256
#define STDMETHODIMP HRESULT

#ifdef _MSC_VER
    #define PACKED_STRUCT
    #pragma pack(push, 1)
#else
    #define PACKED_STRUCT __attribute__((packed))
#endif

#ifdef _WIN32
    #include <tchar.h>
    #include <string.h>
    #define strcasecmp _stricmp
    #define strncasecmp _strnicmp
#else
    #include <strings.h>
    typedef const char *TCHAR *;
    typedef char TCHAR;
    typedef char *LPSTR, *LPTSTR;
#endif

#ifdef UNIXVER
typedef unsigned int DWORD;
#else
// #include <windows.h>
#endif

typedef void *LPVOID;
typedef uint32_t DWORD;

#define _T(z) z

#define _stricmp strcasecmp
#define _tcsdup strdup
#define _strdup strdup
#define sprintf_s sprintf
#define _strtoi64 strtoll

#define StringCchPrintf(dest, size, fmt, ...) snprintf(dest, size, fmt, __VA_ARGS__)
#define StringCchVPrintf(dest, size, fmt, args) vsnprintf(dest, size, fmt, args)

#ifdef UNIXVER
#define ARRAYSIZE(z) (sizeof(z)/sizeof((z)[0]))
#endif

#endif

#ifdef _WIN32
// #include <stdio.h>
// #include <stdlib.h>

int strcasecmp(const char *s1, const char *s2) {
    // fprintf(stderr, "FATAL ERROR: strcasecmp needs to be replaced!\n");
    // abort(); 
    return 0;
}
#endif