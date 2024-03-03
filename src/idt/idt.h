#ifndef __IDT_H__
#define __IDT_H__

#define     PIC1		    0x20		/* IO base address for master PIC */
#define     PIC2		    0xA0		/* IO base address for slave PIC */
#define     PIC1_COMMAND    PIC1
#define     PIC1_DATA	    PIC1 + 1
#define     PIC2_COMMAND	PIC2
#define     PIC2_DATA	    PIC2 + 1

#include <stdint.h>

/*
    This struct implemlents Interrupt Descriptor Table (IDT)
*/
struct idt_desc {
    uint16_t offset_1; // offset bits 0 - 15
    uint16_t selector; // selector thats in out GDT
    uint8_t zero; // unused/reserved bits (set to zero)
    uint8_t type_attr; // descriptor type attributes
    uint16_t offset_2; // offset bits 16 - 31
} __attribute__((packed));

/*
    This struct implements IDTR (IDT Register).
    The location of the IDT is kept in the IDTR (IDT register).

    This is loaded using the LIDT assembly instruction, 
    whose argument is a pointer to an IDT Descriptor structure.
*/
struct idtr_desc {
    uint16_t limit; // size of IDT minus 1
    uint32_t base;  // base addtess of the IDT
} __attribute__((packed));

void idt_init();
void enable_interrupts();
void disable_interrupts();

#endif
