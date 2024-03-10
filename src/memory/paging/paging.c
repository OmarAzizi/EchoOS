#include "paging.h"
#include "../heap/kheap.h"

void paging_load_directory(uint32_t*);

static uint32_t* current_directory = 0;

/*
    This creates a page directory with a bunch of 
    page tables that covers the entire 4GB of RAM
*/
struct paging_4gb_chunk* paging_new_4gb(uint8_t flags) {
    uint32_t* directory = kalloc(sizeof(uint32_t) * PAGING_TOTAL_ENTRIES_PER_TABLE);
    
    // Looping through the page directory entries
    int offset = 0;
    for (size_t i = 0; i < PAGING_TOTAL_ENTRIES_PER_TABLE; ++i) {
        uint32_t* entry = kzalloc(sizeof(uint32_t) * PAGING_TOTAL_ENTRIES_PER_TABLE);

        for (size_t j = 0; j < PAGING_TOTAL_ENTRIES_PER_TABLE; ++j)
            entry[j] = (offset + (j * PAGING_PAGE_SIZE)) | flags;

        offset += (PAGING_TOTAL_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE);
        directory[i] = (uint32_t)entry | flags | PAGING_IS_WRITEABLE;
    }
    
    struct paging_4gb_chunk* chunk_4gb = kzalloc(sizeof(struct paging_4gb_chunk));
    chunk_4gb->directory_entry = directory;

    return chunk_4gb;
}

void paging_switch(uint32_t* directory) {
    paging_load_directory(directory);
    current_directory = directory;
}

uint32_t* paging_4gb_chunk_get_directory(struct paging_4gb_chunk* chunk) {
    return chunk->directory_entry;
}
