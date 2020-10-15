	.data

inBuf:	.space	80
TOKEN:	.space	8
tokSpace: .word 8
TYPE:	.word	0
tabToken: .word	0:30		# 10-entry token table
error: .ascii "Error"



	.text
###############################
#
#	MAIN Driver
#
#		$t3:	index to inBuf(i)
#		$t6:	index to tabToken
#		$t9:	curChar
#
#		$s0:	T
#		$s1:	CUR
#	
#############################
main:
newLine:
	jal	getline

	li	$t3, 0		# index to inBuf
	
	la	$s1, Q0		# CUR = Q0
	li	$s0, 1		# T = 1
	
nextState:	
	lw	$s2, 0($s1)	# $s2 = STAB[CUR][0]
	jalr	$v1, $s2	# Call action; Save return addr in $v1

	sll	$s0, $s0, 2	# 4*T
	add	$s1, $s1, $s0	# CUR+4*T
	sra	$s0, $s0, 2
	lw	$s1, 0($s1)	# CUR = STAB[CUR][T]
	b	nextState

dump:	jal	printTabToken
	jal	clearBuf
	jal	clearTabToken
	b	newLine
	
####################
#
#	ACT1:
#
#		$t3 - global index to inBuf
#		$t9 - curChar
#
####################
ACT1:
    lb     $t9,inBuf($t3)        #ACT1: curChar = inBuf[i]
    jal    lin_search        # T = lin_search($t0)
    
    addi   $t3, $t3, 1        # i++
    jr	   $v1

ACT2:
    sb    $t9, TOKEN($zero)        #ACT2: TOKEN = curChar
    li    $t4, 7            #TokSpace = 7
    jr    $v1

ACT3:
    sb    $t9, TOKEN($t4)        #TOKEN = TOKEN + curChar
    addi  $t4, $t4, 1        #TokSpace++
    jr    $v1

ACT4:
    lw    $t0, TOKEN($0)        # get the first word from TOKEN
    sw    $t0, tabToken($a3)    # save word to tokTab
    lw    $t0, TOKEN+8($0)    # get Token data type
    sw    $t0, tabToken+8($a3)    # save in tokTab
    addi  $a3, $a3, 12        # update index in tokTab
    
    jal    clearTok        # clear TOKEN
    jr    $v1
        
ERROR:
    la    $t9, error    #ERROR
    li    $v0, 4
    syscall
    b    dump
RETURN:
    b    dump

clearTok:
	li	$a0, 0
	sw	$a0, TOKEN($0)		#set token to zero
	sw	$a0, TOKEN+4($0)	#set token to zero
	sw	$a0, TOKEN+8($0)	#set token to zero

	jr	$ra

##############################
#
# lin_search()
#	argument - $t9 for key
#	return val - $s0 for char type
#
#############################
lin_search:
    li $t5, 0            #int i=0
    li $t8, 0            #int found=0
loop2:
    bge $t5, 80, return        #if (i >= n) goto return
    bne $t8, 0, return        #if (found) goto return
    
    sll $t5, $t5, 3            #shift to ext element
    lb  $s0, Tabchar($t5)        #load Tabchar[i] to the memory
    sra $t5, $t5, 3                  #shift back
    
    bne $s0, $t9, next        #if (Tabchar[i] != key) goto next
    li $t8, 1             #found = 1
next: 
    addi $t5, $t5, 1        #i++
    b loop2                #goto loop2
return: 
    beq $t8, 0, err         #if (i >= n)
    subi $t5, $t5, 1 
    sll $t5, $t5, 3         #shift to the ext element
    lw $s0 Tabchar+4($t5)         #return the char type
    sra $t5, $t5, 3         #shift back to element
    jr    $ra
err: 
    li $s0, -1             #return failure
    jr $ra 

##########################3
#
#	getline
#
#
##########################
	.data
prompt:	.asciiz	"Enter an input string:\n"

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
	
#############################################
#
#  printTabToken:
#	print Token table header
#	copy each entry of tabToken into outBuf
#	   and print TOKEN
#	$a3 has the index (in bytes) to the last entry of tabToken
#
#############################################
		.data
outBuf:		.word	0:3			# copy token entry to outBuf to print
tableHead:	.asciiz "TOKEN    TYPE\n"

		.text
printTabToken:
		li	$t7, 0x20		# blank in $t7
		li	$t6, '\n'		# newline in $t6

		la	$a0, tableHead		# print table heading
		li	$v0, 4
		syscall

		li	$t0, 0
loopTok:	bge	$t0, $a3, doneTok	# if ($t0 <= $a3)
	
		lw	$t1, tabToken($t0)	#   copy tabToken[] into outBuf
		sw	$t1, outBuf
		lw	$t1, tabToken+4($t0)
		sw	$t1, outBuf+4
	
		li	$t9, -1			# for each char in outBuf
