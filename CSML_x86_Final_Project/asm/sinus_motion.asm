section .text
    global sinus_motion
    extern sinf

sinus_motion:
    ; Parameters:
    ; rdi = time (pointer)
    ; rsi = x (pointer)
    ; rdx = speed_x (pointer)
    ; rcx = y (pointer)
    ; r8  = speed_y (pointer)

    push rbp
    mov rbp, rsp        ; Set up base pointer
    and rsp, -16        ; Align stack to 16 bytes

    ; Step 1: x += speed_x
    movss xmm0, [rsi]    ; Load *x into xmm0
    movss xmm1, [rdx]    ; Load *speed_x into xmm1
    addss xmm0, xmm1     ; xmm0 = *x + *speed_x
    movss [rsi], xmm0    ; Store result back to *x

    ; Step 2: Calculate sinf(time * 2.0f) * speed_y
    movss xmm0, [rdi]    ; Load *time into xmm0
    movss xmm1, [rel two] ; Load constant 2.0 into xmm1
    mulss xmm0, xmm1     ; xmm0 = *time * 2.0

    ; Call sinf
    sub rsp, 8           ; Reserve space for stack alignment
    call sinf            ; Result in xmm0
    add rsp, 8           ; Restore stack

    ; Multiply sinf result by *speed_y
    movss xmm1, [r8]     ; Load *speed_y into xmm1
    mulss xmm0, xmm1     ; xmm0 = sinf(*time * 2.0) * *speed_y

    ; Step 3: Add result to *y
    movss xmm1, [rcx]    ; Load *y into xmm1
    addss xmm1, xmm0     ; xmm1 = *y + sinf(*time * 2.0) * *speed_y
    movss [rcx], xmm1    ; Store result back to *y

    mov rsp, rbp         ; Restore stack
    pop rbp
    ret

section .rodata
two dd 2.0

section .note.GNU-stack noalloc noexec nowrite progbits
