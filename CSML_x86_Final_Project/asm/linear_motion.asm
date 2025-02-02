section .note.GNU-stack noalloc noexec nowrite progbits

section .text
    global linear_motion
    
linear_motion:
    ; Load x and speed_x into xmm0 and xmm1
    movss xmm0, [rdi]    ; xmm0 = *x (load value pointed to by rdi)
    movss xmm1, [rsi]    ; xmm1 = *speed_x (load value pointed to by rsi)

    ; Add speed_x to x
    addss xmm0, xmm1     ; xmm0 = *x + *speed_x

    ; Store the result back into x
    movss [rdi], xmm0    ; *x = xmm0

    ; Load y and speed_y into xmm2 and xmm3
    movss xmm2, [rdx]    ; xmm2 = *y (load value pointed to by rdx)
    movss xmm3, [rcx]    ; xmm3 = *speed_y (load value pointed to by rcx)

    ; Add speed_y to y
    addss xmm2, xmm3     ; xmm2 = *y + *speed_y

    ; Store the result back into y
    movss [rdx], xmm2    ; *y = xmm2

    ret