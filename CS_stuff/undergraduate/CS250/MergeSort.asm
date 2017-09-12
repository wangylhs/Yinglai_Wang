	.text


main:
	li	$t0, 0				#initialize the counter to 0
	inputFunction:	li $v0, 4
			la $a0, msg1
			syscall
			li $v0, 5
			syscall
			beq $v0, 0, exitInput
			sw $v0, array($t0)
			add $t0, $t0, 4			
			blt $t0, 80, inputFunction	

	exitInput:
			srl $t0, $t0, 2
			la $a0, array
			move $a1, $t0
			jal mergesort
			li $t1, 0
			sll $t0, $t0, 2
	outputFunction:
			ble $t0, $t1, exitOutput
			lw $t3, array($t1)
			addi $t1, $t1, 4
			li $v0, 1
			move $a0, $t3
			syscall
			la $a0, msg2
			li $v0, 4
			syscall
			j outputFunction
	exitOutput:
			li $v0, 10
			syscall

			
	mergesort:
			addi $sp, $sp, -20
			sw $a0, 0($sp)			#save begin = a0
			sw $a1, 4($sp)			#save num = a1
			sw $ra, 8($sp)			#save $ra

			ble $a1, 1, exitMergesort	#if (num<=1) return;
			sra $a2, $a1, 1			#a2 = num1 = num >> 1
			sw $a2, 12($sp)			#save num1
			
			move $a1, $a2			#num = num1
			jal mergesort			#call mergesort
			lw $a0, 0($sp)			#restore begin
			lw $a1, 4($sp)			#restore num
			lw $a2, 12($sp)			#restore num1
			
			sub $a3, $a1, $a2		#a3 = num2 = num - num1
			sw $a3, 16($sp)			#save num2

			sll $t5, $a2, 2			#t5 = num1 * 4
			add $a0, $a0, $t5		#begin = begin + num1 * 4
			move $a1, $a3			#num = num2
			jal mergesort			#call mergesort

			lw $a0, 0($sp)			#restore begin
			lw $a1, 4($sp)			#restore num
			lw $a2, 12($sp)			#restore num1
			lw $a3, 16($sp)			#restore num2

			#begine merge:
			sll $a2, $a2, 2			
			add $a2, $a2, $a0		#num1 = num1*4 + begin
			sll $a3, $a3, 2	
			add $a3, $a3, $a2		#num2 = num2*4 + num1*4 + begin
			move $t5, $a0			#i = begin
			move $t6, $a2			#j = begin + num1*4
			la $t7, temp			#c = temp

	enterWhile:
			lw $t8, 0($t5)			#t8 = *i
			lw $t9, 0($t6)			#t9 = *j
			bgt $t8, $t9, elseBranch	#if (*i>*j) goto elsebranch;
			sw $t8, 0($t7)			#*c = *i
			add $t7, $t7, 4			#c += 4
			add $t5, $t5, 4			#i += 4
			blt $t5, $a2, enterWhile	#if (i<num1) goto enterwhile;
			append2:
				lw $t9, 0($t6)		#t9 = *j
				sw $t9, 0($t7)		#*c = t9
				add $t7, $t7, 4		#c += 4
				add $t6, $t6, 4		#j += 4
				blt $t6, $a3, append2	#if (j<num2) goto append2;
			j exitWhile
		elseBranch:
			sw $t9, 0($t7)			#*c = *j
			add $t7, $t7, 4			#c += 4
			add $t6, $t6, 4			#j += 4
			blt $t6, $a3, enterWhile	#if (j<num2) goto enterwhile;
			append1:
				lw $t8, 0($t5)		#t8 = *i
				sw $t8, 0($t7)		#*c = t8
				add $t7, $t7, 4		#c += 4
				add $t5, $t5, 4		#i += 4
				blt $t5, $a2, append1	#if (i<num1) goto append1;
	exitWhile:
			add $t7, $t7, -4		#c -= 4
			add $a3, $a3, -4		#num2 -= 4
			lw $t8, 0($t7)			#t8 = *c
			sw $t8, 0($a3)			#*num = t8
			bgt $a3, $a0, exitWhile		#loop until all data is copied

	exitMergesort:
			lw $ra, 8($sp)			#restore $ra
			addi $sp, $sp, 20
			jr $ra

	

	.data
msg1:	.asciiz	"Enter integer: "
msg2:	.asciiz "   "
array:	.space	80
temp:	.space	80
