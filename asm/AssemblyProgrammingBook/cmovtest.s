.section .data
output:
  .asciz "el maximo es %d"
values:
  .int 2, 43, 12, 434, 31, 3, 1, 35, -13, 1

.section .text
.globl main

main:
  xorl %edi, %edi
  movl values, %ebx
loop:
  movl values( , %edi, 4), %eax
  cmp %ebx, %eax
  cmovg %eax, %ebx
  inc %edi
  cmp $10, %edi
  jnz loop

  pushl %ebx
  pushl $output
  call printf
  addl $8, %esp

  pushl $0
  call exit

