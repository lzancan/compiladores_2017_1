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
.labbbbellski4:
	.string "%d"
.labbbbellski5:
	.string "%d"
	.text
## TAC_FUNCPUSH
	.globl	main
	.type	main, @function
main:
.labbbbellski6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
## TAC_READ
	movl $a, %esi
	movl $.labbbbellski4, %edi
	movl $0, %eax
	call __isoc99_scanf
## TAC_MOVE
	movl $0, b(%rip)
## TAC_LABEL
.labbbbellski2:
## TAC_LE
	movl b(%rip), %eax
	cmpl $10, %eax
	setle	%al
	movzbl %al, %eax
	movl %eax, temmmmporarryooius3(%rip)
## TAC_IFZ
	movl temmmmporarryooius3(%rip), %eax
	testl %eax, %eax
	je  .labbbbellski3
## TAC_ADD
	movl a(%rip), %edx
	movl b(%rip), %eax
	addl %edx, %eax
	movl %eax, temmmmporarryooius2(%rip)
## TAC_PRINT
	movl	temmmmporarryooius2(%rip), %eax
	movl	%eax, %esi
	movl	$.labbbbellski5, %edi
	movl	$0, %eax
	call	printf
## TAC_INC
	movl b(%rip), %eax
	addl $1, %eax
	movl %eax, b(%rip)
## TAC_GOTO
	jmp  .labbbbellski2
## TAC_LABEL
.labbbbellski3:
## TAC_FUNCPOP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.labbbbellski7:
	.size	main, .-main
