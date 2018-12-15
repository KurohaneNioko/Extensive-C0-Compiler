.data
_testchar1 : .byte 0
_testchar2 : .byte 0
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
# $t2: None -> #1
	# now $t2 is #1
# $t3: None -> t
	# now $t3 is t
	lw $t3 -0 ($sp)
	sub $t2 $t3 1
	sw $t2 -92 ($sp)
# push param: #1
	# save start
	sw $ra -96 ($sp)
	sw $sp -100 ($sp)
	addi $sp $sp -92
	jal func_fact
	# recover start
	addi $sp $sp 92
	lw $ra -96 ($sp)
	# recover end
# $t4: None -> #2
	# now $t4 is #2
	move $t4 $v0
# $t5: None -> #3
	# now $t5 is #3
# $t6: None -> t
	# now $t6 is t
	lw $t6 -0 ($sp)
	mul $t5 $t4 $t6
	move $v0 $t5
	jr $ra
label2:
	jr $ra
func_rt15:
# $t0: None -> #4
	# now $t0 is #4
	li $t0 15
# $t1: None -> #5
	# now $t1 is #5
	div $t1 $t0 1
# $t2: None -> #6
	# now $t2 is #6
	add $t2 $t1 1
# $t3: None -> #7
	# now $t3 is #7
	sub $t3 $t2 1
	move $v0 $t3
	jr $ra
	jr $ra
func_fun2:
# $t0: None -> #8
	# now $t0 is #8
# $t1: None -> b
	# now $t1 is b
	lw $t1 -4 ($sp)
# $t2: None -> c
	# now $t2 is c
	lw $t2 -8 ($sp)
	mul $t0 $t1 $t2
# $t3: None -> #9
	# now $t3 is #9
# $t4: None -> d
	# now $t4 is d
	lw $t4 -12 ($sp)
	mul $t3 $t0 $t4
# $t5: None -> #10
	# now $t5 is #10
# $t6: None -> e
	# now $t6 is e
	lw $t6 -16 ($sp)
	div $t5 $t3 $t6
# $t7: None -> #11
	# now $t7 is #11
# $s0: None -> a
	# now $s0 is a
	lw $s0 -0 ($sp)
	add $t7 $s0 $t5
# $s1: None -> #12
	# now $s1 is #12
# $s2: None -> f
	# now $s2 is f
	lw $s2 -20 ($sp)
	sub $s1 $t7 $s2
	li $v0 1
	move $a0 $s1
	syscall
	# print int #12
	li $v0 65
	jr $ra
	jr $ra
main:
# $t0: None -> x
	# now $t0 is x
	li $t0 -1
	sw $t0 _x
	li $v0 1
	move $a0 $t0
	syscall
	# print int x
# $t1: None -> #13
	# now $t1 is #13
	li $t1 -4
# $t2: None -> r
	# now $t2 is r
	move $t2 $t1
	sw $t2 -212 ($sp)
	li $v0 1
	move $a0 $t2
	syscall
	# print int r
# $t3: None -> aa
	# now $t3 is aa
	li $t3 6
	sw $t3 -136 ($sp)
	li $v0 4
	la $a0 string_1
	syscall
	# print str 1
	sw $t3 -216 ($sp)
# push param: aa
	# save start
	sw $ra -220 ($sp)
	sw $sp -224 ($sp)
	addi $sp $sp -216
	jal func_fact
	# recover start
	addi $sp $sp 216
	lw $ra -220 ($sp)
	# recover end
# $t4: None -> #14
	# now $t4 is #14
	move $t4 $v0
	li $v0 1
	move $a0 $t4
	syscall
	# print int #14
# $t5: None -> #15
	# now $t5 is #15
	li $t5 12
# $t6: None -> #16
	# now $t6 is #16
	li $t6 -1
# $t7: None -> #17
	# now $t7 is #17
	sub $t7 $t6 1
# $s0: None -> #18
	# now $s0 is #18
	mul $s0 $t7 6
# $s1: None -> #19
	# now $s1 is #19
	add $s1 $t5 $s0
# $s2: None -> #20
	# now $s2 is #20
# $s3: None -> x
	# now $s3 is x
	lw $s3 _x
