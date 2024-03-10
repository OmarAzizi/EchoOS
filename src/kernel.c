#include "kernel.h"
#include "./idt/idt.h"
#include "./io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"

#include <stdint.h>
#include <stddef.h>

uint16_t* video_mem = 0; 
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

void next_row() {
    terminal_row += 1;
    terminal_col = 0;
}

// Will return the value of char:color to print in little-endian
uint16_t terminal_make_char(char c, char color) {  return (color << 8) | c; }

void terminal_putchar(int x, int y, char c, char color) {
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, color);
}

void terminal_writechar(char c, char color) {
    if (c == '\n') {
        next_row();
        return;
    }

    terminal_putchar(terminal_col, terminal_row, c, color);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH) next_row();
}

/*
    This will loop over the teminal and clear it all for us
*/
void terminal_initialize() {
    terminal_row = 0;
    terminal_col = 0;

    video_mem = (uint16_t*)(0xB8000); // VGA 16-color text mode
    for (int y = 0; y < VGA_HEIGHT; ++y) {
        for (int x = 0; x < VGA_WIDTH; ++x) terminal_putchar(x, y, ' ', 0);
    }
 
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) ++len;
    return len;
}

void print(const char* str) {
    size_t len = strlen(str);
    for (int i = 0; i < len; ++i) 
        terminal_writechar(str[i], 15); 
}
static struct paging_4gb_chunk* kernel_chunk;

void kernel_main() {
    terminal_initialize();
    print("Hello, World!\nMy Name is Omar :))\n\n");
    
    kheap_init(); 

    idt_init(); // initialize Interrupt Descriptor Table

    void* ptr = kalloc(50);
    void* ptr2 = kalloc(5000);
    void* ptr3 = kalloc(5600);

    kfree(ptr);
    void* ptr4 = kalloc(50);

    if (ptr || ptr2 || ptr3 || ptr4) {
        print("Initialized a variable in heap successfully :)\n");
    }
    
    // setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    
    // switch to kernel paging chunk
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));
    
    // enable paging
    enable_paging();

    enable_interrupts();
}
