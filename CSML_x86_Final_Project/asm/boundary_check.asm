section .note.GNU-stack

section .data
    neg_one dd -1                ; Constant for multiplying by -1

section .text
    global boundary_check

boundary_check:
    ; Parameters:
    ; rdi -> address of y (float*)
    ; rsi -> address of radius (float*)
    ; rdx -> address of speed_y (float*)

    ; Load y and radius
    movss xmm0, dword [rdi]      ; Load *y into xmm0
    movss xmm1, dword [rsi]      ; Load *radius into xmm1

    ; Compute y - radius
    subss xmm0, xmm1             ; xmm0 = y - radius

    ; Compare y - radius <= 0
    xorps xmm2, xmm2             ; xmm2 = 0.0f
    comiss xmm0, xmm2            ; Compare (y - radius) with 0.0f
    ja done                      ; Jump if (y - radius) > 0

    ; Update y to radius
    movss xmm0, xmm1             ; xmm0 = *radius
    movss dword [rdi], xmm0      ; *y = radius

    ; Invert speed_y
    movss xmm0, dword [rdx]      ; Load *speed_y
    mulss xmm0, dword [rel neg_one] ; Multiply by -1
    movss dword [rdx], xmm0      ; Store inverted *speed_y

done:
    ret
