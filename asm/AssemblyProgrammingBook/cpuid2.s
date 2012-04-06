.section .data
output:
  .asciz "The procs Vendor Id is '%s'\n"
.section .bss #null-initialized buffers
  .lcomm buffer, 12 #local common memory area

.section .text
.globl _start

_start: 
  movl $0, %eax
  cpuid
  movl $buffer, %edi
  movl %ebx, (%edi)
  movl %edx, 4(%edi)
  movl %ecx, 8(%edi)

  pushl $buffer
  pushl $output
  call printf
  addl $8, %esp
  pushl $0
  call exit

