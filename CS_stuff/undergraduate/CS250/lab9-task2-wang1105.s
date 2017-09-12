.data
	.comm	length, 8, 8
	str1: .string	"Please enter integers\n"
	str2: .string	"Sum = %d\n"
	str3: .string	"%d"

.text
	.globl main
	.type main, @function
main:
	movl	$str1, %edi 			# set first prameter
	movq	$0, %rax     			# printf needs 0 in %rax
	call	printf      			# printf("Please enter integers\n");
	movq	$0, length(%rip)		# length = 0;
while_in_main:
	pushq	$0						# push to make space for new coming interger
	movq	$str3, %rdi				# set first parameter
	movq	%rsp, %rsi				# set second parameter
	movl	$0, %eax				# scanff needs 0 in %rax
	call	scanf					# call scanf("%d",&a)
	cmpl	$0, (%rsp)				# check a != 0
	je	after_while_in_main
	incq	length(%rip)			# length++;
	jmp	while_in_main

after_while_in_main:
	movq	$0, %rsi				# sum = 0
	popq	%rax					# pop 0 from stack
before_while_in_sum:
	cmpq	$0, length(%rip)		# while(length) {
	je after_while_in_sum
	popq	%rdi					# pop A[length-1]
	addq	%rdi, %rsi				# sum += A[length-1];
	decq	length(%rip)			# length--;
	jmp before_while_in_sum
after_while_in_sum:
	movq	$str2, %rdi				# %edi = "Sum = %d\n"
	call	printf					# printf("Sum = %d\n", sum);
	ret

