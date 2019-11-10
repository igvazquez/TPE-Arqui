GLOBAL cpuVendor
GLOBAL getRegister

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret
;

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
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret
