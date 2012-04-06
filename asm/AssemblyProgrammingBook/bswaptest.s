.section .data
  f: .asciz "0x%x vs. 0x%x\n"
  i: .int 0xdeadbeef
.section .text
.globl main

main:
  movl i, %eax
  bswap %eax

  
  pushl %eax
  pushl i
  pushl $f
  call printf
  addl $8, %esp
  
  
  pushl $0
  call exit