# $s4: None -> r
	# now $s4 is r
	lw $s4 -212 ($sp)
	sub $s2 $s3 $s4
	sw $s2 -216 ($sp)
# push param: #20
# $s5: None -> aa
	# now $s5 is aa
	lw $s5 -136 ($sp)
	sw $s5 -220 ($sp)
# push param: aa
	li $t9 1
	sw $t9 -224 ($sp)
# push param: 1
	li $t9 4
	sw $t9 -228 ($sp)
# push param: 4
	li $t9 2
	sw $t9 -232 ($sp)
# push param: 2
	li $t9 -2
	sw $t9 -236 ($sp)
# push param: -2
	# save start
	sw $s1 -240 ($sp)
	sw $ra -244 ($sp)
	sw $sp -248 ($sp)
	addi $sp $sp -216
	jal func_fun2
	# recover start
	addi $sp $sp 216
	lw $ra -244 ($sp)
	lw $s1 -240 ($sp)
	# recover end
# $s6: None -> #21
	# now $s6 is #21
	move $s6 $v0
	addi $t8 $s1 0
	sub $t8 $sp $t8
	sb $s6 ($t8)
# save array: ar[#19] = #21
	li $t9 4
	sw $t9 -216 ($sp)
# push param: 4
	# save start
	sw $ra -220 ($sp)
	sw $sp -224 ($sp)
	addi $sp $sp -216
	jal func_fact
	# recover start
	addi $sp $sp 216
	lw $ra -220 ($sp)
	# recover end
# $s7: None -> #22
	# now $s7 is #22
	move $s7 $v0
# $fp: None -> #23
	# now $fp is #23
	move $fp $0
# $t0: None -> #24
	# now $t0 is #24
	addi $t9 $fp 0
	sub $t9 $sp $t9
	lbu $t0 ($t9)
# read array: #24 = ar[#23]
	li $v0 1
	move $a0 $t0
	syscall
	# print int #24
	li $t9 48
	sb $t9 -1 ($sp)
# save array: ar[1] = '0'
# $t2: None -> #25
	# now $t2 is #25
	lbu $t2 -1($sp)
# read array: #25 = ar[1]
	# save start
	sw $t2 -216 ($sp)
	sw $ra -220 ($sp)
	sw $sp -224 ($sp)
	addi $sp $sp -216
	jal func_rt15
	# recover start
	addi $sp $sp 216
	lw $ra -220 ($sp)
	lw $t2 -216 ($sp)
	# recover end
# $t3: None -> #26
	# now $t3 is #26
	move $t3 $v0
# $s3: None -> #27
	# now $s3 is #27
	add $s3 $t2 $t3
# $s4: None -> #28
	# now $s4 is #28
	mul $s4 $s3 1
# $s5: None -> #29
	# now $s5 is #29
	sub $s5 $0 $s4
# $s6: #21 -> #30
	# now $s6 is #30
	li $s6 36
# $s7: #22 -> #31
	# now $s7 is #31
	sub $t9 $s6 2
	sub $s7 $0 $t9
# $fp: #23 -> #32
	# now $fp is #32
	add $fp $s5 $s7
# $t0: #24 -> #33
	# now $t0 is #33
	li $t0 218
# $t1: #13 -> #34
	# now $t1 is #34
	add $t1 $fp $t0
# $t2: #25 -> aa
	# now $t2 is aa
	move $t2 $t1
	sw $t2 -136 ($sp)
	li $v0 1
	move $a0 $t2
	syscall
	# print int aa
# $t2: None -> a
	# now $t2 is a
# $t3: #26 -> aa
	# now $t3 is aa
	lw $t3 -136 ($sp)
	move $t2 $t3
	sw $t2 -132 ($sp)
	li $v0 5
	syscall
	move $t2 $v0
	sw $t2 -132 ($sp)
	# read int a
	li $v0 5
	syscall
# $t3: None -> x
	# now $t3 is x
	move $t3 $v0
	sw $t3 _x
	# read int x
	blez $t2 label3
	li $v0 4
	la $a0 string_2
	syscall
	# print str 2
	bgtz $t3 label4
