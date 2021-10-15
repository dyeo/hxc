/*
xstr.h: String Operations
Original Author: Dan Yeomans, 2021
Original Library: HXC: The Header-Only Extension Library for C
*/

#ifndef __HXC_XSTR_H__
#define __HXC_XSTR_H__

#include <stdlib.h>
#include <string.h>

#include "xargs.h"
#include "xarr.h"

#define strjoin(SEP, ...) _strjoin((SEP), __VA_ARGS__, 0)
#define strconcat(...) _strjoin("", __VA_ARGS__, 0)

typedef char *str_t;
typedef arr_t(char *) str_arr_t;

typedef const char *cstr_t;
typedef arr_t(const char *) cstr_arr_t;

str_t _strjoin(cstr_t sep, ...)
{
    size_t sep_len = strlen(sep);
    size_t l = 0, s = 0;
    FOREACH_VARGS(sep, cstr_t, arg,
                  {
                      l += strlen(arg);
                      s += 1;
                  });
    s -= 1;
    str_t res = (str_t)malloc(l + (s * sep_len) + 1);

    l = 0;
    FOREACH_VARGS(sep, cstr_t, arg,
                  {
                      size_t n = strlen(arg);
                      memcpy(res + l, arg, n);
                      l += n;
                      if (s > 0)
                      {
                          memcpy(res + l, sep, sep_len);
                          l += sep_len;
                          s -= 1;
                      }
                  });
    res[l] = 0;
    return res;
}

#define strnew(str) (strcpy((str_t)malloc(strlen((str)) + 1), (str)))

inline static str_arr_t strsplit(cstr_t sep, cstr_t str)
{
    str_arr_t arr;
    arr_new(arr);
    size_t len = strlen(str);
    str_t res = (str_t)malloc(len + 1);
    strcpy(res, str);
    cstr_t seg = strtok(res, sep);
    while (seg != NULL)
    {
        arr_push(cstr_t, arr, seg);
        seg = strtok(NULL, sep);
    }
    return arr;
}

#define strarr(...) _strarr(__VA_ARGS__, 0)

inline static cstr_arr_t _strarr(cstr_t first, ...)
{
    cstr_arr_t res;
    arr_new(res);

    if (first == NULL)
    {
        return res;
    }

    arr_push(cstr_t, res, first);

    FOREACH_VARGS(first, cstr_t, arg, {
        arr_push(cstr_t, res, (cstr_t)strnew(arg));
    });

    return res;
}

#endif //__HXC_XSTR_H__