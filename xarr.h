/*
xarr.h: Resizable Arrays
Original Author: Dan Yeomans, 2021
Original Library: HXC: The Header-Only Extension Library for C
*/

#ifndef __HXC_XARR_H__
#define __HXC_XARR_H__

#include <stdlib.h>
#include <stdbool.h>

#define def_arr_t(type, name) _def_arr_t_h(type, name) _def_arr_t_c(type, name)

#define _def_arr_t_h(type, name)                                     \
                                                                     \
    typedef struct                                                   \
    {                                                                \
        size_t len, max;                                             \
        type *arr;                                                   \
    } name##_t;                                                      \
    typedef bool (*name##_pred_t)(type);                             \
    typedef void (*name##_fptr_t)(type);                             \
                                                                     \
    static inline name##_t *name##_new();                            \
    static inline name##_t name##_init();                            \
    static inline name##_t name##_free(name##_t *a);                 \
    static inline void name##_expand(name##_t *a);                   \
    static inline void name##_push(name##_t *a, type v);             \
    static inline void name##_insert(name##_t *a, type v, size_t i); \
    static inline type name##_pop(name##_t *a);                      \
    static inline bool name##_remove(name##_t *a, size_t i);

#ifdef XARR_IMPLEMENTATION
#define _def_arr_t_c(type, name)                                                     \
                                                                                     \
    static inline name##_t *name##_new()                                             \
    {                                                                                \
        name##_t *a = (name##_t *)malloc(sizeof(name##_t));                          \
        *a = name##_init();                                                          \
        return a;                                                                    \
    }                                                                                \
                                                                                     \
    static inline name##_t name##_init()                                             \
    {                                                                                \
        return (name##_t){0, 0, 0};                                                  \
    }                                                                                \
                                                                                     \
    static inline name##_t name##_free(name##_t *a)                                  \
    {                                                                                \
        a->len = 0;                                                                  \
        a->max = 0;                                                                  \
        free(a->arr);                                                                \
    }                                                                                \
                                                                                     \
    static inline void name##_expand(name##_t *a)                                    \
    {                                                                                \
        a->max = (a->max > 0LU) ? (a->max << 1LU) : 2LU;                             \
        a->arr = (type *)realloc(a->arr, sizeof(type) * a->max);                     \
    }                                                                                \
                                                                                     \
    static inline void name##_push(name##_t *a, type v)                              \
    {                                                                                \
        if (a->len == a->max)                                                        \
        {                                                                            \
            name##_expand(a);                                                        \
        }                                                                            \
        a->arr[a->len++] = v;                                                        \
    }                                                                                \
                                                                                     \
    static inline void name##_insert(name##_t *a, type v, size_t i)                  \
    {                                                                                \
        if (a->len == a->max)                                                        \
        {                                                                            \
            name##_expand(a);                                                        \
        }                                                                            \
        if (i >= 0 && i <= a->len)                                                   \
        {                                                                            \
            for (size_t j = a->len; j > (i); --j)                                    \
            {                                                                        \
                a->arr[j] = a->arr[j - 1];                                           \
            }                                                                        \
            ++a->len;                                                                \
            a->arr[i] = v;                                                           \
        }                                                                            \
    }                                                                                \
                                                                                     \
    static inline name##_t *name##_pushif(name##_t *a, name##_t *b, name##_pred_t p) \
    {                                                                                \
        b = b ? b : name##_t_new();                                                  \
        for (size_t i = 0; i < a->len; ++i)                                          \
        {                                                                            \
            if (p(a->arr[i]))                                                        \
            {                                                                        \
                name##_push(b, a->arr[i]);                                           \
            }                                                                        \
        }                                                                            \
        return b;                                                                    \
    }                                                                                \
                                                                                     \
    static inline type name##_pop(name##_t *a)                                       \
    {                                                                                \
        return a->arr[a->len--];                                                     \
    }                                                                                \
                                                                                     \
    static inline bool name##_remove(name##_t *a, size_t i)                          \
    {                                                                                \
        if (i >= 0 && i < a->len)                                                    \
        {                                                                            \
            --a->len;                                                                \
            for (size_t __j = i; __j < a->len; ++__j)                                \
            {                                                                        \
                a->arr[__j] = a->arr[__j + 1];                                       \
            }                                                                        \
            return true;                                                             \
        }                                                                            \
        return false;                                                                \
    }                                                                                \
                                                                                     \
    static inline size_t name##_removeif(name##_t *a, name##_pred_t p)               \
    {                                                                                \
        size_t c = 0;                                                                \
        for (size_t i = 0; i < a->len; ++i)                                          \
        {                                                                            \
            if (p(a->arr[i]))                                                        \
            {                                                                        \
                ++c;                                                                 \
                --a->len;                                                            \
                for (size_t __j = i--; __j < a->len; ++__j)                          \
                {                                                                    \
                    a->arr[__j] = a->arr[__j + 1];                                   \
                }                                                                    \
            }                                                                        \
        }                                                                            \
        return c;                                                                    \
    }
#else
#define _def_arr_t_c(type, name)
#endif

#define arr_foreach(type, elem, arry, expr)                \
    for (size_t __arri = 0; __arri < (arry).len; ++__arri) \
    {                                                      \
        type elem = (arry).arr[__arri];                    \
        expr                                               \
    }

def_arr_t(bool, bool_arr);

def_arr_t(unsigned char, uchar_arr);
def_arr_t(char, char_arr);

def_arr_t(unsigned short, ushort_arr);
def_arr_t(short, short_arr);

def_arr_t(unsigned int, uint_arr);
def_arr_t(int, int_arr);

def_arr_t(unsigned long, ulong_arr);
def_arr_t(long, long_arr);

def_arr_t(size_t, size_arr);

def_arr_t(char *, str_arr);
def_arr_t(const char *, cstr_arr);

#endif
