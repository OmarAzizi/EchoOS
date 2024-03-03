extern int21h_handler
extern no_interrupt_handler

section     .asm
global enable_interrupts
enable_interrupts:
    sti
    ret

global disable_interrupts
disable_interrupts:
    cli
    ret

global idt_load
; this function will be called from our C code and will load the IDT
idt_load:
    push    ebp             ; pushing the return value of the caller
    mov     ebp, esp

    mov     ebx, [ebp + 8]  ; moving the value of IDTR into ebx 
    lidt    [ebx]           ; loading IDT

    pop     ebp
    ret

; remapped keyboard interrupt
global int21h
int21h:
    cli                     ; clear interrupts
    pushad                  ; push all general purpose registers
    call    int21h_handler
    popad                   ; pop all general purpose register
    sti                     ; set interrupts
    iret

global no_interrupt
no_interrupt:
    cli                     ; clear interrupts
    pushad                  ; push all general purpose registers
    call    no_interrupt_handler
    popad                   ; pop all general purpose register
    sti                     ; set interrupts
    iret


