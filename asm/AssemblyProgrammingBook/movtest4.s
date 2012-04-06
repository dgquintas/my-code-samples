.section .data
values:
  .int 10,20,30,40,50

.section .text
.globl main

main:
  movl values, %eax
  movl $values, %edi
  movl $100, 4(%edi)
  movl $1, %edi
  movl values(, %edi, 4), %ebx
  movl $1, %eax
  int $0x80

