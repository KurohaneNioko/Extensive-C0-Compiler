.data
_testchar1 : .byte 0
_testchar2 : .byte 0
.align 2
_x : .word 0
_xxxx : .word 0
_yyy : .space 28
_zzzzzzz : .word 0
string_1 : .asciiz "!@#$%%abcd114514ABCD963287~;: \n"
string_2 : .asciiz "1 hit \n"
string_3 : .asciiz "2 hit\n"
string_4 : .asciiz "3 hit \n"
string_5 : .asciiz "4 hit \n"
string_6 : .asciiz "5 hit \n"
string_7 : .asciiz "6 hit \n"
.text
.globl main
func_fact:
# $t0: None -> t
	# now $t0 is t
	lw $t0 -0 ($sp)
	bge $t0 3 label1
# $t1: None -> t
	# now $t1 is t
	lw $t1 -0 ($sp)
	move $v0 $t1
	jr $ra
	j label2
label1:
# $t2: None -> t
	# now $t2 is t
	lw $t2 -0 ($sp)
# $t3: None -> #1
	# now $t3 is #1
	addi $t3 $t2 -1
	sw $t3 -88 ($sp)
# push param: #1
	# save start
	sw $ra -172 ($sp)
	addi $sp $sp -88
	jal func_fact
	# recover start
	addi $sp $sp 88
	lw $ra -172 ($sp)
	# recover end
# $t4: None -> #2
	# now $t4 is #2
	move $t4 $v0
# $t5: None -> t
	# now $t5 is t
	lw $t5 -0 ($sp)
	mul $v0 $t4 $t5
	jr $ra
label2:
	jr $ra
func_rt15:
	li $v0 15
	jr $ra
	jr $ra
func_fun2:
# $t0: None -> b
	# now $t0 is b
	lw $t0 -4 ($sp)
# $t1: None -> c
	# now $t1 is c
	lw $t1 -8 ($sp)
# $t2: None -> #6
	# now $t2 is #6
	mul $t2 $t0 $t1
# $t3: None -> d
	# now $t3 is d
	lw $t3 -12 ($sp)
# $t4: None -> #7
	# now $t4 is #7
	mul $t4 $t2 $t3
# $t5: None -> e
	# now $t5 is e
	lw $t5 -16 ($sp)
# $t6: None -> #8
	# now $t6 is #8
	div $t6 $t4 $t5
# $t7: None -> a
	# now $t7 is a
	lw $t7 -0 ($sp)
# $s0: None -> #9
	# now $s0 is #9
	addu $s0 $t7 $t6
# $s1: None -> f
	# now $s1 is f
	lw $s1 -20 ($sp)
# $s2: None -> #10
	# now $s2 is #10
	subu $s2 $s0 $s1
	li $v0 1
	move $a0 $s2
	syscall
	# print int #10
	li $v0 65
	jr $ra
	jr $ra
main:
# $t0: None -> x
	# now $t0 is x
	li $t0 -1
	sw $t0 _x
	li $v0 1
	li $a0 -1
	syscall
	# print int -1
# $t1: None -> r
	# now $t1 is r
	li $t1 -4
	sw $t1 -124 ($sp)
	li $v0 1
	li $a0 -4
	syscall
	# print int -4
# $t2: None -> aa
	# now $t2 is aa
	li $t2 6
	sw $t2 -88 ($sp)
	li $v0 4
	la $a0 string_1
	syscall
	# print str 1
	li $t9 6
	sw $t9 -128 ($sp)
# push param: 6
	# save start
	sw $ra -212 ($sp)
	addi $sp $sp -128
	jal func_fact
	# recover start
	addi $sp $sp 128
	lw $ra -212 ($sp)
	# recover end
# $t3: None -> #11
	# now $t3 is #11
	move $t3 $v0
	li $v0 1
	move $a0 $t3
	syscall
	# print int #11
