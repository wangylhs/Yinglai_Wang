.text
	.globl	strlength
	.type	strlength, @function
strlength:						# int strlen(char *s)
movq	%rdi, %rax				# char *p = s
whileStart:
	cmpb	$0, (%rax)			# while(*p)
	je whileEnd
	incq 	%rax				# p++;
	jmp	whileStart
whileEnd:
	subq	%rdi, %rax			# return p - s;
	ret
