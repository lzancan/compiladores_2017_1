## VARIAVEIS_GLOBAIS
	.globl a
	.data
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	10
## VARIAVEIS_GLOBAIS
	.globl b
	.data
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	5
	.comm	temmmmporarryooius0,4,4
	.comm	temmmmporarryooius1,4,4
	.text
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
## TAC_RETURN
	movl $3, %eax
## TAC_FUNCPOP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.labbbbellski1:
	.size	fun, .-fun
	.text
## TAC_FUNCPUSH
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
## TAC_PARAMETRO_CALL
## TAC_PARAMETRO_CALL
## TAC_PARAMETRO_CALL
## TAC_CALLFUNC
	movl	$0, %eax
	call	fun
## TAC_MOVE
	movl temmmmporarryooius1(%rip), %eax
	movl %eax, a(%rip)
## TAC_FUNCPOP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.labbbbellski3:
	.size	main, .-main