# $t4: None -> #16
	# now $t4 is #16
	addu $t4 $0 $0
# $t5: None -> x
	# now $t5 is x
	lw $t5 _x
# $t6: None -> r
	# now $t6 is r
	lw $t6 -124 ($sp)
# $t7: None -> #17
	# now $t7 is #17
	subu $t7 $t5 $t6
	sw $t7 -128 ($sp)
# push param: #17
# $s0: None -> aa
	# now $s0 is aa
	lw $s0 -88 ($sp)
	sw $s0 -132 ($sp)
# push param: aa
	li $t9 1
	sw $t9 -136 ($sp)
# push param: 1
	li $t9 4
	sw $t9 -140 ($sp)
# push param: 4
	li $t9 2
	sw $t9 -144 ($sp)
# push param: 2
	li $t9 -2
	sw $t9 -148 ($sp)
# push param: -2
	# save start
	sw $t4 -176 ($sp)
	sw $ra -244 ($sp)
	addi $sp $sp -128
	jal func_fun2
	# recover start
	addi $sp $sp 128
	lw $ra -244 ($sp)
	lw $t4 -176 ($sp)
	# recover end
# $s1: None -> #18
	# now $s1 is #18
	move $s1 $v0
	addi $t8 $t4 3
	subu $t8 $sp $t8
	sb $s1 ($t8)
# save array: ar[#16] = #18
	li $t9 4
	sw $t9 -128 ($sp)
# push param: 4
	# save start
	sw $ra -212 ($sp)
	addi $sp $sp -128
	jal func_fact
	# recover start
	addi $sp $sp 128
	lw $ra -212 ($sp)
	# recover end
# $s2: None -> #20
	# now $s2 is #20
	addu $s2 $0 $0
# $s3: None -> #21
	# now $s3 is #21
	lbu $s3 -3($sp)
# read array: #21 = ar[0]
	li $v0 1
	move $a0 $s3
	syscall
	# print int #21
	li $t9 48
	sb $t9 -4 ($sp)
# save array: ar[1] = '0'
# $s4: None -> #22
	# now $s4 is #22
	lbu $s4 -4($sp)
# read array: #22 = ar[1]
	# save start
	sw $s2 -144 ($sp)
	sw $s4 -148 ($sp)
	sw $ra -212 ($sp)
	addi $sp $sp -128
	jal func_rt15
	# recover start
	addi $sp $sp 128
	lw $ra -212 ($sp)
	lw $s2 -144 ($sp)
	lw $s4 -148 ($sp)
	# recover end
# $s5: None -> #23
	# now $s5 is #23
	move $s5 $v0
# $s6: None -> #24
	# now $s6 is #24
	addu $s6 $s4 $s5
# $s7: None -> #25
	# now $s7 is #25
	move $s7 $s6
# $fp: None -> #26
	# now $fp is #26
	subu $fp $0 $s7
# $t0: None -> #29
	# now $t0 is #29
	addi $t0 $fp -34
# $t1: None -> aa
	# now $t1 is aa
	addi $t1 $t0 218
	sw $t1 -88 ($sp)
	li $v0 1
# $t2: None -> aa
	# now $t2 is aa
	lw $t2 -88 ($sp)
	move $a0 $t2
	syscall
	# print int aa
# $t5: None -> aa
	# now $t5 is aa
	lw $t5 -88 ($sp)
# $t6: None -> a
	# now $t6 is a
	move $t6 $t5
	sw $t6 -84 ($sp)
	li $v0 5
	syscall
# $s0: None -> a
	# now $s0 is a
	move $s0 $v0
	sw $s0 -84 ($sp)
	# read int a
	li $v0 5
	syscall
# $t1: None -> x
	# now $t1 is x
	move $t1 $v0
	sw $t1 _x
	# read int x
# $t2: None -> a
	# now $t2 is a
	lw $t2 -84 ($sp)
	blez $t2 label3
	li $v0 4
	la $a0 string_2
	syscall
	# print str 2
