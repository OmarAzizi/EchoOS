#ifndef __KHEAP_H__
#define __KHEAP_H__

#include <stdint.h>
#include <stddef.h>

void* kalloc(size_t);
void  kfree(void*);
void  kheap_init();

#endif
