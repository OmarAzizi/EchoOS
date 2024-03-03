[BITS 32]

extern  kernel_main

global _start
_start:
    mov     ax, DATA_SEG
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax
    mov     ebp, 0x00200000
    mov     esp, ebp

    ; Enable the A20 line
    in      al, 0x92
    or      al, 2
    out     0x92, al
    
    ; Remap the master PIC (Programmable Interrupt Controller)
    mov     al, 0x11            ; PIC initialize command
    out     PIC1_COMMAND, al    ; tell master PIC
    out     PIC2_COMMAND, al    ; tell slave PIC

    mov     al, 0x20            ; remapping master ISR to start at 0x20 (32d)
    out     PIC1_DATA, al        
    mov     al, 0x28            ; remapping slave ISR to start at 0x28 (40d)
    out     PIC2_DATA, al        

    mov     al, 0x01        
    out     PIC1_DATA, al       ; Putting the master PIC in x86 mode
    out     PIC2_DATA, al       ; Putting the slave PIC in x86 mode
    
    call    kernel_main
    jmp     $

section     .data
    CODE_SEG        EQU     0x08
    DATA_SEG        EQU     0x10

    PIC1		    EQU     0x20		; IO base address for master PIC 
    PIC2		    EQU     0xA0		; IO base address for slave PIC

    PIC1_COMMAND	EQU     PIC1       
    PIC1_DATA	    EQU     PIC1 + 1

    PIC2_COMMAND	EQU     PIC2
    PIC2_DATA	    EQU     PIC2 + 1

times 512-($ - $$) db 0
