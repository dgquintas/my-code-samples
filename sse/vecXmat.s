	.file	"vecXmat.cpp"
	.section	.ctors,"aw",@progbits
	.align 4
	.long	_GLOBAL__I_main
	.text
	.align 2
	.p2align 4,,15
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2128:
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	subl	$24, %esp
.LCFI2:
	decl	%eax
	je	.L7
.L5:
	leave
	ret
	.p2align 4,,7
.L7:
	cmpl	$65535, %edx
	jne	.L5
	movl	$_ZSt8__ioinit, (%esp)
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	xorl	%eax, %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$__tcf_0, (%esp)
	call	__cxa_atexit
	leave
	ret
.LFE2128:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
.globl __gxx_personality_v0
	.align 2
	.p2align 4,,15
	.type	_GLOBAL__I_main, @function
_GLOBAL__I_main:
.LFB2130:
	pushl	%ebp
.LCFI3:
	movl	$65535, %edx
	movl	%esp, %ebp
.LCFI4:
	movl	$1, %eax
	popl	%ebp
	jmp	_Z41__static_initialization_and_destruction_0ii
.LFE2130:
	.size	_GLOBAL__I_main, .-_GLOBAL__I_main
	.align 2
	.p2align 4,,15
	.type	__tcf_0, @function
__tcf_0:
.LFB2129:
	pushl	%ebp
.LCFI5:
	movl	%esp, %ebp
.LCFI6:
	movl	$_ZSt8__ioinit, 8(%ebp)
	popl	%ebp
	jmp	_ZNSt8ios_base4InitD1Ev
.LFE2129:
	.size	__tcf_0, .-__tcf_0
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"vecXmat.cpp"
.LC1:
	.string	"(((int)ret) % A) == 0"
	.section	.text._ZN7MyAllocIfLi16EE8allocateEjPKv,"axG",@progbits,_ZN7MyAllocIfLi16EE8allocateEjPKv,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN7MyAllocIfLi16EE8allocateEjPKv
	.type	_ZN7MyAllocIfLi16EE8allocateEjPKv, @function
_ZN7MyAllocIfLi16EE8allocateEjPKv:
.LFB2011:
	pushl	%ebp
.LCFI7:
	movl	%esp, %ebp
.LCFI8:
	subl	$40, %esp
