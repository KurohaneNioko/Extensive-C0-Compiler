.data
.align 2
string_12 : .asciiz "          The total is \n"
string_8 : .asciiz "          \n"
string_7 : .asciiz "  \n"
string_9 : .asciiz " ---------------------------------------------------------------          \n"
string_13 : .asciiz " 10! = \n"
string_5 : .asciiz " OVERFLOW!          \n"
string_3 : .asciiz " SWAP x = \n"
string_4 : .asciiz " SWAP y = \n"
string_11 : .asciiz " \n"
string_10 : .asciiz " b = \n"
string_6 : .asciiz " complete number: \n"
string_1 : .asciiz " x = \n"
string_2 : .asciiz " y = \n"
.text
.globl main
func_factorial:
	lw $t2 -0 ($sp)
	bgt $t2 1 label1
	li $v0 1
	jr $ra
label1:
	addi $t0 $t2 -1
	
	sw $t0 -92 ($sp)
# push param: #1
	# save start
	sw $t2 -112 ($sp)
	sw $ra -180 ($sp)
	addi $sp $sp -92
	jal func_factorial
	# recover start
	addi $sp $sp 92
	lw $ra -180 ($sp)
	lw $t2 -112 ($sp)
	# recover end
	move $t1 $v0
	
	mul $v0 $t2 $t1
	jr $ra
	jr $ra
func_mod:
	lw $t2 -0 ($sp)
	lw $t3 -4 ($sp)
	div $t0 $t2 $t3
	
	mul $t1 $t0 $t3
	
	subu $t2 $t2 $t1
	
	move $v0 $t2
	jr $ra
	jr $ra
func_swap:
	li $v0 4
	la $a0 string_1
	syscall
	# print str 1
	li $v0 1
	lw $t1 -0 ($sp)
	move $a0 $t1
	syscall
	# print int x
	li $v0 4
	la $a0 string_2
	syscall
	# print str 2
	li $v0 1
	lw $t2 -4 ($sp)
	move $a0 $t2
	syscall
	# print int y
	move $t0 $t1
	
	move $t1 $t2
	
	move $t2 $t0
	
	li $v0 4
	la $a0 string_3
	syscall
	# print str 3
	li $v0 1
	move $a0 $t1
	syscall
	# print int x
	li $v0 4
	la $a0 string_4
	syscall
	# print str 4
	li $v0 1
	move $a0 $t2
	syscall
	# print int y
	jr $ra
func_complete_num:
	lw $t1 -0 ($sp)
	move $t7 $t1
	
label2:
	bge $t7 1024 label3
	li $t3 -1
	
	move $t2 $t7
	
	li $s0 1
	
label4:
	bge $s0 $t7 label5
	div $t0 $t7 $s0
	
	sw $t7 -672 ($sp)
# push param: j
	sw $s0 -676 ($sp)
# push param: i
	# save start
	sw $t0 -696 ($sp)
	sw $t2 -700 ($sp)
	sw $t3 -704 ($sp)
	sw $t7 -708 ($sp)
	sw $s0 -712 ($sp)
	sw $ra -764 ($sp)
	addi $sp $sp -672
	jal func_mod
	# recover start
	addi $sp $sp 672
	lw $ra -764 ($sp)
	lw $t0 -696 ($sp)
	lw $t2 -700 ($sp)
	lw $t3 -704 ($sp)
	lw $t7 -708 ($sp)
	lw $s0 -712 ($sp)
	# recover end
	move $fp $v0
	
	bne $fp 0 label6
	addi $t3 $t3 1
	
	subu $t2 $t2 $s0
	
	blt $t3 128 label7
	li $v0 4
	la $a0 string_5
	syscall
	# print str 5
label7:
	bge $t3 128 label8
	sll $t8 $t3 2
	addi $t8 $t8 64
	
	subu $t8 $sp $t8
	sw $s0 ($t8)
# save array: k[n] = i
label8:
label6:
	addi $s0 $s0 1
	
	j label4
label5:
	bne $t2 0 label9
	li $v0 4
	la $a0 string_6
	syscall
	# print str 6
	li $v0 1
	move $a0 $t7
	syscall
	# print int j
	addu $s0 $0 $0
	
label10:
	bgt $s0 $t3 label11
	li $v0 4
	la $a0 string_7
	syscall
	# print str 7
	sll $t9 $s0 2
	addi $t9 $t9 64
	subu $t9 $sp $t9
	lw $s7 ($t9)
	
