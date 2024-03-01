section .asm
global idt_load
; this function will be called from our C code and will load the IDT
idt_load:
    push    ebp             ; pushing the return value of the caller
    mov     ebp, esp

    mov     ebx, [ebp + 8]  ; moving the value of IDTR into ebx 
    lidt    [ebx]           ; loading IDT

    pop     ebp
    ret
