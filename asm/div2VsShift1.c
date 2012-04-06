/* even with no opts (-O0), the code generated 
 * for shift1 and div2 is _exactly_ the same:
    
    Dump of assembler code for function div2:
      0x08048354 <div2+0>:    push   %ebp
      0x08048355 <div2+1>:    mov    %esp,%ebp
      0x08048357 <div2+3>:    sub    $0x10,%esp
      0x0804835a <div2+6>:    mov    0x8(%ebp),%edx
      0x0804835d <div2+9>:    mov    %edx,%eax
      0x0804835f <div2+11>:   shr    $0x1f,%eax
      0x08048362 <div2+14>:   add    %edx,%eax
      0x08048364 <div2+16>:   sar    %eax
      0x08048366 <div2+18>:   mov    %eax,0xfffffffc(%ebp)
      0x08048369 <div2+21>:   leave  
      0x0804836a <div2+22>:   ret    
      End of assembler dump.

    Dump of assembler code for function div2:
      0x08048354 <div2+0>:    push   %ebp
      0x08048355 <div2+1>:    mov    %esp,%ebp
      0x08048357 <div2+3>:    sub    $0x10,%esp
      0x0804835a <div2+6>:    mov    0x8(%ebp),%edx
      0x0804835d <div2+9>:    mov    %edx,%eax
      0x0804835f <div2+11>:   shr    $0x1f,%eax
      0x08048362 <div2+14>:   add    %edx,%eax
      0x08048364 <div2+16>:   sar    %eax
      0x08048366 <div2+18>:   mov    %eax,0xfffffffc(%ebp)
      0x08048369 <div2+21>:   leave  
      0x0804836a <div2+22>:   ret    
      End of assembler dump.

 */

void shift1(int x){
  int y = x >> 1;
}

void div2(int x){
  int y = x / 2;
}

int main(){

  int y;

  shift1(y);
  div2(y);

  return 0;
}

