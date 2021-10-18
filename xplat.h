#ifndef __HXC_XPLAT_H__
#define __HXC_XPLAT_H__

// probably need a more sophisticated way of determined 64 or 32 bit
#if defined(_WIN64) || defined(_LP64) || defined(__LP64__) || defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_AMD_64) || defined(__aarch64__)
#   define XPLAT_64_BIT
#   define XSIZE 8
    typedef signed long xint_t;
    typedef unsigned long xuint_t;
#else
#   define XPLAT_32_BIT
#   define XSIZE 4
    typedef signed int xint_t;
    typedef unsigned int xuint_t;
#endif

#include "xplat/common.h"

#define CMD_SEP " "
#define PATH_SEP "/"
#define ENV_SEP ":"
#define FILE_ENDL "\n"

#if defined(_WIN64) || defined(_WIN32)
#   define XPLAT_WINDOWS
#   define PATH_SEP "\\"
#   define ENV_SEP ";"
#   define FILE_ENDL "\r\n"
#   include "xplat/windows.h"
#endif

#if defined(__APPLE__)
#   define XPLAT_APPLE
#   include "TargetConditionals.h"
#   if defined(TARGET_OS_SIMULATOR)
#       define XPLAT_IOS_SIMULATOR
#   elif TARGET_OS_IPHONE && TARGET_OS_MACCATALYST
#       define XPLAT_MAC_CATALYST
#   elif TARGET_OS_IPHONE
#       define XPLAT_IOS
#   else
#       define XPLAT_OSX
#   endif
#   include "xplat/apple.h"
#endif

#if defined(__ANDROID__)
#   define XPLAT_ANDROID
#   include "xplat/android.h"
#endif

#if defined(__linux)
#   define XPLAT_LINUX
#   include "xplat/linux.h"
#endif

#if defined(__FreeBSD__)
#   define XPLAT_BSD
#   define XPLAT_FREEBSD
#   include "xplat/bsd.h"
#elif defined(__NetBSD__)
#   define XPLAT_BSD
#   define XPLAT_FREEBSD
#   include "xplat/bsd.h"
#elif defined(__OpenBSD__)
#   define XPLAT_BSD
#   define XPLAT_OPENBSD
#   include "xplat/bsd.h"
#elif defined(__DragonFly__)
#   define XPLAT_BSD
#   define XPLAT_DRAGONFLY
#   include "xplat/bsd.h"
#endif

#if defined(__unix)
#   define XPLAT_UNIX
#   include "xplat/unix.h"
#elif defined(__posix)
#   define XPLAT_POSIX
#   include "xplat/posix.h"
#endif

#define PATH(...) strjoin(PATH_SEP, __VA_ARGS__, 0)

#define MKPATH(...) _mkpath_impl(PATH_SEP, PATH(__VA_ARGS__))

#define CMD(...) _cmd_impl(strjoin(CMD_SEP, __VA_ARGS__))

#define CD(...) _cd_impl(PATH(__VA_ARGS__))

#define CWD() _cwd_impl()

#define PWD() _pwd_impl()

#endif