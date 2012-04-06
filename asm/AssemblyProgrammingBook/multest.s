.section .data
  str: .string "Res = %lu\n"

.section .bss
  res: .quad 

.section .text
.globl main

main:
  movl $123123, %eax
  movl $234234, %ebx

  mul %ebx

  movl %eax, res
  movl %edx, res+4

  pushl res
  pushl $str
  call printf

  pushl $0
  call exit



