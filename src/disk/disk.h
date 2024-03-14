#ifndef __DISK_H__
#define __DISK_H__

typedef unsigned int ECHO_OS_DISK_TYPE;

// Represents a real physical hard disk
#define ECHO_OS_TYPE_REAL 0

// This struct will act like an interface for the user
struct disk {
    ECHO_OS_DISK_TYPE type;
    int sector_size;
};

// The interface (the abstraction) that the user will use
void disk_search_and_init();
struct disk* disk_get(int);
int disk_read_block(struct disk*, unsigned int, int, void*);

#endif
