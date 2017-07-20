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
	.comm	temmmmporarryooius3,4,4
	.comm	temmmmporarryooius0,4,4
	.comm	temmmmporarryooius1,4,4
	.comm	temmmmporarryooius2,4,4
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
	movl $1, %eax
## TAC_FUNCPOP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.labbbbellski1:
	.size	fun, .-fun
.labbbbellski2:
	.string "%d"
.labbbbellski3:
	.string "%d"
.labbbbellski4:
	.string "\n"
	.text
## TAC_FUNCPUSH
	.globl	main
	.type	main, @function
main:
.labbbbellski5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
## TAC_CALLFUNC
	movl	$0, %eax
	call	fun
## TAC_ADD
	addl $1, %eax
	movl %eax, temmmmporarryooius3(%rip)
## TAC_MOVE
	movl temmmmporarryooius3(%rip), %eax
	movl %eax, a(%rip)
## TAC_READ
	movl $a, %esi
	movl $.labbbbellski2, %edi
	movl $0, %eax
	call __isoc99_scanf
## TAC_PRINT
	movl	a(%rip), %eax
	movl	%eax, %esi
	movl	$.labbbbellski3, %edi
	movl	$0, %eax
	call	printf
## TAC_PRINT
	movl	$.labbbbellski4, %edi
	movl	$0, %eax
	call	printf
## TAC_FUNCPOP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.labbbbellski6:
	.size	main, .-main
