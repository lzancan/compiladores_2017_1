	.file	"exemplo.c"
	.globl	a
	.data
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	2
	.comm	vaidasim,4,4
	.text
	.globl	fun
	.type	fun, @function
fun:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	a, %eax
	addl	$1, %eax
	popl	%ebp
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE0:
	.size	fun, .-fun
	.section	.rodata
.LC0:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$16, %esp
	movl	$.LC0, %eax
	movl	$a, 4(%esp)
	movl	%eax, (%esp)
	call	__isoc99_scanf
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
