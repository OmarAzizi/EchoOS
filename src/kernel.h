#ifndef __KERNEL_H__
#define __KERNEL_H__

#define VGA_WIDTH  80
#define VGA_HEIGHT 20

#define ECHO_OS_MAX_PATH 108

void kernel_main();
void print(const char* str);

#endif
