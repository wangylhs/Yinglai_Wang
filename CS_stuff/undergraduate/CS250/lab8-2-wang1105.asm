	.text
	.globl	main

main:
	li	$s1, 0				#initialize index of array
	li	$t0, 0				#initialize the counter to 0

	Read:	li	$v0, 4					#message that remind user to input
			la	$a0, msg1	
			syscall
			li	$v0, 5				#read int	
			syscall
			beq	$v0, 0, ReadFinish		#if input==0, ReadFinish	
			sw	$v0, array($s1)			#save input into array if input!=0
			addi	$t0, $t0, 1			#counter++
			addiu	$s1, $s1, 4			#index++
			blt	$t0, 20, Read			#if size<20, Read
	

	ReadFinish:	
				li $v0, 4
				la $a0, print			#message before print the sorted array
				syscall
				li $s0, 0			#initialize the index that used to output array
				la $a0, array			#load array address to $a0, $a0 also is the first parameter 
				li $a1, 0			#$a1 = first = 0
				addi $sp, $sp, -8		#create stack frame
				sw $t0, 0($sp)			#save counter t0
				move $a2, $t0
				jal mergesort
				lw $t0, 0($sp)			#sort done, load counter $t0 use for print
				jal Print
				#exit

	Print:	
			ble $t0, 0, printEnd		#if counter<=0, printEnd
			lw $t3, array($s0)		#$t3=array[index]
			addi	$t0, $t0, -1		#counter--
			addi	$s0, $s0, 4		#index--
			li	$v0, 1			#print array value
			move $a0, $t3
			syscall
			
			la	$a0, msg2		#print space between values
			li	$v0, 4
			syscall
			j Print				#loop Print
	printEnd:
			li	$v0, 10			#program end
			syscall

			
	mergesort:
			addi $sp, $sp, -24
			sw $a0, 0($sp)			#array = $a0
			sw $a1, 4($sp)			#first = $a1
			sw $a2, 8($sp)			#n = $a2
			sw $ra, 12($sp)			#save $ra

			ble $a2, 1, mergesortReturn		#if (n<1) return;
			srl $a3, $a2, 1			#$a3 = n1 = n / 2
			sw $a3, 16($sp)			#save n1
			sub $t4, $a2, $a3		#$t4 = n2 = n - n1
			sw $t4, 20($sp)			#save n2
			
			move $a0, $a0			#array = array
			move $a1, $a1			#first = first
			move $a2, $a3			# n = n1
			jal mergesort			#call mergesort

			lw $a0, 0($sp)			#restore array
			lw $a1, 4($sp)			#restore first
			lw $a3, 16($sp)			#restore n1
			add $a1, $a1, $a3		#first = first + n1
			lw $a2, 20($sp)			#restore n2
			jal mergesort			#call mergesort

			lw $a0, 0($sp)			#restore array
			lw $a1, 4($sp)			#restore first
			lw $a2, 16($sp)			#restore n1
			lw $a3, 20($sp)			#restore n2		
			jal merge

	mergesortReturn:
			lw $ra, 12($sp)			#restore $ra
			addi $sp, $sp, 24		#destroy stack frame
			jr $ra

	merge:
			sll $a1, $a1, 2			#$a1 = $a1*4
			sll $a2, $a2, 2			#$a2 = $a2*4
			sll $a3, $a3, 2			#$a3 = $a3*4
			li $t4, 0			#index = 0
			li $t5, 0			#index1 = 0
			li $t6, 0			#index2 = 0

	whileStart:
			bge $t5, $a2, whileEnd	#if (index1 >= n1) goto whileEnd;
			bge $t6, $a3, whileEnd	#if (index2 >= n2) goto whileEnd;
			add $t7, $a1, $t5		#$t7 = first + index1			
			lw $t7, array($t7)		#$t7 = array[first + index1]
			add $t8, $a1, $a2		#$t8 = first + n1
			add $t8, $t8, $t6		#$t8 = first + n1 + index2		
			lw $t8, array($t8)		#$t8 = array[first + n1 + index2]

			bgt $t7, $t8, branch2	#if array[first+index1]>array[first+n1+index2]
				sw $t7, temp($t4)	#temp[index] = array[first + index1]
				addi $t4, $t4, 4	#index++
				addi $t5, $t5, 4	#index1++
				j whileStart
			branch2:
				sw $t8, temp($t4)	#temp[index] = array[first + n1 + index2]
				addi $t4, $t4, 4	#index++
				addi $t6, $t6, 4	#index2++	
				j whileStart
	whileEnd:

	whileStart2:
			bge $t5, $a2, whileEnd2	#if (index1 >= n1) goto whileEnd2;
			add $t7, $a1, $t5		#$t7 = first + index1
			lw $t7, array($t7)		#$t7 = array[fisrt + index1]
			sw $t7, temp($t4)		#temp[index] = array[first + index1]
			addi $t4, $t4, 4		#index++
			addi $t5, $t5, 4		#index1++
			j whileStart2
	whileEnd2:			

	whileStart3:
			bge $t6, $a3, whileEnd3	#if (index2 >= n2) goto whileEnd3;
			add $t8, $a1, $a2		#$t8 = first + n1
			add $t8, $t8, $t6		#$t8 = first + n1 + index2
			lw $t8, array($t8)		#$t8 = array[first + n1 + index2]
			sw $t8, temp($t4)		#temp[index] = array[first + n1 + index2]
			addi $t4, $t4, 4		#index++
			addi $t6, $t6, 4		#index2++
			j whileStart3	
	whileEnd3:

	whileStart4:
			ble $t4, 0, whileEnd4
			addi $t4, $t4, -4		#index--
			add $t5, $a1, $t4		#$t5 = first + index
			lw $t6, temp($t4)		#$t6 = temp[index]
			sw $t6, array($t5)		#array[first + index] = a6
			j whileStart4
	whileEnd4:

	jr $ra

	.data
msg1:	.asciiz	"Enter integer: "
msg2:	.asciiz "   "
print:	.asciiz "Sorted array:  "
array:	.space	80
temp:	.space	80
