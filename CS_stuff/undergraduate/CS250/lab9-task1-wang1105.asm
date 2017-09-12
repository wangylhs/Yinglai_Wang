	.text
	.globl	main
main:
	li	$t1, 0					#initialize sum to 0
	li	$t2, 0					#initialize counter to 0
	la	$s0, array				#load array address to $s0
	
	Read:
		li		$v0, 4				#remind user to input
		la		$a0, inputmsg	
		syscall
		li		$v0, 5				#read int from input
		syscall				
		beq		$v0, 0, ReadFinish	#if input==0, ReadFinish
		sw		$v0, 0($s0)			#save input in array
		addi	$s0, $s0, 4			#increment memory location
		addi	$t2, $t2, 1			#increment counter
		j		Read

	ReadFinish:
		beq		$t2, 0, Exit
		la		$s1, array			#$s1 is the head address of array
	getSum:
		lw		$t0, 0($s1)		#$t0 = array's current address element
		add		$t1, $t1, $t0	#sum += $t0
		addi	$s1, $s1, 4		#increment current address of array
		beq		$s1, $s0, Print #if current address == $s0, Print
		j		getSum			#otherwise getSum
	Print:
		li		$v0, 4
		la		$a0, outputmsg
		syscall
		li		$v0, 1				#print sum
		move	$a0, $t1
		syscall
	Exit:
		li	$v0, 10
		syscall
	.data
array:		.space	400
inputmsg:	.asciiz	"Enter integer: "
outputmsg:	.asciiz	"Sum of inputs is: "
