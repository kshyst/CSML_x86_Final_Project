section .text
    global adder
adder:
    movss xmm1, dword [rdi]    ; Load the current value from *variable
    addss xmm1, xmm0           ; Add the constant value in xmm0
    movss dword [rdi], xmm1    ; Store the updated value back to *variable
    ret
