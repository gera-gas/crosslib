#ifndef STRING_H_
#define STRING_H_
/**
 *  @file    string.h
 *  @brief   Header file with string prototypes.
 *  @author  Gerasimov A.S.
 *  @date    2013-03-12 23:44:35 +0400
 */
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t strlen   ( const char * );
   int strcmp   ( const char *, const char * );
   int strncmp  ( const char *, const char *, size_t );
 char* strchr   ( const char *, int );
 char* strrchr  ( const char *, int );
size_t strnumc  ( const char *, char );
 char* strrepc  ( char *, char, char );
 char* strcpy   ( char *, const char * );
 char* strncpy  ( char *, const char *, size_t );
 char* strcat   ( char *, const char * );
 char* strncat  ( char *, const char *, size_t );
size_t strcspn  ( const char *, const char * );
size_t strspn   ( const char *, const char * );
 char* strrev   ( char * );
 char* strpbrk  ( const char *, const char * );
 char* strstr   ( const char *, const char * );
 char* strnset  ( char *, char, size_t );

 size_t  wcslen   ( const wchar_t * );
    int  wcscmp   ( const wchar_t *, const wchar_t * );
    int  wcsncmp  ( const wchar_t *, const wchar_t *, size_t );
wchar_t* wcschr   ( const wchar_t *, wchar_t );
wchar_t* wcsrchr  ( const wchar_t *, wchar_t );
 size_t  wcsnumc  ( const wchar_t *, wchar_t );
wchar_t* wcsrepc  ( wchar_t *, wchar_t, wchar_t );
wchar_t* wcscpy   ( wchar_t *, const wchar_t * );
wchar_t* wcsncpy  ( wchar_t *, const wchar_t *, size_t );
wchar_t* wcscat   ( wchar_t *, const wchar_t * );
wchar_t* wcsncat  ( wchar_t *, const wchar_t *, size_t );
 size_t  wcscspn  ( const wchar_t *, const wchar_t * );
 size_t  wcsspn   ( const wchar_t *, const wchar_t * );
wchar_t* wcsrev   ( wchar_t * );
wchar_t* wcspbrk  ( const wchar_t *, const wchar_t * );
wchar_t* wcsstr   ( const wchar_t *, const wchar_t * );
wchar_t* wcsnset  ( wchar_t *, wchar_t, size_t );

#ifdef __cplusplus
}
#endif

#endif  /*  STRING_H_  */ 
