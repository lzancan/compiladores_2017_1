## TAC_FUNCPUSH
.labbbbellski0:
	.string "ok\n"
	.globl	main
	.type	main, @function
main:
.labbbbellski1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
## TAC_PRINT
	movl	$.labbbbellski0, %edi
	movl	$0, %eax
	call	printf
## TAC_FUNCPOP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.labbbbellski2:
	.size	main, .-main
