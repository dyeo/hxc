#ifndef __HXC_XPLAT_IMPLEMENTATION_H__
#define __HXC_XPLAT_IMPLEMENTATION_H__

#include <stdbool.h>
#include "../xstr.h"
#include "../xlog.h"

bool _cmd_impl(cstr_t args);

#endif

#if defined(XPLAT_IMPLEMENTATION)

bool _cmd_impl(cstr_t args)
{
    info("CMD: %s\n", args);
    if (system(NULL))
    {
        return system(args);
    }
    error("CMD: No command processor");
    return false;
}

#endif