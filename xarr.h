/*
xarr.h: Resizable Arrays
Original Author: Dan Yeomans, 2021
Original Library: HXC: The Header-Only Extension Library for C
*/

#ifndef __HXC_XARR_H__
#define __HXC_XARR_H__

#include <stdlib.h>

#define _arr_roundup32(x) (--(x), (x) |= (x) >> 1, (x) |= (x) >> 2, (x) |= (x) >> 4, (x) |= (x) >> 8, (x) |= (x) >> 16, ++(x))

typedef struct
{
    size_t len, max;
    void *arr;
} _gen_arr_t;

#define arr_t(type)      \
    struct               \
    {                    \
        size_t len, max; \
        type *arr;       \
    }

#define arr_new(a) \
    ((a).len = (a).max = 0, (a).arr = NULL)

#define arr_free(a) \
    ((a).len = (a).max = 0, free((a).arr))

#define arr_rfree(a)                         \
    do                                       \
    {                                        \
        for (size_t i = 0; i < (a).len; ++i) \
        {                                    \
            free((a).arr[i]);                \
        }                                    \
        (a).len = (a).max = 0;               \
        free((a).arr);                       \
    } while (0)

#define arr_at(a, i) \
    ((a).arr[(i)])

#define arr_resize(type, a, s) \
    ((a).max = (s), (a).arr = (type *)realloc((a).arr, sizeof(type) * (a).max))

#define arr_expand(type, a) \
    ((a).max = (a).max ? (a).max << 1 : 2, (a).arr = (type *)realloc((a).arr, sizeof(type) * (a).max))

#define arr_push(type, a, v)      \
    do                            \
    {                             \
        if ((a).len == (a).max)   \
            arr_expand(type, a);  \
        (a).arr[(a).len++] = (v); \
    } while (0)

#define arr_insert(type, a, i, v)                        \
    do                                                   \
    {                                                    \
        if ((a).len == (a).max)                          \
            arr_expand(type, a);                         \
        if ((i) >= 0 && (i) <= (a).len)                  \
        {                                                \
            for (size_t __j = (a).len; __j > (i); --__j) \
            {                                            \
                (a).arr[__j] = (a).arr[__j - 1];         \
            }                                            \
            ++(a).len;                                   \
            (a).arr[(i)] = (v);                          \
        }                                                \
    } while (0)

#define arr_pop(a) \
    ((a).arr[--(a).len])

#define arr_remove(type, a, i)                           \
    do                                                   \
    {                                                    \
        if ((i) >= 0 && (i) < (a).len)                   \
        {                                                \
            --(a).len;                                   \
            for (size_t __j = (i); __j < (a).len; ++__j) \
            {                                            \
                (a).arr[__j] = (a).arr[__j + 1];         \
            }                                            \
        }                                                \
    } while (0)

#define arr_foreach(type, elem, a, expr)           \
    do                                             \
    {                                              \
        for (size_t __i = 0; __i < (a).len; ++__i) \
        {                                          \
            type elem = (a).arr[__i];              \
            expr                                   \
        }                                          \
    } while (0)

#define arr_select(type, src, dst, cond)             \
    arr_foreach(type, __elem, src,                   \
                {                                    \
                    if ((cond(__elem)))              \
                    {                                \
                        arr_push(type, dst, __elem); \
                    }                                \
                })

#define arr_prune(type, src, dst, cond)              \
    arr_foreach(type, __elem, src,                   \
                {                                    \
                    if (!(cond(__elem)))             \
                    {                                \
                        arr_push(type, dst, __elem); \
                    }                                \
                })

#endif
