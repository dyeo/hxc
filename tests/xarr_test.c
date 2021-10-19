#define XARR_IMPLEMENTATION
#include "../xarr.h"

#include "../xlog.h"

int main(int argc, char **argv)
{
    int_arr_t *a = int_arr_new();
    int_arr_push(a, 1);

    arr_foreach(int, i, *a, {
        debug("%d", i);
    });

    return 0;
}