# $t5: None -> x
	# now $t5 is x
	lw $t5 _x
	bgtz $t5 label4
# $t6: None -> a
	# now $t6 is a
	lw $t6 -84 ($sp)
# $s0: None -> x
	# now $s0 is x
	lw $s0 _x
# $t1: None -> #31
	# now $t1 is #31
	div $t1 $t6 $s0
# $t2: None -> a
	# now $t2 is a
	lw $t2 -84 ($sp)
# $t5: None -> r
	# now $t5 is r
	mul $t5 $t1 $t2
	sw $t5 -124 ($sp)
	li $v0 1
# $t6: None -> r
	# now $t6 is r
	lw $t6 -124 ($sp)
	move $a0 $t6
	syscall
	# print int r
	li $v0 4
	la $a0 string_3
	syscall
	# print str 3
label4:
# $s0: None -> r
	# now $s0 is r
	lw $s0 -124 ($sp)
# $t2: None -> aa
	# now $t2 is aa
	lw $t2 -88 ($sp)
	addu $s0 $s0 $t2
	sw $s0 -124 ($sp)
	li $v0 1
# $t5: None -> r
	# now $t5 is r
	lw $t5 -124 ($sp)
	move $a0 $t5
	syscall
	# print int r
label3:
# $t6: None -> x
	# now $t6 is x
	lw $t6 _x
	beq $t6 0 label5
	li $v0 4
	la $a0 string_4
	syscall
	# print str 4
# $s0: None -> a
	# now $s0 is a
	lw $s0 -84 ($sp)
	bne $s0 -4 label6
# $t2: None -> r
	# now $t2 is r
	lw $t2 -124 ($sp)
	addi $t2 $t2 1
	sw $t2 -124 ($sp)
	li $v0 1
# $t5: None -> r
	# now $t5 is r
	lw $t5 -124 ($sp)
	move $a0 $t5
	syscall
	# print int r
	li $v0 4
	la $a0 string_5
	syscall
	# print str 5
label6:
label5:
# $t6: None -> a
	# now $t6 is a
	lw $t6 -84 ($sp)
	bgez $t6 label7
	li $v0 4
	la $a0 string_6
	syscall
	# print str 6
# $s0: None -> x
	# now $s0 is x
	lw $s0 _x
	bltz $s0 label8
# $t2: None -> r
	# now $t2 is r
	lw $t2 -124 ($sp)
# $t5: None -> a
	# now $t5 is a
	lw $t5 -84 ($sp)
	addu $t2 $t2 $t5
	sw $t2 -124 ($sp)
	li $v0 1
# $t6: None -> r
	# now $t6 is r
	lw $t6 -124 ($sp)
	move $a0 $t6
	syscall
	# print int r
	li $v0 4
	la $a0 string_7
	syscall
	# print str 7
label8:
	j label9
label7:
# $s0: None -> r
	# now $s0 is r
	lw $s0 -124 ($sp)
	mul $s0 $s0 -1
	sw $s0 -124 ($sp)
	li $v0 1
# $t2: None -> r
	# now $t2 is r
	lw $t2 -124 ($sp)
	move $a0 $t2
	syscall
	# print int r
label9:
# $t5: None -> a
	# now $t5 is a
	li $t5 -2
	sw $t5 -84 ($sp)
label10:
# $t6: None -> x
	# now $t6 is x
	lw $t6 _x
	addi $t6 $t6 4
	sw $t6 _x
# $s0: None -> a
	# now $s0 is a
	lw $s0 -84 ($sp)
	addi $s0 $s0 1
	sw $s0 -84 ($sp)
# $t2: None -> a
	# now $t2 is a
	lw $t2 -84 ($sp)
	blt $t2 3 label10
	li $v0 1
# $t5: None -> x
	# now $t5 is x
	lw $t5 _x
	move $a0 $t5
	syscall
	# print int x
exit:
