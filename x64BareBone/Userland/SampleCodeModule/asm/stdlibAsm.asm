GLOBAL write
GLOBAL getCharAsm
GLOBAL setCursorPosAsm
GLOBAL getTicksElapsedAsm
GLOBAL triggerException6Asm
GLOBAL getAllRegisters
GLOBAL getRegister
GLOBAL getScreenWidth
GLOBAL getScreenHeight

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

setCursorPosAsm:
	push rbx
	push rcx

	mov rax, 7
	mov rbx, rdi
	mov rcx, rdx
	int 80h

	pop rcx
	pop rbx
    
	ret

getTicksElapsedAsm:
	mov rax, 0
	int 80h

	ret

getScreenWidth:
    mov rax, 1
    int 80h

    ret

getScreenHeight:
    mov rax, 2
    int 80h

    ret

triggerException6Asm:
	int 300h
	ret

getAllRegisters:
	mov rax, 5
	int 80h

	ret

getRegister:
    push rbp
    mov rbp, rsp
    push rax

    mov rax, rdi
    
    cmp rax, 0
    je getRAX
    cmp rax, 1
    je getRBX
    cmp rax, 2
    je getRCX
    cmp rax, 3
    je getRDX
    cmp rax, 4
    je getRBP
    cmp rax, 5
    je getRDI
    cmp rax, 6
    je getRSI
    cmp rax, 7
    je getR8
    cmp rax, 8
    je getR9
    cmp rax, 9
    je getR10
    cmp rax, 10
    je getR11
    cmp rax, 11
    je getR12
    cmp rax, 12
    je getR13
    cmp rax, 13
    je getR14
    cmp rax, 14
    je getR15
   ; cmp rax, 15
   ; je getRIP

    _exit:
        mov rsp, rbp
        pop rbp
        ret

    getRAX:
        pop rax
        jmp _exit

    getRBX:
        mov rax, rbx
        jmp _exit

    getRCX:
        mov rax, rcx
        jmp _exit

    getRDX:
        mov rax, rdx
        jmp _exit

    getRBP:
        mov rsp, rbp
        pop rax
        ret

    getRDI:
        mov rax, rdi
        jmp _exit

    getRSI:
        mov rax, rsi
        jmp _exit

    getR8:
        mov rax, r8
        jmp _exit
    getR9:
        mov rax, r9
        jmp _exit

    getR10:
        mov rax, r10
        jmp _exit

    getR11:
        mov rax, r11
        jmp _exit
    getR12:
        mov rax, r12
        jmp _exit

    getR13:
        mov rax, r13
        jmp _exit

    getR14:
        mov rax, r14
        jmp _exit
    
    getR15:
        mov rax, r15
        jmp _exit

   ; getRIP:
   ;     mov rax, cs:rip
   ;     jmp _exit
