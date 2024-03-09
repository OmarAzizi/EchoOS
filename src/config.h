#ifndef __CONFIG_H__
#define __CONFIG_H__

#define     ECHO_OS_TOTAL_INTERRUPTS    512

#define     KERNEL_DATA_SELECTOR        0x10
#define     KERNEL_CODE_SELECTOR        0x8

// 100MB heap size
#define     ECHO_OS_HEAP_SIZE_BYTES     104857600
#define     ECHO_OS_HEAP_BLOCK_SIZE     4096
#define     ECHO_OS_HEAP_ADDRESS        0x01000000
#define     ECHO_OS_HEAP_TABLE_ADDRESS  0x00007E00

#endif
