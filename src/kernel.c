#include "kernel.h"
#include <stdint.h>

uint16_t* video_mem = 0; 

// Will return the value of char:color to print in little-endian
uint16_t terminal_make_char(char c, char color) {  return (color << 8) | c; }

/*
    This will loop over the teminal and clear it all for us
*/
void terminal_initialize() {
    video_mem = (uint16_t*)(0xB8000); // VGA 16-color text mode
    for (int y = 0; y < VGA_HEIGHT; ++y) {
        for (int x = 0; x < VGA_WIDTH; ++x) 
            video_mem[(y * VGA_WIDTH)  + x] = terminal_make_char(' ', 0);
    }
 
}
void kernel_main() {
    terminal_initialize();
    video_mem[0] = terminal_make_char('B', 3);
}
