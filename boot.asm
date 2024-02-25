BITS 16                         ; telling the assembler that we are using 16-bit architechture
ORG 0x7C00                      ; originate instruction

section     .data
    ; some constants
    NULL            EQU     0

    CODE_SEG        EQU     gdt_code - gdt_start
    DATA_SEG        EQU     gdt_data - gdt_start

; --------------------------------------------

section     .text
global _start
_start:
    ; BIOS Parameter Block (BPB)
    jmp     short start         
    nop                         ; no operation
    times   33 db 0         
start:
    jmp     0x00:step2
step2:
    ; here I will be clearing interrupts because i will change some segment registers
    cli                         ; clear interrupts
    
    mov     ax, 0x00
    mov     ds, ax
    mov     es, ax

    mov     ss, ax
    mov     sp, 0x7C00

    sti                         ; enables interrupts

; --------------------------------------------

; Loading GDT
.load_protected:
    cli
    lgdt[gdt_descriptor]        ; load global descriptor table instruction
    mov     eax, cr0
    or      eax, 0x1            ; set PE (Protection Enable) bit in CR0 (Control Register 0)
    mov     cr0, eax

    jmp     CODE_SEG:load32 

; --------------------------------------------

; Global Describtor Table (GDT)
gdt_start:

; offset 0x0 in GDT (First Entry)
gdt_null:
    dw      0x0000, 0x0000, 0x0000, 0x0000

; offset 0x8 / Code Selector (Second Entry)
gdt_code:                       ; CS should point to this
    dw      0xFFFF              ; Segment limit (first 0-15 bits)
    dw      0x0000              ; Base (16-31 bits)
    db      0x00                ; Base (32-39 bits)
    db      0x9A                ; Access Byte (40-47 bits)
    db      0xCF                ; High 4 bit Flags (52-55) and the Limit from 48-51 
    db      0x00                ; Base (56-63 bits)

; offset 0x10 / Data Selector (Third Entry)
gdt_data:                       ; DS, SS, ES, FS, GS
    dw      0xFFFF              ; Segment limit (first 0-15 bits)
    dw      0x0000              ; Base (16-31 bits)
    db      0x00                ; Base (32-39 bits)
    db      0x92                ; Access Byte (40-47 bits)
    db      0xCF                ; High 4 bit Flags (52-55) and the Limit from 48-51 
    db      0x00                ; Base (56-63 bits)

gdt_end:

; --------------------------------------------

; Global Descriptor Table Register (GDTR)
gdt_descriptor:
    dw      gdt_end - gdt_start - 1     ; size
    dd      gdt_start                   ; offset

; --------------------------------------------

BITS 32
load32:
    mov     ax, DATA_SEG
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax
    mov     ebp, 0x00200000
    mov     esp, ebp

    jmp     $

times 510-($ - $$) db 0         ; padding
dw  0xAA55                      ; magic number
