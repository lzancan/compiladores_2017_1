## VARIAVEIS_GLOBAIS
	.globl a
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	45
	.globl b
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	45
## TAC_FUNCPUSH
	.globl	fun
	.type	fun, @function
fun:
.labbbbellski0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
## TAC_FUNCPOP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.labbbbellski1:
	.size	fun, .-fun
## TAC_FUNCPUSH
	.globl	funct2
	.type	funct2, @function
funct2:
.labbbbellski2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
## TAC_FUNCPOP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.labbbbellski3:
	.size	funct2, .-funct2
## TAC_FUNCPUSH
	.globl	main
	.type	main, @function
main:
.labbbbellski4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
## TAC_CALLFUNC
	movl	$0, %eax
	call	fun
## TAC_MOVE_VETOR
	movl	%eax, c+8(%rip)
## TAC_FUNCPOP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.labbbbellski5:
	.size	main, .-main
