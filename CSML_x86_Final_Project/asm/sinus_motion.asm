section .data
    two_float dd 2.0            ; Constant 2.0f for time scaling

section .text
    global sinus_motion
sinus_motion:
    ; sinus_motion(float* time, float* x, float* speed_x, float* y, float* speed_y)
    push rbp
    mov rbp, rsp
    sub rsp, 16                 ; Reserve space for local variables

    ; Load pointers into registers
    mov rdi, rdi                ; time
    mov rsi, rsi                ; x
    mov rdx, rdx                ; speed_x
    mov rcx, rcx                ; y
    mov r8, r8                  ; speed_y

    ; Update x = *x + *speed_x
    movss xmm0, dword [rsi]     ; Load *x
    movss xmm1, dword [rdx]     ; Load *speed_x
    addss xmm0, xmm1            ; *x += *speed_x
    movss dword [rsi], xmm0     ; Store result back to *x

    ; Compute sin(time * 2.0f)
    movss xmm2, dword [rdi]     ; Load *time
    mulss xmm2, dword [rel two_float] ; time * 2.0f
    movss dword [rsp], xmm2     ; Store for FPU operation

    ; Compute sine using FPU
    fld dword [rsp]             ; Load time * 2.0f onto FPU stack
    fsin                        ; Calculate sine
    fstp dword [rsp]            ; Store sine result
    movss xmm3, dword [rsp]     ; Load sine result into xmm3

    ; Multiply sine by speed_y
    movss xmm4, dword [r8]      ; Load *speed_y
    mulss xmm3, xmm4            ; sin(time * 2.0f) * *speed_y

    ; Update y = *y + computed value
    movss xmm5, dword [rcx]     ; Load *y
    addss xmm5, xmm3            ; *y += sin(time * 2.0f) * *speed_y
    movss dword [rcx], xmm5     ; Store result back to *y

    add rsp, 16                 ; Restore stack
    leave
    ret

section .note.GNU-stack noexec
