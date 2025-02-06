section .text
    global sinus_motion
    extern sinf

sinus_motion:
    ; Ensure stack alignment
    sub rsp, 16            ; Align the stack to 16 bytes (required by x86-64 calling convention)

    ; Step 1: x += speed_x
    movss xmm0, [rsi]      ; xmm0 = *x
    movss xmm1, [rdx]      ; xmm1 = *speed_x
    addss xmm0, xmm1       ; xmm0 = *x + *speed_x
    movss [rsi], xmm0      ; *x = xmm0

    ; Step 2: Calculate sinf(time * 2.0f)
    movss xmm0, [rdi]      ; xmm0 = *time
    movss xmm1, [rel two]  ; xmm1 = 2.0
    mulss xmm0, xmm1       ; xmm0 = *time * 2.0
    call sinf              ; Call sinf(xmm0), result in xmm0

    ; Step 3: y += sinf(time * 2.0f) * speed_y
    movss xmm1, [rcx]      ; xmm1 = *y
    movss xmm2, [rdx]      ; xmm2 = *speed_y
    mulss xmm0, xmm2       ; xmm0 = sinf(time * 2.0f) * *speed_y
    addss xmm1, xmm0       ; xmm1 = *y + sinf(time * 2.0f) * speed_y
    movss [rcx], xmm1      ; *y = xmm1

    ; Restore stack alignment
    add rsp, 16            ; Restore stack alignment

    ret

section .rodata
two dd 2.0

section .note.GNU-stack noalloc noexec nowrite progbits
