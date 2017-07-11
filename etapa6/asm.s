## VARIAVEIS_GLOBAIS
	.globl b
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	15
## VARIAVEIS_GLOBAIS
	.globl a
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	0
## TAC_FUNCPUSH
.labbbbellski0:
	.string "kkk"
.labbbbellski1:
	.string "%d"
	.globl	main
	.type	main, @function
main:
.labbbbellski2:
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
## TAC_PRINT
	movl	a(%rip), %eax
	movl	%eax, %esi
	movl	$.labbbbellski1, %edi
	movl	$0, %eax
	call	printf
## TAC_FUNCPOP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.labbbbellski3:
	.size	main, .-main
