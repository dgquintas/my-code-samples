;
; A simple boot sector that prints a message to the screen using a bios routine
;

mov ah, 0x0e           ; int 10/ah = 0eh -> scrolling teletype bios routine

mov al, 'H'
int 0x10
mov al, 'o'
int 0x10
mov al, 'l'
int 0x10
mov al, 'a'
int 0x10
mov al, ' '
int 0x10
mov al, 'm'
int 0x10
mov al, 'u'
int 0x10
mov al, 'n'
int 0x10
mov al, 'd'
int 0x10
mov al, 'o'
int 0x10

jmp $                  ; jump to current address


times 510-($-$$) db 0; ; Fill up with zeros. $ is the address right before this
                       ; instruction. $$ is the address of this section.
dw 0xaa55
