.section .data
output:
  .asciz "the value is %d\n"
values:
  .int 10,20,30,40,50,60,70

.section .text
.globl main 

main:
  nop
  movl $0, %edi

loop:
  pushl values(, %edi, 4)
  pushl $output
  call printf
  inc %edi
  cmpl $7, %edi
  jnz loop

  movl $1, %eax
  movl $0, %ebx
  int $0x80
    


