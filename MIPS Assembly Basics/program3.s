# program3

.data
	nPrompt: .asciiz "Enter the number of integers to use: "
	intPrompt: .asciiz "Enter integer: "
	
	sumOut1: .asciiz "The sum of the "
	sumOut2: .asciiz " integers is "
	maxOut: .asciiz "The maximum value is "
	minOut: .asciiz "The minimum value is "
	newLine: .asciiz "\n"
	
	
	
	.text
	main:
		la $a0, nPrompt		#prompt user for number of integers
		li $v0, 4
		syscall
		li $v0, 5			#read number of integers
		syscall
		move $t0, $v0		#t0 is the number of integers
		la $a0, newLine		#print new line
		li $v0, 4
		syscall
		move $t1, $t0		#$t1 = $t0
		li $t2, 0			#hold sum
		li $t3, 0			#hold max
		li $t4, 0			#hold min
		li $t5, 0			#copy
		li $t6, 1			#hold 1 for subtraction
		
		la $a0, intPrompt	#print "Enter integer "
		li $v0, 4
		syscall
		li $v0, 5			#read integer
		syscall
		move $t5, $v0

		move $t2, $t5		#sum, max, and min equal to first integer
		move $t3, $t5
		move $t4, $t5
		sub $t1, $t1, $t6 	#subtract 1 from $t1
		
	
	inputLoop:
		beqz $t1, quit		#quit if no more integers are needed
		sub $t1, $t1, $t6	#subtract 1 from $t1
		
		la $a0, intPrompt	#print "Enter integer "
		li $v0, 4
		syscall
		li $v0, 5			#read integer
		syscall
		move $t5, $v0
		
		bgt $t5, $t3, replaceMax	#jump to replaceMax if new max is found
		max_ret:
		
		blt $t5, $t4, replaceMin	#jump to replaceMin if new min is found
		min_ret:
		
		add $t2, $t2, $t5			#add integer to the sum
		
		j inputLoop					#jump back to start of the loop
		
	replaceMax:
		move $t3, $t5		#replace the maximum integer with the current
		j max_ret			#jump back to appropriate place in the loop
		
	replaceMin:
		move $t4, $t5		#replace the minimum integer with the current
		j min_ret			#jump back to appropriate place in the loop
	
	quit:
		la $a0, newLine		#print new line
		li $v0, 4
		syscall
		la $a0, sumOut1		#print "The sum of the "
		li $v0, 4
		syscall
		move $a0, $t0 		#print the number of integers
		li $v0, 1
		syscall
		la $a0, sumOut2		#print " integers is "
		li $v0, 4
		syscall
		move $a0, $t2		#print the sum
		li $v0, 1
		syscall
		la $a0, newLine		#print new line
		li $v0, 4
		syscall
		
		la $a0, maxOut		#print "The maximum value is "
		li $v0, 4
		syscall
		move $a0, $t3		#print the max value
		li $v0, 1
		syscall
		la $a0, newLine		#print new line
		li $v0, 4
		syscall
		
		la $a0, minOut		#print "The minimum value is "
		li $v0, 4
		syscall
		move $a0, $t4		#print the min value
		li $v0, 1
		syscall
		la $a0, newLine		#print new line
		li $v0, 4
		syscall
		
		li $v0, 10		#ends the program
		syscall
		
		