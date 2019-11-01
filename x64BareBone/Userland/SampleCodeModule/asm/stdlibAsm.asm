GLOBAL write
GLOBAL getCharAsm

section .text

;-----------------------------------------------------------
; write - Llama a la syscall Write
;-----------------------------------------------------------
; rdi - FileDescriptor
; rsi - Puntero a string
;-----------------------------------------------------------
; Return: 
;-----------------------------------------------------------

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

write:
    push rbx
    push rcx
    mov rax, 4
    mov rbx, rdi
    mov rcx, rsi
    int 80h
    pop rcx
    pop rbx
    
    ret

getCharAsm:
    mov rax, 3
    int 80h 

    ret
    