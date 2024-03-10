#ifndef __KHEAP_H__
#define __KHEAP_H__

#include <stdint.h>
#include <stddef.h>

void* kalloc(size_t);
void  kfree(void*);
void  kheap_init();

/*
    kzalloc is same as kalloc but will set 
    the memory to nulls (zeros)
*/
void* kzalloc(size_t);

#endif
