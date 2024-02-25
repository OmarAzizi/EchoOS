BITS 16                         ; telling the assembler that we are using 16-bit architechture
ORG 0                           ; originate instruction

section     .data
    ; some constants
    NULL            EQU     0
    
    ; Ralf Brown Interrupt List (RBIL) interrupts
    RBIL_VIDEO      EQU     0x10
    RBIL_DISK       EQU     0x13
    
    DISPLAY_CHAR    EQU     0Eh
    READ_SECTOR     EQU     0x2

section     .text
global _start
_start:
    ; BIOS Parameter Block (BPB)
    jmp     short start         
    nop                         ; no operation
    times   33 db 0         
start:
    jmp     0x7C0:step2
step2:
    ; here I will be clearing interrupts because i will change some segment registers
    cli                         ; clear interrupts
    
    mov     ax, 0x7C0
    mov     ds, ax
    mov     es, ax
    mov     ax, 0x00

    mov     ss, ax
    mov     sp, 0x7C00

    sti                         ; enables interrupts
    
    mov     ah, READ_SECTOR
    mov     al, 0x1             ; number of sectors
    mov     ch, 0               ; cylinder (low 8 bits)
    mov     cl,0x2              ; sector number 2
    mov     dh, 0x0             ; head number
    mov     bx, buffer
    int     RBIL_DISK
    
    jc      error               ; if the carry flag is set handle the error
    
    mov     si, buffer
    call    print_message

    jmp     $                   ; infinite loop
error:
    mov     si, error_message
    call    print_message
    jmp     $                   ; infinite loop
print_message:
    mov     bx, 0
.loop:
    lodsb                       ; will load the charchter that the `DS:SI` register is pointing to into `AL`
    cmp     al, NULL            ; check if we reached end of the string
    je      .done
    call    print_char
    jmp     .loop               ; repeat to the next charchter
.done:
    ret

print_char:
    mov     ah, DISPLAY_CHAR
    int     RBIL_VIDEO
    ret

error_message: db "Failed to laod sector", 0

times 510- ($ - $$) db 0        ; padding
dw  0xAA55                      ; magic number

buffer: 
