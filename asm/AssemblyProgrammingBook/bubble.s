.section .data
  values: .int 3, 12, 45, 1, 0, 12, 46, 51, 77, 8

.section .text
.globl main

main:
  movl $9, %edx

outer:
  dec %edx
  jz out
  movl $0, %ebx
  movl $values, %esi
inner:
  movl (%esi), %ecx
  cmp %ecx, 4(%esi) /* if values[i] <= values[i+1] ... */
  jg skip          /* skip (the jmp condition is the negation of what'd fit in
                      the middle of the cmp arguments */
  xchg %ecx, 4(%esi) /* else ( > ), xchange */
  movl %ecx, (%esi)
skip:
  inc %ebx
  addl $4, %esi
  cmp %ebx, %edx
  jge inner
  jmp outer

out:
  pushl $0
  call exit
  


