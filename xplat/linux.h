#ifndef __HXC_XPLAT_IMPLEMENTATION_H__
#define __HXC_XPLAT_IMPLEMENTATION_H__

#define _POSIX_C_SOURCE 200809L

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include "../xarr.h"
#include "../xstr.h"

bool _mkpath_impl(cstr_t sep, cstr_t path);
bool _cmd_impl(cstr_t args);
bool _cd_impl(cstr_t path);
cstr_t _cwd_impl();
cstr_t _pwd_impl();

#endif

#if defined(XPLAT_IMPLEMENTATION)

bool _mkpath_impl(cstr_t sep, cstr_t path)
{
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
                break;
            default:
                fprintf(stderr, "ERROR: %s: %s\n", temp, strerror(errno));
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

bool _cmd_impl(cstr_t args)
{
    printf("[CMD] %s\n", args);
    if (system(NULL))
    {
        return system(args);
    }
    return false;
}

bool _cd_impl(cstr_t path)
{
    printf("[CD] %s\n", path);
    if (chdir(path) != 0)
    {
        fprintf(stderr, "ERROR: %s: %s\n", path, strerror(errno));
        return false;
    }
    return true;
}

cstr_t _cwd_impl()
{
    cstr_t path = getcwd(NULL, 0);
    if(path == NULL)
    {
        fprintf(stderr, "ERROR: CWD: %s\n", strerror(errno));
    }
    return path;
}

cstr_t _pwd_impl()
{
    cstr_t path = getenv("PWD");
    if(path == NULL)
    {
        fprintf(stderr, "ERROR: PWD: %s\n", strerror(errno));
    }
    return path;
}

#endif