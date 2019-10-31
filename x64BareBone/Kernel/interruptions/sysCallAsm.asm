;sysCallAsm.asm

GLOBAL _sysCallHandler

;Funcion encargada de de realizar la escritura a pantalla
EXTERN sysWriteHandler

;No guarda eax ya que es el registro designado para el retorno de datos
%macro pushState 0
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
%endmacro

;---------------------------------------------------------------------------------
;Funcion encargada de manejar las system calls, cuando se realiza una int 80h,
; se viene a esta funcion y de aca, en base a lo que haya en rax llamar a la
; system cal correspondiente.
;---------------------------------------------------------------------------------
; Entrada:
;   rax: ID de la system call
;   rbx, rcx, etc: depende de la system call en cuestion
;.................................................................................
; Salida: 
;	rax: retorna el valor solicitado
;---------------------------------------------------------------------------------
_sysCallHandler:
	
	pushState

	cmp rax, sysWriteID
	je .Write
	
	cmp rax, sysRTCID
	je .RTC

	jmp .end

    .Write:
        call _sysWriteLoader
        jmp .end
	
	.RTC:
		call _sysRTC
        jmp .end

    .end:
        ; signal pic EOI (End of Interrupt)
        push rax
		mov al, 20h
        out 20h, al
		pop rax
		
        popState
        iretq
;

;---------------------------------------------------------------------------------
; System Write 
%define sysWriteID 4
;---------------------------------------------------------------------------------
;Funcion encargada de tomar los valores de los registros utilizados 
;para  realizar la system call y pasarselos a la funcion.
;---------------------------------------------------------------------------------
; Entrada:
;   rbx: File Descriptor
;   rcx: Puntero al string a imprimir
;.................................................................................
; Salida: no retorna nada
;---------------------------------------------------------------------------------
_sysWriteLoader:
    
    mov rdi, rbx 
    mov rsi, rcx 
    call sysWriteHandlers
    ret
;

;---------------------------------------------------------------------------------
; System call RTC
%define sysRTCID 1
;---------------------------------------------------------------------------------
;Funcion encargada de acceder a la memoria interna del RTC 
;---------------------------------------------------------------------------------
; Entrada:
;   rbx: recibe el "Time Descriptor", es decir, si quiere los minutos, segundo, etc.
;.................................................................................
; Salida: 
;	rax: retorna el valor solicitado
;---------------------------------------------------------------------------------
_sysRTC:
	mov rax, rbx ;Time Descriptor
    out 70h, al
    in al, 71h
	call bcdToInt
	ret
;

;---------------------------------------------------------------------------------
;Funcion auxiliar para convertir el dato BCD que devuelve el RTC a binnario "comun"
;---------------------------------------------------------------------------------
bcdToInt:
	div 16

	mov cl, ah

	mov ah, 0

	mul 10

	mov bl, al

	add bl, cl

	mov al, bl

	ret
