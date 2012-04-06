.section .data
  data: .int 42
.section .text
.globl main

main:
  pushl data /* the VALUE contained in the data vble */
  pushl $data /* ie, where's the data vble content stored */

  popl %eax
  popl %eax

out:
  pushl $0
  call exit
  


