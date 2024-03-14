#include "disk.h"
#include "../io/io.h"
#include "../memory/memory.h"
#include "../config.h"
#include "../status.h"

struct disk disk; // This will represent the primary hard disk

/*
    This function will read a number of sectors from the primary hard disk 
    specified in 'total' starting from logical block address (lba) into the buffer 'buf'

    This is a low level function used by kernel not users (it will be abstracted)
*/
int disk_read_sector(int lba, int total, void* buf) {
    outb(0x1F6, (lba >> 24) | 0xE0);
    outb(0x1F2, total);
    outb(0x1F3, (unsigned char)(lba & 0xFF));
    outb(0x1F4, (unsigned char)(lba >> 8));
    outb(0x1F5, (unsigned char)(lba >> 16));
    outb(0x1F7, 0x20);

    unsigned short* ptr = (unsigned short*) buf;
    for (int i = 0; i < total; ++i) {
        // Wait for the buffer to be ready
        char c = insb(0x1F7);
        while (!(c & 0x08)) c = insb(0x1F7);

        // read from hard disk to memory
        for (int j = 0; j < 256; ++j) {
            *ptr = insw(0x1F0);
            ++ptr;
        }
    }
    return 0;
}

/*
    This function will be responsible of searching for disks and initiallizing them
*/ 
void disk_search_and_init() {
    // Its not actually searching (we dont have a disk array)
    memset(&disk, 0, sizeof(disk));
    disk.type = ECHO_OS_TYPE_REAL;
    disk.sector_size = ECHO_OS_SECTOR_SIZE;
}

/*
    This will get a disk by index
*/
struct disk* disk_get(int index) {
    // we are not really using the index (we dont habe a disk array)
    if (index != 0) return 0;
    return &disk;
}

/*
    This and `disk_get` will be useful when we implement a secondary disk
*/
int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buf) {
    if (idisk != &disk) return -EIO;

    return disk_read_sector(lba, total, buf);
}
