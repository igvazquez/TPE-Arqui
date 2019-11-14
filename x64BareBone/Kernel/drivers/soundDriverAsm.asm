GLOBAL playSound
GLOBAL noSound

playSound:
    push rax
    push rbx
    push rcx
    push rdx

    mov ebx, edi    ;rbx = nFrequence
    mov eax, 1193180
    mov edx, 0
    
    div ebx         ;rax = 1193180 / nFrequence
    push rax    ;backUp de rax

    ;Set the PIT to the desired frequency
    mov al, 0xb6
    out 0x43, al  ;outb(0x43, 0xb6);
    
    pop rdx    ;restauro rax

    out 0x42, al    ;outb(0x42, (uint8_t) (Div) );
    shr eax, 8      ;rax = div >> 8
    out 0x42, al    ;outb(0x42, (uint8_t) (Div >> 8));

    in al, 0x61     ; tmp
    mov cl, al      ; tmp
    or al, 3        ; tmp | 3
    cmp al, cl      ; tmp != (tmp | 3)
    je .fin
    out 0x61, al

    .fin:
    pop rdx
    pop rcx
    pop rbx
    pop rax
    ret
;

noSound:
    push rax

    in al, 0x61
    and al, 0xFC
    out 0x61, al

    pop rax
    ret
;