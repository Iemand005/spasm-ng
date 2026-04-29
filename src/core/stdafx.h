#pragma once

#ifndef _STDAFX_H
#define _STDAFX_H

#undef WIN32

#include <stdio.h>
#include <stdarg.h>
#include <string>

#ifndef NO_APPSIGN
#include <gmp.h>
// #include <openssl/md5.h> TODO: Replace OpenSSL with way smaller library why'd you do entire openssl over one md5 func
#endif /* NO_APPSIGN */


#include <stdint.h>

#define __inout

#define MAX_PATH 256
#define HRESULT int
#define STDMETHODIMP HRESULT
#define S_OK 0
#define LONG long
typedef char* LPSTR;
typedef uint32_t DWORD;



#ifdef _WIN32
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// int isxdigit(int c);
// int isalnum(int c);
// TODO: dont do this inline shi
static inline char* strndup(const char* s, size_t n) {
    if (s == NULL) return NULL;

    size_t len = strnlen(s, n);
    
    char* new_str = (char*)malloc(len + 1);
    if (new_str == NULL) return NULL;

    memcpy(new_str, s, len);
    new_str[len] = '\0';

    return new_str;
}
#endif

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

// typedef TCHAR* LPTSTR;
typedef char *LPSTR, *LPTSTR;


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

// #ifdef UNIXVER
#define ARRAYSIZE(z) (sizeof(z)/sizeof((z)[0]))
// #endif

#ifdef _WIN32
#include <string.h>
#include <ctype.h>

inline int strcasecmp(const char *s1, const char *s2) {
    return _stricmp(s1, s2);
}

inline int strncasecmp(const char *s1, const char *s2, size_t n) {
    return _strnicmp(s1, s2, n);
}
#else
#include <strings.h>
#endif

#endif
