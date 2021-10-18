#include <stdio.h>

#define XPLAT_IMPLEMENTATION
#include "../xplat.h"

#include "../xstr.h"

bool is_hi1(cstr_t elem)
{
    return elem == "hi!1";
}

typedef arr_t(int) int_arr_t;

int main()
{
    CD(".");

    fatal("Hi!");

    int_arr_t ia;
    arr_new(ia);

    cstr_arr_t a;
    arr_new(a);
    cstr_arr_t b;
    arr_new(b);
    arr_push(cstr_t, a, strnew("hi!1"));
    arr_push(cstr_t, a, strnew("hi!2"));
    arr_push(cstr_t, a, strnew("hi!3"));

    arr_prune(cstr_t, a, b, is_hi1);

    arr_foreach(cstr_t, i, b, {
        printf("%s\n", i);
    });

    arr_rfree(a);
    CD("tests", "xplat_test");
    if (MKPATH("tests", "var", "xplat_test"))
    {
        return 0;
    }
    printf("woops!\n");
    return 1;
}