# $t2: None -> #35
	# now $t2 is #35
# $t3: None -> a
	# now $t3 is a
	lw $t3 -132 ($sp)
# $t4: #14 -> x
	# now $t4 is x
	lw $t4 _x
	div $t2 $t3 $t4
# $t3: None -> #36
	# now $t3 is #36
# $t4: None -> a
	# now $t4 is a
	lw $t4 -132 ($sp)
	mul $t3 $t2 $t4
# $t4: None -> r
	# now $t4 is r
	move $t4 $t3
	sw $t4 -212 ($sp)
	li $v0 1
	move $a0 $t4
	syscall
	# print int r
	li $v0 4
	la $a0 string_3
	syscall
	# print str 3
label4:
# $t4: None -> #37
	# now $t4 is #37
# $t5: #15 -> r
	# now $t5 is r
	lw $t5 -212 ($sp)
# $t6: #16 -> aa
	# now $t6 is aa
	lw $t6 -136 ($sp)
	add $t4 $t5 $t6
# $t5: None -> r
	# now $t5 is r
	move $t5 $t4
	sw $t5 -212 ($sp)
	li $v0 1
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
# $t5: None -> #38
	# now $t5 is #38
	li $t5 -4
# $t6: None -> a
	# now $t6 is a
	lw $t6 -132 ($sp)
	bne $t6 $t5 label6
# $t6: None -> #39
	# now $t6 is #39
# $t7: #17 -> r
	# now $t7 is r
	lw $t7 -212 ($sp)
	add $t6 $t7 1
# $t7: None -> r
	# now $t7 is r
	move $t7 $t6
	sw $t7 -212 ($sp)
	li $v0 1
	move $a0 $t7
	syscall
	# print int r
	li $v0 4
	la $a0 string_5
	syscall
	# print str 5
label6:
label5:
# $t7: None -> a
	# now $t7 is a
	lw $t7 -132 ($sp)
	bgez $t7 label7
	li $v0 4
	la $a0 string_6
	syscall
	# print str 6
# $t7: None -> x
	# now $t7 is x
	lw $t7 _x
	bltz $t7 label8
# $t7: None -> #40
	# now $t7 is #40
# $s0: #18 -> r
	# now $s0 is r
	lw $s0 -212 ($sp)
# $s1: #19 -> a
	# now $s1 is a
	lw $s1 -132 ($sp)
	add $t7 $s0 $s1
# $s0: None -> r
	# now $s0 is r
	move $s0 $t7
	sw $s0 -212 ($sp)
	li $v0 1
	move $a0 $s0
	syscall
	# print int r
	li $v0 4
	la $a0 string_7
	syscall
	# print str 7
label8:
	j label9
label7:
# $s1: None -> #41
	# now $s1 is #41
# $s0: None -> r
	# now $s0 is r
	lw $s0 -212 ($sp)
	mul $s1 $s0 -1
# $s0: None -> r
	# now $s0 is r
	move $s0 $s1
	sw $s0 -212 ($sp)
	li $v0 1
	move $a0 $s0
	syscall
	# print int r
label9:
# $s0: None -> #42
	# now $s0 is #42
	li $s0 -2
# $s1: #41 -> a
	# now $s1 is a
	move $s1 $s0
	sw $s1 -132 ($sp)
label10:
# $s2: #20 -> #43
	# now $s2 is #43
# $s3: #27 -> x
	# now $s3 is x
	lw $s3 _x
	add $s2 $s3 4
# $s3: None -> x
	# now $s3 is x
	move $s3 $s2
	sw $s3 _x
	add $s1 $s1 1
	sw $s1 -132 ($sp)
# $s1: None -> a
	# now $s1 is a
	lw $s1 -132 ($sp)
	blt $s1 3 label10
label11:
	blez $s3 label12
# $s3: None -> #44
	# now $s3 is #44
# $s1: None -> x
	# now $s1 is x
	lw $s1 _x
	sub $s3 $s1 2
# $s1: None -> x
	# now $s1 is x
	move $s1 $s3
	sw $s1 _x
	j label11
label12:
	li $v0 1
	move $a0 $s1
	syscall
	# print int x
exit:
