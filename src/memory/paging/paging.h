#ifndef __PAGING_H__
#define __PAGING_H__

#include <stdint.h>
#include <stddef.h>

/* 
    defining bitmasks
*/
#define     PAGING_CACHE_DISABLED               0b00010000
#define     PAGING_WRITE_THROUGH                0b00001000
#define     PAGING_ACCESS_FROM_ALL              0b00000100
#define     PAGING_IS_WRITEABLE                 0b00000010
#define     PAGING_IS_PRESENT                   0b00000001

#define     PAGING_TOTAL_ENTRIES_PER_TABLE      1024
#define     PAGING_PAGE_SIZE                    4096

/*
    This will be the paging directory that 
    will map the whole 4GB addtess space
*/
struct paging_4gb_chunk {
    uint32_t* directory_entry;
};

void paging_switch(uint32_t*);
struct paging_4gb_chunk* paging_new_4gb(uint8_t);
uint32_t* paging_4gb_chunk_get_directory(struct paging_4gb_chunk*);

// assembly function
void enable_paging();

#endif
