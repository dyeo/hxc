#ifndef __HXC_XLOG_H__
#define __HXC_XLOG_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#ifndef XLOG_LEVEL
#   define XLOG_LEVEL 6
#endif

#define _STR(s) #s
#define _FMTTRACE(file, line) file ":" _STR(line)

#ifndef XLOG_TIME_FORMAT
#   define XLOG_TIME_FORMAT "%H:%M:%S "
#endif

#ifdef XLOG_NO_COLOR
#   define _XLOG_COLOR5 ""
#   define _XLOG_COLOR4 ""
#   define _XLOG_COLOR3 ""
#   define _XLOG_COLOR2 ""
#   define _XLOG_COLOR1 ""
#   define _XLOG_COLOR0 ""
#   define _XLOG_COLORE ""
#else
#   define _XLOG_COLOR5 "\x1B[40;37m"
#   define _XLOG_COLOR4 "\x1B[40;36m"
#   define _XLOG_COLOR3 "\x1B[36;32m"
#   define _XLOG_COLOR2 "\x1B[40;33m"
#   define _XLOG_COLOR1 "\x1B[40;31m"
#   define _XLOG_COLOR0 "\x1B[41;01m"
#   define _XLOG_COLORE "\x1B[40;37m"
#endif

#ifndef XLOG_PREFIX5
#define XLOG_PREFIX5 "[  DEBUG] "
#endif
#ifndef XLOG_PREFIX4
#define XLOG_PREFIX4 "[   INFO] "
#endif
#ifndef XLOG_PREFIX3
#define XLOG_PREFIX3 "[ NOTICE] "
#endif
#ifndef XLOG_PREFIX2
#define XLOG_PREFIX2 "[WARNING] "
#endif
#ifndef XLOG_PREFIX1
#define XLOG_PREFIX1 "[  ERROR] "
#endif
#ifndef XLOG_PREFIX0
#define XLOG_PREFIX0 "[  FATAL] "
#endif

#if !defined(_NDEBUG) && XLOG_LEVEL >= 5
#   define debug(...) _xlog(stdout, _XLOG_COLOR5, XLOG_PREFIX5, _XLOG_COLORE "\n", __VA_ARGS__, 0)
#else
#   define debug(...) ((void)(0))
#endif

#if XLOG_LEVEL >= 4
#   define info(...) _xlog(stdout, _XLOG_COLOR4, XLOG_PREFIX4, _XLOG_COLORE "\n", __VA_ARGS__, 0)
#else 
#   define info(...) ((void)(0))
#endif

#if XLOG_LEVEL >= 3
#   define notice(...) _xlog(stdout, _XLOG_COLOR3, XLOG_PREFIX3, _XLOG_COLORE "\n", __VA_ARGS__, 0)
#else 
#   define notice(...) ((void)(0))
#endif

#if XLOG_LEVEL >= 2
#   define warning(...) _xlog(stderr, _XLOG_COLOR2, XLOG_PREFIX2, _XLOG_COLORE "\n", __VA_ARGS__, 0)
#else 
#   define warning(...) ((void)(0))
#endif

#if XLOG_LEVEL >= 1
#   define error(...) _xlog(stderr, _XLOG_COLOR1, XLOG_PREFIX1, _XLOG_COLORE "\n", __VA_ARGS__, 0)
#else 
#   define error(...) ((void)(0))
#endif

#if XLOG_LEVEL >= 0
#   define fatal(...) _xlog(stderr, _XLOG_COLOR0, XLOG_PREFIX0, _XLOG_COLORE "\n", __VA_ARGS__, 0)
#else 
#   define fatal(...) ((void)(0))
#endif

#if !defined(_NDEBUG) && XLOG_LEVEL >= 0
#define assert(cond, mesg) (void)((cond) || (_xlog(stderr, _XLOG_COLOR0, "[ ASSERT] " _FMTTRACE(__FILE__, __LINE__) ": \"" #cond "\" is false: ", _XLOG_COLORE "\n", "%s", mesg), exit(1), 0))
#else
#define assert(cond, mesg) ((void)(0))
#endif

static inline void _xlogv(FILE *stream, const char *prefix, const char *midfix, const char *suffix, const char *format, va_list args)
{
    fputs(prefix, stream);

    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    char *timestamp = (char *)malloc(strftime(NULL, (size_t)-1, XLOG_TIME_FORMAT, info));
    strftime(timestamp, (size_t)-1, XLOG_TIME_FORMAT, info);
    fputs(timestamp, stream);
    free((void*)timestamp);

    fputs(midfix, stream);
    
    vfprintf(stream, format, args);
    
    fputs(suffix, stream);
}

static inline void _xlog(FILE *stream, const char *prefix, const char *midfix, const char *suffix, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    _xlogv(stream, prefix, midfix, suffix, format, args);
    va_end(args);
}

#endif