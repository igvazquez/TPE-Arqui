GLOBAL write

section .text

;-----------------------------------------------------------
; write - Llama a la syscall Write
;-----------------------------------------------------------
; rdi - FileDescriptor
; rsi - Puntero a string
;-----------------------------------------------------------
; Return: 
;-----------------------------------------------------------

write:
    push rdi
    push rsi
    push rdx

    mov rax, 0
    mov rbx, rsi
    mov rcx, rdi

    int 80h

    pop rdx
    pop rsi
    pop rdi

    ret