loopChar:	addi	$t9, $t9, 1
		bge	$t9, 8, tokType		
		lb	$t8, outBuf($t9)		#   if char == Null
		bne	$t8, $zero, loopChar	
		sb	$t7, outBuf($t9)		#       replace it by ' ' (0x20)
		b	loopChar
tokType:
		sb	$t7, outBuf+8		# insert blank
		lb	$t1, tabToken+8($t0)	# $t1 = token type
		addi	$t1, $t1, 0x30		# ASCII(token type)
		sb	$t1, outBuf+9
		sb	$t6, outBuf+10		# terminate with '\n'
		sb	$0, outBuf+11
		
		la	$a0, outBuf		# print token and its type
		li	$v0, 4
		syscall
	
		addi	$t0, $t0, 12
		sw	$0, outBuf		# clear outBuf
		sw	$0, outBuf+4
		b	loopTok

doneTok:
		jr	$ra


#######################
#
# clearBuf():
#
#######################
clearBuf:
	li $t4, 0 #int i = 0
repeat: 
	bge $t4, 80, clear #if (1 >= n) goto return
	sb $0, inBuf($t4) #clear the inBuf/ inBuf(i) = null
	sb $0, outBuf($t4) #clear the outBuf/outBuf(i) = null
	
	addi $t4, $t4, 1 #i++
	b repeat #loop
clear:
	jr	$ra
	

##########################################################
#
#    clears tabToken
#
##########################################################
clearTabToken:
    li    $t3, 0x20                   # int i=0
clearTokenRept:
    bge   $t3, 60, clearTokenRet   # if (i>=n) goto ret
    li    $t4, ' '
    sb    $t4, tabToken($t3)
    
    addi    $t3, $t3, 1            # i++
    b    clearTokenRept            # loop
clearTokenRet:
    jr    $ra                      # return

	.data

STAB:
Q0:     .word  ACT1
        .word  Q1   # T1
        .word  Q1   # T2
        .word  Q1   # T3
        .word  Q1   # T4
        .word  Q1   # T5
        .word  Q1   # T6
        .word  Q11  # T7

Q1:     .word  ACT2
        .word  Q2   # T1
        .word  Q5   # T2

        .word  Q3   # T3

        .word  Q3   # T4

        .word  Q0   # T5

        .word  Q4   # T6

        .word  Q11  # T7



Q2:     .word  ACT1

        .word  Q6   # T1

        .word  Q7   # T2

        .word  Q7   # T3

        .word  Q7   # T4

        .word  Q7   # T5

        .word  Q7   # T6

        .word  Q11  # T7



Q3:     .word  ACT4

        .word  Q0   # T1

        .word  Q0   # T2

        .word  Q0   # T3

        .word  Q0   # T4

        .word  Q0   # T5

        .word  Q0   # T6

        .word  Q11  # T7



Q4:     .word  ACT4

        .word  Q10  # T1

        .word  Q10  # T2

        .word  Q10  # T3

        .word  Q10  # T4

        .word  Q10  # T5

        .word  Q10  # T6

        .word  Q11  # T7



Q5:     .word  ACT1

        .word  Q8   # T1

        .word  Q8   # T2

        .word  Q9   # T3

        .word  Q9   # T4

        .word  Q9   # T5

        .word  Q9   # T6

        .word  Q11  # T7



Q6:     .word  ACT3

        .word  Q2   # T1

        .word  Q2   # T2

        .word  Q2   # T3

        .word  Q2   # T4

        .word  Q2   # T5

        .word  Q2   # T6

        .word  Q11  # T7



Q7:     .word  ACT4

        .word  Q1   # T1

        .word  Q1   # T2

        .word  Q1   # T3

        .word  Q1   # T4

        .word  Q1   # T5

        .word  Q1   # T6

        .word  Q11  # T7



Q8:     .word  ACT3

        .word  Q5   # T1

        .word  Q5   # T2

        .word  Q5   # T3

        .word  Q5   # T4

        .word  Q5   # T5

        .word  Q5   # T6

        .word  Q11  # T7



Q9:     .word  ACT4

        .word  Q1  # T1

        .word  Q1  # T2

        .word  Q1  # T3

        .word  Q1  # T4

        .word  Q1  # T5

        .word  Q1  # T6

        .word  Q11 # T7



Q10:	.word	RETURN

        .word  Q10  # T1

        .word  Q10  # T2

        .word  Q10  # T3

        .word  Q10  # T4

        .word  Q10  # T5

        .word  Q10  # T6

        .word  Q11  # T7



Q11:    .word  ERROR 

	.word  Q4  # T1

	.word  Q4  # T2

	.word  Q4  # T3

	.word  Q4  # T4

	.word  Q4  # T5

	.word  Q4  # T6

	.word  Q4  # T7

	
Tabchar: 
	.word 	0x0a, 6		# LF
	.word	' ', 5
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
