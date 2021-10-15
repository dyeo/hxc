#include <stdio.h>

#define XPLAT_IMPLEMENTATION
#include "../xplat.h"

int main()
{
    PWD();

    cstr_arr_t a;
    arr_new(a);
    arr_push(cstr_t, a, "hi!1");
    arr_push(cstr_t, a, "hi!2");
    arr_push(cstr_t, a, "hi!3");

    arr_foreach(cstr_t i, a,
        printf("%s\n", i);
    );

    CD("tests", "xplat_test");
    if(MKPATH("tests", "var", "xplat_test"))
    {
        return 0;
    }
    printf("woops!\n");
    return 1;
}