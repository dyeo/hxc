#include <stdio.h>

#define XPLAT_IMPLEMENTATION
#include "../xplat.h"

#include "../xstr.h"

bool is_hi1(cstr_t elem)
{
    return elem == "hi!1";
}

int main()
{
    CD(".");

    fatal("Hi!");

    int_arr_t ia;
    arr_new(ia);

    cstr_arr_t *a;
    arr_new(a);
    cstr_arr_t b;
    arr_new(b);
    cstr_arr_push(a, strnew("hi!1"));
    cstr_arr_push(a, strnew("hi!2"));
    cstr_arr_push(a, strnew("hi!3"));

    arr_foreach(cstr_t, i, *a, {
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