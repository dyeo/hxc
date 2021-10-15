/*
xtree.h: Dynamic Memory Management
Original Author: Dan Yeomans, 2021
Original Library: HXC: The Header-Only Extension Library for C
*/

#ifndef __HXC_XMEM_H__
#define __HXC_XMEM_H__

#include <stdlib.h>

void *xalloc(size_t size);
#define xcalloc(type, size) xalloc(sizeof(type) * (size))

void xfree(void *memory);

void xfrees(void *memory, size_t size);

#ifndef XMEM_HEAP_SIZE
#define XMEM_HEAP_SIZE 16777216
#endif

#endif

#ifdef XMEM_IMPLEMENTATION

typedef struct Block_
{
    unsigned char *beg;
    size_t size;
    struct Block_ *next;
    struct Block_ *prev;
} Block;

static struct
{
    volatile unsigned char data[XMEM_HEAP_SIZE];
    Block *beg;
    Block *end;
} CTX;

#define mem_block_new(NAME) (Block *)malloc(sizeof(Block))

void *xalloc(size_t size)
{
    if (CTX.beg == NULL)
    {
        CTX.beg = CTX.end = mem_block_new();
        CTX.beg->beg = &CTX.data;
        CTX.beg->size = size;
        return (void *)CTX.beg->beg;
    }
    Block *curr = CTX.beg;
    do
    {
        if (curr->size > size)
        {
            void *ret = curr->beg;
            curr->beg += size;
            return ret;
        }
        if (curr->size == size)
        {
            void *ret = curr->beg;
            if (curr->prev)
            {
                curr->prev->next = curr->next;
            }
            else
            {
                CTX.beg = curr->next;
            }
            if (curr->next)
            {
                curr->next->prev = curr->prev;
            }
            else
            {
                CTX.end = curr->prev;
            }
            free(curr);
            return ret;
        }
    } while (curr = curr->next);
    return NULL;
}

#endif