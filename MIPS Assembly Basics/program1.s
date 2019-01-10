# program1

.data
	stringPrompt: .asciiz "Enter String (under 100 characters): "
	charPrompt: .asciiz "Enter Character: "
	newLine: .asciiz "\n"
	string: .space 100
	char: .space 2
	output1: .asciiz "Character "
	output2: .asciiz " occurs in string "
	output3: .asciiz " times"
	
.text
main:	
	la $a0, stringPrompt	#prompt for string
	li $v0, 4
	syscall
	la $a0, string			#get string input	
	li $a1, 100
	li $v0, 8
	syscall
	
	la $a0, charPrompt		#prompt for char
	li $v0, 4
	syscall
	la $a0, char			#get char input
	li $a1, 2
	li $v0, 8
	syscall
	
	la $t0, string		#store address of string
	lb $t1, ($t0)		#get the first character in string (t0 holds address)
	lb $t2, char		#store the value of char
	li $t3, 0 			#hold number of occurrences
	
loop:
	beq $t1, $zero, quit		#quit if the end of the string is reached
	beq $t1, $t2, count			#go to count if the characters are equal
	j next

count:
	addi $t3, $t3, 1		#add one to the number of occurrences
	j next
	
next:
	addi $t0, $t0, 1	#increment string address
	lb $t1, ($t0)
	j loop 
	
quit:
	la $a0, newLine		#print new lines
	li $v0, 4
	syscall
	syscall
	
	la $a0, output1		#print "Character "
	syscall
	
	la $a0, char		#print the specified character
	syscall
	
	la $a0, output2		#print "occurs in string "
	syscall
	
	la $a0, string		#print the specified string
	syscall
	
	move $a0, $t3		#print the number of occurrences
	li $v0, 1
	syscall
	
	la $a0, output3		#print " times"
	li $v0, 4
	syscall
	
	li $v0, 10		#ends the program
	syscall
	