section .asm
global insb
insb:
    push    ebp
    mov     ebp, esp
    
    xor     eax, eax
    mov     edx, [ebp + 8]      ; port number
    in      al, dx

    pop     ebp
    ret

global insw
insw:
    push    ebp
    mov     ebp, esp
    
    xor     eax, eax
    mov     edx, [ebp + 8]      ; port number
    in      ax, dx

    pop     ebp
    ret

global outb
outb:
    push    ebp
    mov     ebp, esp
    
    xor     eax, eax
    mov     edx, [ebp + 8]      ; port number
    mov     eax, [ebp + 12]     ; byte to input
    out     dx, al

    pop     ebp
    ret

global outw
outw:
    push    ebp
    mov     ebp, esp
    
    xor     eax, eax
    mov     edx, [ebp + 8]      ; port number
    mov     eax, [ebp + 12]     ; word to input
    out     dx, ax

    pop     ebp
    ret

