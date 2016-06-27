;
; A simple boot sector program that demonstrates the stack
;

mov ah, 0x0e           ; int 10/ah = 0eh -> scrolling teletype bios routine

mov bp, 0x8000         ; set the base of the stack a little above where the bios
mov sp, bp             ; loads our boot sector - so it won't ovewrite us

push 'A'               ; note: pushed as 16 bit values.
push 'B'
push 'C'

pop bx                 ; likewise, only 16 bit values are popped.
mov al, bl             ; move only the lower 8 from bl onto al
int 0x10               ; print(al)

pop bx
mov al, bl
int 0x10

mov al, [0x7ffe]       ; to prove our stack grows downwards from bp, fetch the
                       ; char at 0x8000 - 0x2 (ie, 16 bits)
int 0x10

jmp $                  ; jump to current address

times 510-($-$$) db 0; ; Fill up with zeros. $ is the address right before this
                       ; instruction. $$ is the address of this section.
dw 0xaa55
