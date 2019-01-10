# program2

.data
	stringPrompt: .asciiz "Enter String (under 100 characters): "
	charPrompt: .asciiz "Replace character: "
	replacePrompt: .asciiz "With character: "
	newLine: .asciiz "\n"
	string: .space 100
	char: .space 2
	rChar: .space 2
	output1: .asciiz "Original string: "
	output2: .asciiz "Substitute "
	output3: .asciiz " --> "
	output4: .asciiz "Result string: "
	
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
	la $a0, newLine			#print new line
	li $v0, 4
	syscall
	
	la $a0, replacePrompt	#prompt for replacement char
	li $v0, 4
	syscall
	la $a0, rChar			#get rChar input
	li $a1, 2
	li $v0, 8
	syscall
	
	la $t0, string		#store address of string
	lb $t1, ($t0)		#get the first character in string (t0 holds address)
	lb $t2, char		#store the value of char
	lb $t3, rChar		#store replacement character
	
	la $a0, newLine		#print new lines
	li $v0, 4
	syscall
	syscall
	
	la $a0, output1		#print "Original string: "
	syscall
	la $a0, string		#print the specified string
	syscall
	
	la $a0, output2		#print "Substitute "
	syscall
	la $a0, char		#print the character to replace
	syscall
	la $a0, output3		#print " --> "
	syscall
	la $a0, rChar		#print the replacement char
	syscall
	la $a0, newLine		#print new line
	syscall
	
loop:
	beq $t1, $zero, quit		#quit if the end of the string is reached
	beq $t1, $t2, replace		#replace char with rChar if found
	j next

replace:
	sb $t3, ($t0)		#store the new char into the string
	j next
	
next:
	addi $t0, $t0, 1	#increment string address
	lb $t1, ($t0)
	j loop 
	
quit:
	la $a0, output4		#print "Result string: "
	syscall
	la $a0, string		#print the resulting string
	syscall
	
	li $v0, 10		#ends the program
	syscall