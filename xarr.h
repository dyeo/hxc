/*
xarr.h: Resizable Arrays
Original Author: Dan Yeomans, 2021
Original Library: HXC: The Header-Only Extension Library for C
*/

#ifndef __HXC_XARR_H__
#define __HXC_XARR_H__

#include <stdlib.h>

#define _arr_roundup32(x) (--(x), (x)|=(x)>>1, (x)|=(x)>>2, (x)|=(x)>>4, (x)|=(x)>>8, (x)|=(x)>>16, ++(x))

#define arr_t(type)      \
    struct               \
    {                    \
        size_t len, max; \
        type *arr;       \
    }

#define arr_new(a) \
    ((a).len = (a).max = 0, (a).arr = NULL)

#define arr_free(a) \
    ((a).len = (a).max = 0, (free((a).arr))

#define arr_rfree(a) \
    do                                      \
    {                                       \
        for(size_t i = 0; i < (a).len; ++i) \
        {                                   \
            free((a).arr[i]);               \
        }                                   \
        (a).len = (a).max = 0;              \
        free((a).arr);                      \
    }                                       \
    while (0)

#define arr_at(a, i) \
    ((a).arr[(i)])
    
#define arr_rat(a, i) \
    ((a).arr[(a).len-1-(i)])

#define arr_first(a) \
    ((a).arr[0])

#define arr_last(a) \
    ((a).arr[(a).len-1])

#define arr_pop(a) \
    ((a).arr[--(a).len])

#define arr_resize(type, a, s) \
    ((a).max = (s), (a).arr = (type *)realloc((a).arr, sizeof(type) * (a).max))

#define arr_expand(type, a, s) \
    ((a).max = (a).len = (s), _arr_roundup32((a).max), (a).arr = (type *)realloc((a).arr, sizeof(type) * (a).max))

#define arr_push(type, a, x)                                            \
    do                                                                  \
    {                                                                   \
        if ((a).len == (a).max)                                         \
        {                                                               \
            (a).max = (a).max ? (a).max << 1 : 2;                       \
            (a).arr = (type *)realloc((a).arr, sizeof(type) * (a).max); \
        }                                                               \
        (a).arr[(a).len++] = (x);                                       \
    } while (0)

#define arr_pushp(type, a)                                                                                        \
    (((a).len == (a).max)                                                                                         \
        ? ((a).max = ((a).max ? (a).max << 1 : 2), (a).arr = (type *)realloc((a).arr, sizeof(type) * (a).max), 0) \
        : 0),                                                                                                     \
        ((a).arr + ((a).len++))

#define arr_a(type, a, i)                                                                                                       \
    (((a).max <= (size_t)(i)                                                                                                    \
        ? ((a).max = (a).len = (i) + 1, _arr_roundup32((a).max), (a).arr = (type *)realloc((a).arr, sizeof(type) * (a).max), 0) \
        : (a).len <= (size_t)(i) ? (a).len = (i) + 1 : 0),                                                                      \
     (a).arr[(i)])

#define arr_foreach(elem, a, expr)                 \
    do                                             \
    {                                              \
        for (size_t __i = 0; __i < (a).len; ++__i) \
        {                                          \
            elem = (a).arr[__i];                   \
            expr                                   \
        }                                          \
    } while (0)

#endif
