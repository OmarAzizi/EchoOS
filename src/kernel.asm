[BITS 32]

extern  kernel_main

CODE_SEG    EQU     0x08
DATA_SEG    EQU     0x10

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
    
    call    kernel_main
    jmp     $

; This divides by zero to test interrupt 0 in the that we sat up in IDT
global  problem
problem:
    mov     eax, 0
    div     eax

times 512-($ - $$) db 0
