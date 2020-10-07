	.data
inBuf:	.space 	80
outBuf:	.space	80
	
	
	.text
	
newInput:
	jal	getline		# getline()
	li	$t0, 0		# i=0
loop:
	bge	$t0, 80, dump	# if (i>= 80) goto dump
	lb	$t1, inBuf($t0)	# key = inBuf[i]
				
	jal	lin_search	# $t9 = lin_search($t1)
	addi	$t9, $t9, 0x30	# char(chType)
	sb	$t9, outBuf($t0)
	
	beq	$t1, '#', dump	# if (key=='#') exit
				
	addi	$t0, $t0, 1	# i++
	b	loop
			 
dump:	
	jal	printOutBuf
	jal	clearBufs
				
	b	newInput
	
	
	
###################
#
# getline()
#	argument -
#	return value -
#
#######################
	.data
prompt:	.asciiz	"Enter an input string: "
	
	.text
getline:
	la	$a0, prompt		# Prompt to enter a new line
	li	$v0, 4
	syscall

	la	$a0, inBuf		# read a new line
	li	$a1, 80	
	li	$v0, 8
	syscall

	jr	$ra
	
##############################
#
# lin_search()
#	argument - $t1 for key
#	return val - $t9 for char type
#
#############################
lin_search:
	li $t2, 0    #int i=0
	li $t3, 0    #int found=0, 1 = true, 0 = false
loopTwo:
	bge $t2, 80, return    #if (i >= n) goto return
	bne $t3, 0, return     #if (found) goto return
	
	sll $t2, $t2, 3        #shift to ext element
	lb  $t9, Tabchar($t2)  #load Tabchar[i] to the memory
	sra $t2, $t2, 3	       #shift back
	
	bne $t9, $t1, iterate   #if (Tabchar[i] != key) goto iterate
	li $t3, 1 #found = 1
iterate: 
	addi $t2, $t2, 1 #i++
	b loopTwo #goto loopTwo
return: 
	beq $t3, 0, error #if (i >= n)
	subi $t2, $t2, 1 
	sll $t2, $t2, 3 #shift to the ext element
	lw $t9 Tabchar+4($t2) #return the char type
	sra $t2, $t2, 3 #shift back to element
	jr	$ra
error: 
	li $t9, -1 #return failure
	jr 	$ra 
	
	
#####################
#
# printOutBuf()
#
#####################
printOutBuf:
	la $a0, outBuf  #load outBuf address
	li $v0, 4 	#read to display outBuf
	syscall 
	
	la $a0, '\n' 
	li $v0, 11
	syscall 
	jr	$ra
	
	
	
#######################
#
# clearBuf():
#
#######################
clearBufs:
	li $t4, 0 #int i = 0
repeat: 
	bge $t4, 80, clear #if (1 >= n) goto return
	sb $zero, inBuf($t4) #clear the inBuf/ inBuf(i) = null
	sb $zero, outBuf($t4) #clear the outBuf/outBuf(i) = null
	
	addi $t4, $t4, 1 #i++
	b repeat #loop
clear:
	jr	$ra
	
	.data
Tabchar: 
	.word 	0x0a, 6		# LF
	.word 	' ', 5
 	.word 	'#', 6
	.word 	'$', 4
	.word 	'(', 4 
	.word 	')', 4 
	.word 	'*', 3 
	.word 	'+', 3 
	.word 	',', 4 
	.word 	'-', 3 
	.word 	'.', 4 
	.word 	'/', 3 

	.word 	'0', 1

	.word 	'1', 1 

	.word 	'2', 1 

	.word 	'3', 1 

	.word 	'4', 1 

	.word 	'5', 1 

	.word 	'6', 1 

	.word 	'7', 1 

	.word 	'8', 1 

	.word 	'9', 1 



	.word 	':', 4 



	.word 	'A', 2

	.word 	'B', 2 

	.word 	'C', 2 

	.word 	'D', 2 

	.word 	'E', 2 

	.word 	'F', 2 

	.word 	'G', 2 

	.word 	'H', 2 

	.word 	'I', 2 

	.word 	'J', 2 

	.word 	'K', 2

	.word 	'L', 2 

	.word 	'M', 2 

	.word 	'N', 2 

	.word 	'O', 2 

	.word 	'P', 2 

	.word 	'Q', 2 

	.word 	'R', 2 

	.word 	'S', 2 

	.word 	'T', 2 

	.word 	'U', 2

	.word 	'V', 2 

	.word 	'W', 2 

	.word 	'X', 2 

	.word 	'Y', 2

	.word 	'Z', 2



	.word 	'a', 2 

	.word 	'b', 2 

	.word 	'c', 2 

	.word 	'd', 2 

	.word 	'e', 2 

	.word 	'f', 2 

	.word 	'g', 2 

	.word 	'h', 2 

	.word 	'i', 2 

	.word 	'j', 2 

	.word 	'k', 2

	.word 	'l', 2 

	.word 	'm', 2 

	.word 	'n', 2 

	.word 	'o', 2 

	.word 	'p', 2 

	.word 	'q', 2 

	.word 	'r', 2 

	.word 	's', 2 

	.word 	't', 2 

	.word 	'u', 2

	.word 	'v', 2 

	.word 	'w', 2 

	.word 	'x', 2 

	.word 	'y', 2

	.word 	'z', 2
	.word	0x5c, -1	# if you ‘\’ as the end-of-table symbol