.LCFI9:
	movl	12(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 8(%esp)
	movl	$16, %eax
	movl	%eax, 4(%esp)
	leal	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	posix_memalign
	xorl	%edx, %edx
	testl	%eax, %eax
	jne	.L15
	movl	-4(%ebp), %edx
	testb	$15, %dl
	jne	.L18
.L15:
	leave
	movl	%edx, %eax
	ret
.L18:
	movl	$_ZZN7MyAllocIfLi16EE8allocateEjPKvE19__PRETTY_FUNCTION__, %eax
	movl	$.LC0, %ecx
	movl	%eax, 12(%esp)
	movl	$58, %eax
	movl	%eax, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	$.LC1, (%esp)
	call	__assert_fail
.LFE2011:
	.size	_ZN7MyAllocIfLi16EE8allocateEjPKv, .-_ZN7MyAllocIfLi16EE8allocateEjPKv
	.section	.rodata.str1.1
.LC2:
	.string	"vector::_M_insert_aux"
	.section	.text._ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf,"axG",@progbits,_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf
	.type	_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf, @function
_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf:
.LFB1952:
	pushl	%ebp
.LCFI10:
	movl	%esp, %ebp
.LCFI11:
	pushl	%edi
.LCFI12:
	pushl	%esi
.LCFI13:
	pushl	%ebx
.LCFI14:
	subl	$60, %esp
.LCFI15:
	movl	8(%ebp), %edi
	movl	12(%ebp), %esi
	movl	16(%ebp), %ebx
	movl	4(%edi), %edx
	cmpl	8(%edi), %edx
	je	.L20
	testl	%edx, %edx
	je	.L22
	movl	-4(%edx), %eax
	movl	%eax, (%edx)
.L22:
	leal	4(%edx), %eax
	movl	(%ebx), %ebx
	movl	%eax, 4(%edi)
	leal	-4(%edx), %eax
	subl	%esi, %eax
	andl	$-4, %eax
	subl	%eax, %edx
	movl	%esi, 4(%esp)
	movl	%eax, 8(%esp)
	movl	%edx, (%esp)
	call	memmove
	movl	%ebx, (%esi)
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
.L20:
	movl	%edx, %eax
	movl	(%edi), %edx
	subl	%edx, %eax
	sarl	$2, %eax
	cmpl	$1073741823, %eax
	je	.L60
	testl	%eax, %eax
	movl	$1, %edx
	je	.L30
	leal	(%eax,%eax), %edx
	cmpl	%eax, %edx
	movl	$-4, -32(%ebp)
	jae	.L30
	.p2align 4,,15
.L32:
	movl	-32(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$16, %eax
	movl	%eax, 4(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	posix_memalign
	testl	%eax, %eax
	jne	.L33
	movl	-16(%ebp), %edx
	testb	$15, %dl
	movl	%edx, -40(%ebp)
	jne	.L35
	addl	$4, %edx
	movl	%edx, -36(%ebp)
	movl	-40(%ebp), %edx
.L37:
	movl	(%edi), %eax
	movl	%eax, -44(%ebp)
	movl	-40(%ebp), %eax
	cmpl	%esi, -44(%ebp)
	je	.L40
	movl	-44(%ebp), %ecx
	movl	%eax, %edx
	.p2align 4,,15
.L41:
	testl	%edx, %edx
	je	.L42
	movl	(%ecx), %eax
	movl	%eax, (%edx)
.L42:
	addl	$4, %ecx
	addl	$4, %edx
	cmpl	%esi, %ecx
	jne	.L41
	movl	%edx, %eax
	leal	4(%edx), %edx
	movl	%edx, -36(%ebp)
	movl	%eax, %edx
.L40:
	testl	%eax, %eax
	je	.L45
	movl	(%ebx), %eax
	movl	%eax, (%edx)
.L45:
	movl	4(%edi), %ebx
	cmpl	%esi, %ebx
	je	.L47
	movl	-36(%ebp), %edx
	movl	%esi, %ecx
	.p2align 4,,15
.L49:
	testl	%edx, %edx
	je	.L50
	movl	(%ecx), %eax
	movl	%eax, (%edx)
.L50:
	addl	$4, %ecx
	addl	$4, %edx
	cmpl	%ecx, %ebx
	jne	.L49
	movl	%edx, -36(%ebp)
.L47:
	movl	-44(%ebp), %ecx
	testl	%ecx, %ecx
	je	.L53
	movl	-44(%ebp), %eax
	movl	%eax, (%esp)
	call	free
.L53:
	movl	-40(%ebp), %edx
	movl	-36(%ebp), %eax
	movl	%edx, (%edi)
	movl	%eax, 4(%edi)
	movl	%edx, %eax
	movl	-32(%ebp), %edx
	addl	%edx, %eax
	movl	%eax, 8(%edi)
	addl	$60, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.L30:
	sall	$2, %edx
	movl	%edx, -32(%ebp)
	jmp	.L32
.L33:
	xorl	%edx, %edx
	movl	$0, -40(%ebp)
	movl	$4, -36(%ebp)
	jmp	.L37
.L60:
	movl	$.LC2, (%esp)
	call	_ZSt20__throw_length_errorPKc
.L35:
	movl	$_ZZN7MyAllocIfLi16EE8allocateEjPKvE19__PRETTY_FUNCTION__, %edi
	movl	$58, %esi
	movl	$.LC0, %ebx
	movl	%edi, 12(%esp)
	movl	%esi, 8(%esp)
	movl	%ebx, 4(%esp)
	movl	$.LC1, (%esp)
	call	__assert_fail
.LFE1952:
	.size	_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf, .-_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf
	.section	.rodata.str1.1
.LC12:
	.string	"\t"
.LC13:
	.string	"vector::_M_range_check"
.LC14:
	.string	"-----------------------------"
.globl _Unwind_Resume
	.text
	.align 2
	.p2align 4,,15
.globl main
	.type	main, @function
main:
.LFB1904:
	leal	4(%esp), %ecx
.LCFI16:
	andl	$-16, %esp
	pushl	-4(%ecx)
.LCFI17:
	movl	$16, %eax
	pushl	%ebp
.LCFI18:
	movl	%esp, %ebp
.LCFI19:
	pushl	%ebx
.LCFI20:
	pushl	%ecx
.LCFI21:
	subl	$96, %esp
.LCFI22:
	movl	$0, -56(%ebp)
	movl	$0, -52(%ebp)
	movl	$0, -48(%ebp)
	movl	$0, -68(%ebp)
	movl	$0, -64(%ebp)
	movl	$0, -60(%ebp)
	movl	$0, -80(%ebp)
	movl	$0, -76(%ebp)
	movl	$0, -72(%ebp)
	movl	%eax, 8(%esp)
	movl	$16, %eax
	movl	%eax, 4(%esp)
	leal	-44(%ebp), %eax
	movl	%eax, (%esp)
	call	posix_memalign
	testl	%eax, %eax
	jne	.L62
	movl	-44(%ebp), %eax
	testb	$15, %al
	jne	.L64
	leal	16(%eax), %edx
	testl	%eax, %eax
	movl	%eax, -80(%ebp)
	movl	%edx, -72(%ebp)
	je	.L169
	movl	$0x00000000, (%eax)
	jmp	.L169
	.p2align 4,,7
.L62:
	xorl	%eax, %eax
	movl	$16, %edx
	movl	$0, -80(%ebp)
	movl	$16, -72(%ebp)
.L169:
	movl	%edx, -76(%ebp)
	movl	-52(%ebp), %edx
	cmpl	-48(%ebp), %edx
	movl	$0x00000000, 4(%eax)
	movl	$0x00000000, 8(%eax)
	movl	$0x00000000, 12(%eax)
	movl	$0x3f8ccccd, %eax
	movl	%eax, -40(%ebp)
	je	.L74
	testl	%edx, %edx
	je	.L76
	movl	%eax, (%edx)
.L76:
	leal	4(%edx), %eax
	movl	%eax, -52(%ebp)
.L78:
	movl	-52(%ebp), %edx
	movl	$0x40066666, %eax
	cmpl	-48(%ebp), %edx
	movl	%eax, -36(%ebp)
	je	.L79
	testl	%edx, %edx
	je	.L81
	movl	%eax, (%edx)
.L81:
	leal	4(%edx), %eax
	movl	%eax, -52(%ebp)
.L83:
	movl	-52(%ebp), %edx
	movl	$0x40466666, %eax
	cmpl	-48(%ebp), %edx
	movl	%eax, -32(%ebp)
	je	.L84
	testl	%edx, %edx
	je	.L86
	movl	%eax, (%edx)
.L86:
	leal	4(%edx), %eax
	movl	%eax, -52(%ebp)
.L88:
	movl	-52(%ebp), %edx
	movl	$0x40833333, %eax
	cmpl	-48(%ebp), %edx
	movl	%eax, -28(%ebp)
	je	.L89
	testl	%edx, %edx
	je	.L91
	movl	%eax, (%edx)
.L91:
	leal	4(%edx), %eax
	movl	%eax, -52(%ebp)
.L93:
	movl	-64(%ebp), %edx
	movl	$0x3f99999a, %eax
	cmpl	-60(%ebp), %edx
	movl	%eax, -24(%ebp)
	je	.L94
	testl	%edx, %edx
	je	.L96
	movl	%eax, (%edx)
.L96:
	leal	4(%edx), %eax
	movl	%eax, -64(%ebp)
.L98:
	movl	-64(%ebp), %edx
	movl	$0x400ccccd, %eax
	cmpl	-60(%ebp), %edx
	movl	%eax, -20(%ebp)
	je	.L99
	testl	%edx, %edx
	je	.L101
	movl	%eax, (%edx)
.L101:
	leal	4(%edx), %eax
	movl	%eax, -64(%ebp)
.L103:
	movl	-64(%ebp), %edx
	movl	$0x404ccccd, %eax
	cmpl	-60(%ebp), %edx
	movl	%eax, -16(%ebp)
	je	.L104
	testl	%edx, %edx
	je	.L106
	movl	%eax, (%edx)
.L106:
	leal	4(%edx), %eax
	movl	%eax, -64(%ebp)
.L108:
	movl	-64(%ebp), %edx
	movl	$0x4083d70a, %eax
	cmpl	-60(%ebp), %edx
	movl	%eax, -12(%ebp)
	je	.L109
	testl	%edx, %edx
	je	.L111
	movl	%eax, (%edx)
.L111:
	leal	4(%edx), %eax
	movl	%eax, -64(%ebp)
.L113:
	movl	-56(%ebp), %edx
	movl	-68(%ebp), %eax
	movaps	(%edx), %xmm0
	mulps	(%eax), %xmm0
#APP
	FOO:
#NO_APP
	movl	-80(%ebp), %eax
	movaps	%xmm0, (%eax)
#APP
	BAR:
#NO_APP
	movl	-52(%ebp), %eax
	subl	%edx, %eax
	shrl	$2, %eax
	je	.L138
	movl	(%edx), %eax
	movl	$_ZSt4cout, (%esp)
	movl	%eax, 4(%esp)
.LEHB0:
	call	_ZNSolsEf
	movl	$.LC12, %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	-56(%ebp), %edx
	movl	-52(%ebp), %eax
	subl	%edx, %eax
	sarl	$2, %eax
	cmpl	$1, %eax
	jbe	.L138
	movl	4(%edx), %eax
	movl	$_ZSt4cout, (%esp)
	movl	%eax, 4(%esp)
	call	_ZNSolsEf
	movl	$.LC12, %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	-56(%ebp), %edx
	movl	-52(%ebp), %eax
	subl	%edx, %eax
	sarl	$2, %eax
	cmpl	$2, %eax
	jbe	.L138
	movl	8(%edx), %eax
	movl	$_ZSt4cout, (%esp)
	movl	%eax, 4(%esp)
	call	_ZNSolsEf
	movl	$.LC12, %ebx
	movl	%ebx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	-56(%ebp), %edx
	movl	-52(%ebp), %eax
	subl	%edx, %eax
	sarl	$2, %eax
	cmpl	$3, %eax
	jbe	.L138
	movl	12(%edx), %eax
	movl	$_ZSt4cout, (%esp)
	movl	%eax, 4(%esp)
	call	_ZNSolsEf
	movl	$.LC12, %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4cout, (%esp)
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	movl	-68(%ebp), %edx
	movl	-64(%ebp), %eax
	subl	%edx, %eax
	shrl	$2, %eax
	je	.L138
	movl	(%edx), %eax
	movl	$_ZSt4cout, (%esp)
	movl	%eax, 4(%esp)
	call	_ZNSolsEf
	movl	$.LC12, %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	-68(%ebp), %edx
	movl	-64(%ebp), %eax
	subl	%edx, %eax
	sarl	$2, %eax
	cmpl	$1, %eax
	jbe	.L138
	movl	4(%edx), %eax
	movl	$_ZSt4cout, (%esp)
	movl	%eax, 4(%esp)
	call	_ZNSolsEf
	movl	$.LC12, %ebx
	movl	%ebx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	-68(%ebp), %edx
	movl	-64(%ebp), %eax
	subl	%edx, %eax
	sarl	$2, %eax
	cmpl	$2, %eax
	jbe	.L138
	movl	8(%edx), %eax
	movl	$_ZSt4cout, (%esp)
	movl	%eax, 4(%esp)
	call	_ZNSolsEf
	movl	$.LC12, %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	-68(%ebp), %edx
	movl	-64(%ebp), %eax
	subl	%edx, %eax
	sarl	$2, %eax
	cmpl	$3, %eax
	jbe	.L138
	movl	12(%edx), %eax
	movl	$_ZSt4cout, (%esp)
	movl	%eax, 4(%esp)
	call	_ZNSolsEf
	movl	$.LC12, %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4cout, (%esp)
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	movl	$.LC14, %ebx
	movl	%ebx, 4(%esp)
	movl	$_ZSt4cout, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%eax, (%esp)
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	movl	-80(%ebp), %edx
	movl	-76(%ebp), %eax
	subl	%edx, %eax
	shrl	$2, %eax
	je	.L138
	movl	(%edx), %eax
	movl	$_ZSt4cout, (%esp)
	movl	%eax, 4(%esp)
	call	_ZNSolsEf
	movl	$.LC12, %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	-80(%ebp), %edx
	movl	-76(%ebp), %eax
	subl	%edx, %eax
	sarl	$2, %eax
	cmpl	$1, %eax
	jbe	.L138
	movl	4(%edx), %eax
	movl	$_ZSt4cout, (%esp)
	movl	%eax, 4(%esp)
	call	_ZNSolsEf
	movl	$.LC12, %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	-80(%ebp), %edx
	movl	-76(%ebp), %eax
	subl	%edx, %eax
	sarl	$2, %eax
	cmpl	$2, %eax
	jbe	.L138
	movl	8(%edx), %eax
	movl	$_ZSt4cout, (%esp)
	movl	%eax, 4(%esp)
	call	_ZNSolsEf
	movl	$.LC12, %ebx
	movl	%ebx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	-80(%ebp), %edx
	movl	-76(%ebp), %eax
	subl	%edx, %eax
	sarl	$2, %eax
	cmpl	$3, %eax
	jbe	.L138
	movl	12(%edx), %eax
	movl	$_ZSt4cout, (%esp)
	movl	%eax, 4(%esp)
	call	_ZNSolsEf
	movl	$.LC12, %ecx
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4cout, (%esp)
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	movl	-80(%ebp), %eax
	testl	%eax, %eax
	je	.L150
	movl	%eax, (%esp)
	call	free
.L150:
	movl	-68(%ebp), %eax
	testl	%eax, %eax
	je	.L153
	movl	%eax, (%esp)
	call	free
.L153:
	movl	-56(%ebp), %eax
	testl	%eax, %eax
	je	.L161
	movl	%eax, (%esp)
	call	free
.L161:
	addl	$96, %esp
	xorl	%eax, %eax
	popl	%ecx
	popl	%ebx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.p2align 4,,7
.L138:
	movl	$.LC13, (%esp)
	call	_ZSt20__throw_out_of_rangePKc
.L109:
	leal	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-68(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf
	jmp	.L113
.L74:
	leal	-40(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-56(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf
	jmp	.L78
.L99:
	leal	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-68(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf
	jmp	.L103
.L104:
	leal	-16(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-68(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf
	jmp	.L108
.L79:
	leal	-36(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-56(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf
	jmp	.L83
.L84:
	leal	-32(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-56(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf
	jmp	.L88
.L89:
	leal	-28(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-56(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf
	jmp	.L93
.L94:
	leal	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-68(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_ZNSt6vectorIf7MyAllocIfLi16EEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPfS2_EERKf
.LEHE0:
	jmp	.L98
.L64:
	movl	$_ZZN7MyAllocIfLi16EE8allocateEjPKvE19__PRETTY_FUNCTION__, %eax
	movl	$.LC0, %ebx
	movl	%eax, 12(%esp)
	movl	$58, %eax
	movl	%eax, 8(%esp)
	movl	%ebx, 4(%esp)
	movl	$.LC1, (%esp)
	call	__assert_fail
.L166:
.L154:
	movl	%eax, %ebx
	movl	-80(%ebp), %eax
	testl	%eax, %eax
	je	.L155
	movl	%eax, (%esp)
	call	free
.L155:
.L167:
.L157:
	movl	-68(%ebp), %eax
	testl	%eax, %eax
	je	.L158
	movl	%eax, (%esp)
	call	free
.L168:
.L158:
.L162:
	movl	-56(%ebp), %eax
	testl	%eax, %eax
	je	.L163
	movl	%eax, (%esp)
	call	free
.L163:
	movl	%ebx, (%esp)
.LEHB1:
	call	_Unwind_Resume
.LEHE1:
.LFE1904:
	.size	main, .-main
	.section	.gcc_except_table,"a",@progbits
.LLSDA1904:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1904-.LLSDACSB1904
.LLSDACSB1904:
	.uleb128 .LEHB0-.LFB1904
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L166-.LFB1904
	.uleb128 0x0
	.uleb128 .LEHB1-.LFB1904
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0x0
	.uleb128 0x0
.LLSDACSE1904:
	.text
	.local	_ZSt8__ioinit
	.comm	_ZSt8__ioinit,1,1
	.section	.rodata
	.align 32
	.type	_ZZN7MyAllocIfLi16EE8allocateEjPKvE19__PRETTY_FUNCTION__, @object
	.size	_ZZN7MyAllocIfLi16EE8allocateEjPKvE19__PRETTY_FUNCTION__, 77
_ZZN7MyAllocIfLi16EE8allocateEjPKvE19__PRETTY_FUNCTION__:
	.string	"T* MyAlloc<T, A>::allocate(size_t, const void*) [with T = float, int A = 16]"
	.weakref	_Z20__gthrw_pthread_oncePiPFvvE,pthread_once
	.weakref	_Z27__gthrw_pthread_getspecificj,pthread_getspecific
	.weakref	_Z27__gthrw_pthread_setspecificjPKv,pthread_setspecific
	.weakref	_Z22__gthrw_pthread_createPmPK16__pthread_attr_sPFPvS3_ES3_,pthread_create
	.weakref	_Z22__gthrw_pthread_cancelm,pthread_cancel
	.weakref	_Z26__gthrw_pthread_mutex_lockP15pthread_mutex_t,pthread_mutex_lock
	.weakref	_Z29__gthrw_pthread_mutex_trylockP15pthread_mutex_t,pthread_mutex_trylock
	.weakref	_Z28__gthrw_pthread_mutex_unlockP15pthread_mutex_t,pthread_mutex_unlock
	.weakref	_Z26__gthrw_pthread_mutex_initP15pthread_mutex_tPK19pthread_mutexattr_t,pthread_mutex_init
	.weakref	_Z26__gthrw_pthread_key_createPjPFvPvE,pthread_key_create
	.weakref	_Z26__gthrw_pthread_key_deletej,pthread_key_delete
	.weakref	_Z30__gthrw_pthread_mutexattr_initP19pthread_mutexattr_t,pthread_mutexattr_init
	.weakref	_Z33__gthrw_pthread_mutexattr_settypeP19pthread_mutexattr_ti,pthread_mutexattr_settype
	.weakref	_Z33__gthrw_pthread_mutexattr_destroyP19pthread_mutexattr_t,pthread_mutexattr_destroy
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	"zPL"
	.uleb128 0x1
	.sleb128 -4
	.byte	0x8
	.uleb128 0x6
	.byte	0x0
	.long	__gxx_personality_v0
	.byte	0x0
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x88
	.uleb128 0x1
	.align 4
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB2128
	.long	.LFE2128-.LFB2128
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI0-.LFB2128
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE1:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB1952
	.long	.LFE1952-.LFB1952
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI10-.LFB1952
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI11-.LCFI10
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI15-.LCFI11
	.byte	0x83
	.uleb128 0x5
	.byte	0x86
	.uleb128 0x4
	.byte	0x87
	.uleb128 0x3
	.align 4
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB1904
	.long	.LFE1904-.LFB1904
	.uleb128 0x4
	.long	.LLSDA1904
	.byte	0x4
	.long	.LCFI16-.LFB1904
	.byte	0xc
	.uleb128 0x1
	.uleb128 0x0
	.byte	0x9
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x4
	.long	.LCFI17-.LCFI16
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI18-.LCFI17
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI19-.LCFI18
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI21-.LCFI19
	.byte	0x84
	.uleb128 0x4
	.byte	0x83
	.uleb128 0x3
	.align 4
.LEFDE11:
	.ident	"GCC: (GNU) 4.1.2 20061115 (prerelease) (Debian 4.1.1-21)"
	.section	.note.GNU-stack,"",@progbits
