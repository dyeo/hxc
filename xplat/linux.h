#ifndef __HXC_XPLAT_IMPLEMENTATION_H__
#define __HXC_XPLAT_IMPLEMENTATION_H__

#include <stdbool.h>
#include "../xstr.h"

bool _mkpath_impl(cstr_t sep, cstr_t path);
bool _cd_impl(cstr_t path);
cstr_t _cwd_impl();
cstr_t _pwd_impl();

#endif

#if defined(XPLAT_IMPLEMENTATION) && !defined(__HXC_XPLAT_IMPLEMENTATION_C__)
#define __HXC_XPLAT_IMPLEMENTATION_C__

#define _POSIX_C_SOURCE 200809L

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

bool _mkpath_impl(cstr_t sep, cstr_t path)
{
    info("mkdir -p %s", path);
    bool ok = true;
    size_t sep_len = strlen(sep);
    str_t temp = strnew(path);
    str_t next = temp;
    while (next)
    {
        next = strstr(next, sep);

        bool has_next = next != NULL;
        if (has_next)
        {
            next[0] = 0;
        }
        if (mkdir(temp, 755) != 0)
        {
            switch (errno)
            {
            case EEXIST:
                warning("%s: %s", temp, strerror(errno));
                break;
            default:
                error("%s: %s", temp, strerror(errno));
                ok = false;
            }
        }
        if (has_next)
        {
            next[0] = sep[0];
            next += sep_len;
        }
        if (!ok)
        {
            break;
        }
    }
    free(temp);
    return ok;
}

bool _cd_impl(cstr_t path)
{
    info("cd %s", path);
    if (chdir(path) != 0)
    {
        error("%s: %s", path, strerror(errno));
        return false;
    }
    return true;
}

cstr_t _cwd_impl()
{
    cstr_t path = getcwd(NULL, 0);
    if (path == NULL)
    {
        error("CWD: %s", strerror(errno));
    }
    return path;
}

cstr_t _pwd_impl()
{
    cstr_t path = getenv("PWD");
    if (path == NULL)
    {
        error("PWD: %s", strerror(errno));
    }
    return path;
}

#endif