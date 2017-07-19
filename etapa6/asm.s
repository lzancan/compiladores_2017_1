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
.labbbbellski0:
	.string "%d"
.labbbbellski1:
	.string "\n"
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
## TAC_DIV
	movl a(%rip), %eax
	movl b(%rip), %ecx
	cltd
	idivl %ecx
	movl %eax, temmmmporarryooius1(%rip)
## TAC_MOVE
	movl temmmmporarryooius1(%rip), %eax
	movl %eax, a(%rip)
## TAC_PRINT
	movl	a(%rip), %eax
	movl	%eax, %esi
	movl	$.labbbbellski0, %edi
	movl	$0, %eax
	call	printf
## TAC_PRINT
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