# read array: #7 = k[i]
	li $v0 1
	move $a0 $s7
	syscall
	# print int #7
	addi $s0 $s0 1
	
	j label10
label11:
	li $v0 4
	la $a0 string_8
	syscall
	# print str 8
label9:
	addi $t7 $t7 1
	
	j label2
label3:
	li $v0 4
	la $a0 string_9
	syscall
	# print str 9
	addu $s4 $0 $0
	
	addu $s0 $0 $0
	
label12:
	bge $s0 1024 label13
	mul $s3 $s4 $s0
	
	mul $s2 $t7 $t3
	
	mul $s4 $s4 $s0
	
	addu $s6 $s4 $s3
	
	addu $s4 $s6 $s2
	
	addi $s0 $s0 1
	
	j label12
label13:
	move $s3 $s4
	
	addu $s0 $0 $0
	
label14:
	bge $s0 1024 label15
	addu $s3 $s3 $s0
	
	addi $s0 $s0 1
	
	j label14
label15:
	li $v0 4
	la $a0 string_10
	syscall
	# print str 10
	li $v0 1
	move $a0 $s3
	syscall
	# print int b
	li $v0 4
	la $a0 string_9
	syscall
	# print str 9
	addu $s1 $0 $0
	
	li $t5 1
	
	li $t4 2
	
label16:
	bgt $t4 1024 label17
	sra $t6 $t4 1
	
	li $s0 2
	
label18:
	bgt $s0 $t6 label19
	div $s5 $t4 $s0
	
	sw $t4 -672 ($sp)
# push param: m
	sw $s0 -676 ($sp)
# push param: i
	# save start
	sw $t0 -696 ($sp)
	sw $t2 -700 ($sp)
	sw $t3 -704 ($sp)
	sw $t4 -708 ($sp)
	sw $t5 -712 ($sp)
	sw $s0 -716 ($sp)
	sw $s1 -720 ($sp)
	sw $s5 -724 ($sp)
	sw $ra -764 ($sp)
	addi $sp $sp -672
	jal func_mod
	# recover start
	addi $sp $sp 672
	lw $ra -764 ($sp)
	lw $t0 -696 ($sp)
	lw $t2 -700 ($sp)
	lw $t3 -704 ($sp)
	lw $t4 -708 ($sp)
	lw $t5 -712 ($sp)
	lw $s0 -716 ($sp)
	lw $s1 -720 ($sp)
	lw $s5 -724 ($sp)
	# recover end
	sw $t2 -592 ($sp)
	move $t2 $v0
	
	bne $t2 0 label20
	addu $t5 $0 $0
	
label20:
	addi $s0 $s0 1
	
	j label18
label19:
	bne $t5 1 label21
	li $v0 4
	la $a0 string_11
	syscall
	# print str 11
	li $v0 1
	move $a0 $t4
	syscall
	# print int m
	addi $s1 $s1 1
	
	div $t1 $s1 10
	
	sw $t0 -20 ($sp)
	mul $t0 $t1 10
	
	bne $t0 $s1 label22
	li $v0 4
	la $a0 string_8
	syscall
	# print str 8
label22:
label21:
	li $t5 1
	
	addi $t4 $t4 1
	
	j label16
label17:
	li $v0 4
	la $a0 string_12
	syscall
	# print str 12
	li $v0 1
	move $a0 $s1
	syscall
	# print int h
	jr $ra
main:
	li $t9 10
	sw $t9 -12 ($sp)
# push param: 10
	# save start
	sw $ra -100 ($sp)
	addi $sp $sp -12
	jal func_factorial
	# recover start
	addi $sp $sp 12
	lw $ra -100 ($sp)
	# recover end
	move $t0 $v0
	
	li $v0 4
	la $a0 string_13
	syscall
	# print str 13
	li $v0 1
	move $a0 $t0
	syscall
	# print int n
	li $t9 5
	sw $t9 -12 ($sp)
# push param: 5
	li $t9 10
	sw $t9 -16 ($sp)
# push param: 10
	# save start
	sw $ra -100 ($sp)
	addi $sp $sp -12
	jal func_swap
	# recover start
	addi $sp $sp 12
	lw $ra -100 ($sp)
	# recover end
	li $t9 2
	sw $t9 -12 ($sp)
# push param: 2
	# save start
	sw $ra -680 ($sp)
	addi $sp $sp -12
	jal func_complete_num
	# recover start
	addi $sp $sp 12
	lw $ra -680 ($sp)
	# recover end
exit:
