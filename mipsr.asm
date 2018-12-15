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
# $t1: None -> x
	# now $t1 is x
	lw $t1 _x
	move $a0 $t1
	syscall
	# print int x
# $t2: None -> #13
	# now $t2 is #13
	li $t2 -4
# $t3: None -> r
	# now $t3 is r
	move $t3 $t2
	sw $t3 -212 ($sp)
	li $v0 1
# $t4: None -> r
	# now $t4 is r
	lw $t4 -212 ($sp)
	move $a0 $t4
	syscall
	# print int r
# $t5: None -> aa
	# now $t5 is aa
	li $t5 6
	sw $t5 -136 ($sp)
	li $v0 4
	la $a0 string_1
	syscall
	# print str 1
# $t6: None -> aa
	# now $t6 is aa
	lw $t6 -136 ($sp)
	sw $t6 -216 ($sp)
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
# $t7: None -> #14
	# now $t7 is #14
	move $t7 $v0
	li $v0 1
	move $a0 $t7
	syscall
	# print int #14
# $s0: None -> #15
	# now $s0 is #15
	li $s0 12
# $s1: None -> #16
	# now $s1 is #16
	li $s1 -1
# $s2: None -> #17
	# now $s2 is #17
	sub $s2 $s1 1
# $s3: None -> #18
	# now $s3 is #18
	mul $s3 $s2 6
# $s4: None -> #19
	# now $s4 is #19
	add $s4 $s0 $s3
# $s5: None -> #20
	# now $s5 is #20
# $s6: None -> x
	# now $s6 is x
	lw $s6 _x
# $s7: None -> r
	# now $s7 is r
	lw $s7 -212 ($sp)
	sub $s5 $s6 $s7
	sw $s5 -216 ($sp)
# push param: #20
# $fp: None -> aa
	# now $fp is aa
	lw $fp -136 ($sp)
	sw $fp -220 ($sp)
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
	sw $s4 -240 ($sp)
	sw $ra -244 ($sp)
	sw $sp -248 ($sp)
	addi $sp $sp -216
	jal func_fun2
	# recover start
	addi $sp $sp 216
	lw $ra -244 ($sp)
	lw $s4 -240 ($sp)
	# recover end
# $t0: None -> #21
	# now $t0 is #21
	move $t0 $v0
	addi $t8 $s4 0
	sub $t8 $sp $t8
	sb $t0 ($t8)
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
# $t1: None -> #22
	# now $t1 is #22
	move $t1 $v0
# $t3: None -> #23
	# now $t3 is #23
	move $t3 $0
# $t4: None -> #24
	# now $t4 is #24
	addi $t9 $t3 0
	sub $t9 $sp $t9
	lbu $t4 ($t9)
# read array: #24 = ar[#23]
	li $v0 1
	move $a0 $t4
	syscall
	# print int #24
	li $t9 48
	sb $t9 -1 ($sp)
# save array: ar[1] = '0'
# $t5: None -> #25
	# now $t5 is #25
	lbu $t5 -1($sp)
# read array: #25 = ar[1]
	# save start
	sw $t5 -216 ($sp)
	sw $ra -220 ($sp)
	sw $sp -224 ($sp)
	addi $sp $sp -216
	jal func_rt15
	# recover start
	addi $sp $sp 216
	lw $ra -220 ($sp)
	lw $t5 -216 ($sp)
	# recover end
# $t6: None -> #26
	# now $t6 is #26
	move $t6 $v0
# $s6: None -> #27
	# now $s6 is #27
	add $s6 $t5 $t6
# $s7: None -> #28
	# now $s7 is #28
	mul $s7 $s6 1
# $fp: None -> #29
	# now $fp is #29
	sub $fp $0 $s7
# $t0: #21 -> #30
	# now $t0 is #30
	li $t0 36
# $t1: #22 -> #31
	# now $t1 is #31
	sub $t9 $t0 2
	sub $t1 $0 $t9
# $t2: #13 -> #32
	# now $t2 is #32
	add $t2 $fp $t1
# $t3: #23 -> #33
	# now $t3 is #33
	li $t3 218
# $t4: #24 -> #34
	# now $t4 is #34
	add $t4 $t2 $t3
# $t5: #25 -> aa
	# now $t5 is aa
	move $t5 $t4
	sw $t5 -136 ($sp)
	li $v0 1
# $t6: #26 -> aa
	# now $t6 is aa
	lw $t6 -136 ($sp)
	move $a0 $t6
	syscall
	# print int aa
# $t7: #14 -> a
	# now $t7 is a
# $s0: #15 -> aa
	# now $s0 is aa
	lw $s0 -136 ($sp)
	move $t7 $s0
	sw $t7 -132 ($sp)
	li $v0 5
	syscall
# $s1: #16 -> a
	# now $s1 is a
	move $s1 $v0
	sw $s1 -132 ($sp)
	# read int a
	li $v0 5
	syscall
# $s2: #17 -> x
	# now $s2 is x
	move $s2 $v0
	sw $s2 _x
	# read int x
# $s3: #18 -> a
	# now $s3 is a
	lw $s3 -132 ($sp)
	blez $s3 label3
	li $v0 4
	la $a0 string_2
	syscall
	# print str 2
# $s4: #19 -> x
	# now $s4 is x
	lw $s4 _x
	bgtz $s4 label4
# $s5: #20 -> #35
	# now $s5 is #35
# $s6: #27 -> a
	# now $s6 is a
	lw $s6 -132 ($sp)
# $s7: #28 -> x
	# now $s7 is x
	lw $s7 _x
	div $s5 $s6 $s7
# $fp: #29 -> #36
	# now $fp is #36
# $t0: #30 -> a
	# now $t0 is a
	lw $t0 -132 ($sp)
	mul $fp $s5 $t0
# $t1: #31 -> r
	# now $t1 is r
	move $t1 $fp
	sw $t1 -212 ($sp)
	li $v0 1
# $t2: #32 -> r
	# now $t2 is r
	lw $t2 -212 ($sp)
	move $a0 $t2
	syscall
	# print int r
	li $v0 4
	la $a0 string_3
	syscall
	# print str 3
label4:
# $t3: #33 -> #37
	# now $t3 is #37
# $t4: #34 -> r
	# now $t4 is r
	lw $t4 -212 ($sp)
# $t5: #25 -> aa
	# now $t5 is aa
	lw $t5 -136 ($sp)
	add $t3 $t4 $t5
# $t6: #26 -> r
	# now $t6 is r
	move $t6 $t3
	sw $t6 -212 ($sp)
	li $v0 1
# $t7: #14 -> r
	# now $t7 is r
	lw $t7 -212 ($sp)
	move $a0 $t7
	syscall
	# print int r
label3:
# $s0: #15 -> x
	# now $s0 is x
	lw $s0 _x
	beq $s0 0 label5
	li $v0 4
	la $a0 string_4
	syscall
	# print str 4
# $s1: #16 -> #38
	# now $s1 is #38
	li $s1 -4
# $s2: #17 -> a
	# now $s2 is a
	lw $s2 -132 ($sp)
	bne $s2 $s1 label6
# $s3: #18 -> #39
	# now $s3 is #39
# $s4: #19 -> r
	# now $s4 is r
	lw $s4 -212 ($sp)
	add $s3 $s4 1
# $s5: #35 -> r
	# now $s5 is r
	move $s5 $s3
	sw $s5 -212 ($sp)
	li $v0 1
# $s6: #27 -> r
	# now $s6 is r
	lw $s6 -212 ($sp)
	move $a0 $s6
	syscall
	# print int r
	li $v0 4
	la $a0 string_5
	syscall
	# print str 5
label6:
label5:
# $s7: #28 -> a
	# now $s7 is a
	lw $s7 -132 ($sp)
	bgez $s7 label7
	li $v0 4
	la $a0 string_6
	syscall
	# print str 6
# $fp: #36 -> x
	# now $fp is x
	lw $fp _x
	bltz $fp label8
# $t0: #30 -> #40
	# now $t0 is #40
# $t1: #31 -> r
	# now $t1 is r
	lw $t1 -212 ($sp)
# $t2: #32 -> a
	# now $t2 is a
	lw $t2 -132 ($sp)
	add $t0 $t1 $t2
# $t3: #37 -> r
	# now $t3 is r
	move $t3 $t0
	sw $t3 -212 ($sp)
	li $v0 1
# $t4: #34 -> r
	# now $t4 is r
	lw $t4 -212 ($sp)
	move $a0 $t4
	syscall
	# print int r
	li $v0 4
	la $a0 string_7
	syscall
	# print str 7
label8:
	j label9
label7:
# $t5: #25 -> #41
	# now $t5 is #41
# $t6: #26 -> r
	# now $t6 is r
	lw $t6 -212 ($sp)
	mul $t5 $t6 -1
# $t7: #14 -> r
	# now $t7 is r
	move $t7 $t5
	sw $t7 -212 ($sp)
	li $v0 1
# $s0: #15 -> r
	# now $s0 is r
	lw $s0 -212 ($sp)
	move $a0 $s0
	syscall
	# print int r
label9:
# $s1: #38 -> #42
	# now $s1 is #42
	li $s1 -2
# $s2: #17 -> a
	# now $s2 is a
	move $s2 $s1
	sw $s2 -132 ($sp)
label10:
# $s3: #39 -> #43
	# now $s3 is #43
# $s4: #19 -> x
	# now $s4 is x
	lw $s4 _x
	add $s3 $s4 4
# $s5: #35 -> x
	# now $s5 is x
	move $s5 $s3
	sw $s5 _x
# $s6: #27 -> a
	# now $s6 is a
# $s7: #28 -> a
	# now $s7 is a
	lw $s7 -132 ($sp)
	add $s6 $s7 1
	sw $s6 -132 ($sp)
# $fp: #36 -> a
	# now $fp is a
	lw $fp -132 ($sp)
	blt $fp 3 label10
label11:
# $t0: #40 -> x
	# now $t0 is x
	lw $t0 _x
	blez $t0 label12
# $t1: #31 -> #44
	# now $t1 is #44
# $t2: #32 -> x
	# now $t2 is x
	lw $t2 _x
	sub $t1 $t2 2
# $t3: #37 -> x
	# now $t3 is x
	move $t3 $t1
	sw $t3 _x
	j label11
label12:
	li $v0 1
# $t4: #34 -> x
	# now $t4 is x
	lw $t4 _x
	move $a0 $t4
	syscall
	# print int x
exit:
