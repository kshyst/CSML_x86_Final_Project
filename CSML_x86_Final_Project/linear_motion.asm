section .data
    ; No global data needed for this function

section .text
    global linear_motion

; Function prototype:
; void linear_motion(float* x, float* speed_x, float* y, float* speed_y);

linear_motion:
    ; Load addresses of x, speed_x, y, and speed_y into registers
    mov rdi, [rdi]       ; Dereference x pointer (rdi = x)
    mov rsi, [rsi]       ; Dereference speed_x pointer (rsi = speed_x)
    mov rdx, [rdx]       ; Dereference y pointer (rdx = y)
    mov rcx, [rcx]       ; Dereference speed_y pointer (rcx = speed_y)

    ; Load x and speed_x into xmm0 and xmm1
    movss xmm0, [rdi]    ; xmm0 = x
    movss xmm1, [rsi]    ; xmm1 = speed_x

    ; Add speed_x to x
    addss xmm0, xmm1     ; xmm0 = x + speed_x

    ; Store the result back into x
    movss [rdi], xmm0    ; x = xmm0

    ; Load y and speed_y into xmm2 and xmm3
    movss xmm2, [rdx]    ; xmm2 = y
    movss xmm3, [rcx]    ; xmm3 = speed_y

    ; Add speed_y to y
    addss xmm2, xmm3     ; xmm2 = y + speed_y

    ; Store the result back into y
    movss [rdx], xmm2    ; y = xmm2

    ret