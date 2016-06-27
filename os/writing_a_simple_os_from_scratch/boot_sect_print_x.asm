;
; A simple boot sector program that demonstrates addressing
;

[org 0x7c00]           ; Applies this offset to label references

mov ah, 0x0e           ; int 10/ah = 0eh -> scrolling teletype bios routine

; First attempt
mov al, the_secret
int 0x10

; Second attempt
mov al, [the_secret]
int 0x10

; Third attempt
mov bx, the_secret
add bx, 0x7c00
mov al, [bx]
int 0x10

; Fourth attempt
mov al, [0x7c1d]
int 0x10

jmp $                  ; jump to current address

the_secret:
    db "X"

times 510-($-$$) db 0; ; Fill up with zeros. $ is the address right before this
                       ; instruction. $$ is the address of this section.
dw 0xaa55
