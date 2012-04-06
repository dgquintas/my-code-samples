BITS 32

section .data   ; Data segment
msg     db      "Hello world!", 0x0a

section .text
global start

start:

;SYSCALL: write(1, msg, 13)
mov eax, 4
mov ebx, 1
mov ecx, msg
mov edx, 14
int 0x80

; SYSCALL: exit(0)
mov eax, 1
mov ebx, 0
int 0x80
