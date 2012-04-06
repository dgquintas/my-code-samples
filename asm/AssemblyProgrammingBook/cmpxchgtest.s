.section .data
  f: .asciz "src = %x; dst = 0x%x; eax = 0x%x\n"
  src: .int 0xdeadbeef
  dst: .int 0xfabada
.section .text
.globl main

main:
  movl $0xf00, %eax
  movl src, %ebx
  cmpxchgl %ebx, dst /* not moved. but now, eax == dst */
  
  pushl %eax /* save eax: printf (maybe? always?) modifies it */
  pushl %eax
  pushl dst
  pushl %ebx
  pushl $f
  call printf
  addl $16, %esp
  popl %eax /* restore eax */
  
  cmpxchgl %ebx, dst /* now, moved. dst == src */

  pushl %eax
  pushl dst
  pushl %ebx
  pushl $f
  call printf
  addl $16, %esp

 
  pushl $0
  call exit

