/* Different instructions are used depending on whether the vrble to 
 * shift is signed:
 *
 * Dump of assembler code for function sign:
 * 0x08048356 <sign+0>:    push   %ebp
 * 0x08048357 <sign+1>:    mov    %esp,%ebp
 * 0x08048359 <sign+3>:    sub    $0x10,%esp
 * 0x0804835c <sign+6>:    movl   $0x29a,0xfffffffc(%ebp)
 * 0x08048363 <sign+13>:   sarl   0xfffffffc(%ebp)          <----
 * 0x08048366 <sign+16>:   leave  
 * 0x08048367 <sign+17>:   ret    
 * End of assembler dump.
 * (gdb) disass unsign
 * Dump of assembler code for function unsign:
 * 0x08048344 <unsign+0>:  push   %ebp
 * 0x08048345 <unsign+1>:  mov    %esp,%ebp
 * 0x08048347 <unsign+3>:  sub    $0x10,%esp
 * 0x0804834a <unsign+6>:  movl   $0x29a,0xfffffffc(%ebp)
 * 0x08048351 <unsign+13>: shrl   0xfffffffc(%ebp)         <----
 * 0x08048354 <unsign+16>: leave  
 * 0x08048355 <unsign+17>: ret
 *
 * Shift *arithmetic* (signed) vs Shift *logical* (unsigned) 
 */


void unsign(){
  unsigned int u=666;
  u >>= 1;
}
void sign(){
  int s=666;
  s >>= 1;
}


int main(){
  unsign();
  sign();

  return 0;
}
