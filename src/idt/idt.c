#include "idt.h"
#include "../config.h"
#include "../memory/memory.h"
#include "../kernel.h"
#include "../io/io.h"
#include <stdint.h>

struct idt_desc idt_descriptors[ECHO_OS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

extern void idt_load(struct idtr_desc* ptr); // telling C that this function will be resolved at link time
extern void int21h();
extern void no_interrupt();

void int21h_handler() { 
    print("Keyboard Pressed\n");
    outb(PIC1_COMMAND, 0x20); // sending the master PIC an acknowledgement
}

void no_interrupt_handler() { outb(PIC1_COMMAND, 0x20); }

void idt_zero() { print("Devide by zero error\n"); }

/*
    We will use this function to setup interrupts
*/
void idt_set(int interrupt_no, void* address) {
    struct idt_desc* desc = &idt_descriptors[interrupt_no];
    desc->offset_1 = (uint32_t) address & 0x0000FFFF;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0x00; 
    desc->type_attr = 0xEE; // setting an interrupt gate (type 0d1110) in user space (DPL 0b11) with present bit set to 1
    desc->offset_2 = (uint32_t) address >> 16;
}

void idt_init() {
    // setting the array to nulls
    memset(idt_descriptors, 0, sizeof(idt_descriptors));

    // setting the base and limit of IDT in IDTR
    idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base = (uint32_t) idt_descriptors;
   
    for (int i = 0; i < ECHO_OS_TOTAL_INTERRUPTS; ++i)
        idt_set(i, no_interrupt);

    idt_set(0, idt_zero);
    idt_set(0x21, int21h);

    // load the IDT
    idt_load(&idtr_descriptor);
}

