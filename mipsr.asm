.data
__c1 : .byte 0
__c2 : .byte 0
__c3 : .byte 0
__c4 : .byte 0
.align 2
string_14 : .asciiz " \n"
string_18 : .asciiz " ojbk\n"
string_4 : .asciiz "@@@@@\n"
string_3 : .asciiz "\n"
string_2 : .asciiz "___ !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~___\\n\\t\\\\\\'___\n"
string_1 : .asciiz "_ff4_\n"
string_15 : .asciiz "error10\n"
string_16 : .asciiz "error11\n"
string_17 : .asciiz "error12\n"
string_19 : .asciiz "error13\n"
string_20 : .asciiz "error14\n"
string_5 : .asciiz "error1\n"
string_6 : .asciiz "error2\n"
string_7 : .asciiz "error3\n"
string_8 : .asciiz "error4\n"
string_9 : .asciiz "error5\n"
string_10 : .asciiz "error6\n"
string_11 : .asciiz "error7\n"
string_12 : .asciiz "error8\n"
string_13 : .asciiz "error9\n"
.text
.globl main
func_ff1:
# $t0: None -> _c1
	# now $t0 is _c1
	li $t0 98
	sb $t0 __c1
# $t1: None -> c
	# now $t1 is c
	lbu $t1 -0 ($sp)
	move $v0 $t1
	jr $ra
	jr $ra
func_ff2:
# $t0: None -> _c2
	# now $t0 is _c2
	li $t0 45
	sb $t0 __c2
# $t1: None -> #1
	# now $t1 is #1
	li $t1 3
	addi $v0 $t1 3
	jr $ra
	jr $ra
func_ff3:
# $t0: None -> a
	# now $t0 is a
	lw $t0 -0 ($sp)
# $t1: None -> b
	# now $t1 is b
	lw $t1 -4 ($sp)
# $t2: None -> #2
	# now $t2 is #2
	addu $t2 $t0 $t1
# $t3: None -> c
	# now $t3 is c
	lbu $t3 -8 ($sp)
# $t4: None -> #3
	# now $t4 is #3
	addu $t4 $t2 $t3
# $t5: None -> d
	# now $t5 is d
	lw $t5 -12 ($sp)
# $t6: None -> #4
	# now $t6 is #4
	addu $t6 $t4 $t5
# $t7: None -> e
	# now $t7 is e
	lbu $t7 -16 ($sp)
# $s0: None -> #5
	# now $s0 is #5
	addu $s0 $t6 $t7
# $s1: None -> f
	# now $s1 is f
	lbu $s1 -20 ($sp)
# $s2: None -> #6
	# now $s2 is #6
	addu $s2 $s0 $s1
	li $v0 1
	move $a0 $s2
	syscall
	# print int #6
	jr $ra
	jr $ra
func_ff4:
	li $v0 4
	la $a0 string_1
	syscall
	# print str 1
	jr $ra
func_factorial:
# $t0: None -> a
	# now $t0 is a
	lw $t0 -0 ($sp)
	bne $t0 1 label1
	li $v0 1
	jr $ra
	j label2
label1:
# $t1: None -> a
	# now $t1 is a
	lw $t1 -0 ($sp)
# $t2: None -> #7
	# now $t2 is #7
	addi $t2 $t1 -1
	sw $t2 -96 ($sp)
# push param: #7
	# save start
	sw $ra -188 ($sp)
	addi $sp $sp -96
	jal func_factorial
	# recover start
	addi $sp $sp 96
	lw $ra -188 ($sp)
	# recover end
# $t3: None -> #8
	# now $t3 is #8
	move $t3 $v0
# $t4: None -> a
	# now $t4 is a
	lw $t4 -0 ($sp)
# $t5: None -> b
	# now $t5 is b
	mul $t5 $t3 $t4
	sw $t5 -20 ($sp)
# $t6: None -> b
	# now $t6 is b
	lw $t6 -20 ($sp)
	move $v0 $t6
	jr $ra
label2:
	jr $ra
func_ff5:
# $t0: None -> _t1
	# now $t0 is _t1
	li $t0 4
	sw $t0 -16 ($sp)
# $t1: None -> _t1
	# now $t1 is _t1
	lw $t1 -16 ($sp)
# $t2: None -> #9
	# now $t2 is #9
	addi $t2 $t1 122
# $t3: None -> _c1
	# now $t3 is _c1
	lbu $t3 __c1
# $t4: None -> #10
	# now $t4 is #10
	addu $t4 $t2 $t3
	li $v0 1
	move $a0 $t4
	syscall
	# print int #10
	jr $ra
main:
	li $v0 5
	syscall
# $t0: None -> in_1
	# now $t0 is in_1
	move $t0 $v0
	sw $t0 -528 ($sp)
	# read int in_1
# $t1: None -> in_1
	# now $t1 is in_1
	lw $t1 -528 ($sp)
	bne $t1 1 label3
	li $v0 5
	syscall
# $t2: None -> t1
	# now $t2 is t1
	move $t2 $v0
	sw $t2 -532 ($sp)
	# read int t1
	li $v0 12
	syscall
# $t3: None -> c2
	# now $t3 is c2
	move $t3 $v0
	sb $t3 -4 ($sp)
	# read char c2
	li $v0 12
	syscall
# $t4: None -> c1
	# now $t4 is c1
	move $t4 $v0
	sb $t4 -3 ($sp)
	# read char c1
	li $v0 5
	syscall
# $t5: None -> t2
	# now $t5 is t2
	move $t5 $v0
	sw $t5 -576 ($sp)
	# read int t2
# $t6: None -> t1
	# now $t6 is t1
	lw $t6 -532 ($sp)
# $t7: None -> c2
	# now $t7 is c2
	lbu $t7 -4 ($sp)
# $s0: None -> #11
	# now $s0 is #11
	mul $s0 $t6 $t7
# $s1: None -> c2
	# now $s1 is c2
	lbu $s1 -4 ($sp)
# $s2: None -> #12
	# now $s2 is #12
	addu $s2 $s1 $s0
# $s3: None -> t1
	# now $s3 is t1
	lw $s3 -532 ($sp)
# $s4: None -> c1
	# now $s4 is c1
	lbu $s4 -3 ($sp)
# $s5: None -> #13
	# now $s5 is #13
	div $s5 $s3 $s4
# $s6: None -> #14
	# now $s6 is #14
	subu $s6 $s2 $s5
	li $v0 1
	move $a0 $s6
	syscall
	# print int #14
	li $v0 4
	la $a0 string_2
	syscall
	# print str 2
	li $v0 4
	la $a0 string_3
	syscall
	# print str 3
	li $v0 4
	la $a0 string_4
	syscall
	# print str 4
	li $v0 11
# $s7: None -> c2
	# now $s7 is c2
	lbu $s7 -4 ($sp)
	move $a0 $s7
	syscall
	# print char c2
	li $t9 43
	sb $t9 -211 ($sp)
# save array: single_chars[0] = '+'
	li $t9 45
	sb $t9 -212 ($sp)
# save array: single_chars[1] = '-'
	li $t9 42
	sb $t9 -213 ($sp)
# save array: single_chars[2] = '*'
	li $t9 47
	sb $t9 -214 ($sp)
# save array: single_chars[3] = '/'
	li $t9 48
	sb $t9 -215 ($sp)
# save array: single_chars[4] = '0'
	li $t9 57
	sb $t9 -216 ($sp)
# save array: single_chars[5] = '9'
	li $t9 97
	sb $t9 -217 ($sp)
# save array: single_chars[6] = 'a'
	li $t9 122
	sb $t9 -218 ($sp)
# save array: single_chars[7] = 'z'
	li $t9 65
	sb $t9 -219 ($sp)
# save array: single_chars[8] = 'A'
	li $t9 90
	sb $t9 -220 ($sp)
# save array: single_chars[9] = 'Z'
# $fp: None -> _c1
	# now $fp is _c1
	li $fp 43
	sb $fp __c1
# $t0: None -> _c3
	# now $t0 is _c3
	li $t0 97
	sb $t0 __c3
# $t1: None -> _c1
	# now $t1 is _c1
	lbu $t1 __c1
# $t2: None -> t3
	# now $t2 is t3
	addi $t2 $t1 2
	sw $t2 -596 ($sp)
# $t3: None -> _c3
	# now $t3 is _c3
	lbu $t3 __c3
# $t4: None -> #15
	# now $t4 is #15
	subu $t4 $0 $t3
# $t5: None -> t4
	# now $t5 is t4
	addi $t5 $t4 77
	sw $t5 -600 ($sp)
# $t6: None -> #16
	# now $t6 is #16
	li $t6 -1
# $t7: None -> #17
	# now $t7 is #17
	addi $t7 $t6 45
# $s0: None -> t5
	# now $s0 is t5
	addi $s0 $t7 1
	sw $s0 -604 ($sp)
# $s1: None -> t3
	# now $s1 is t3
	lw $s1 -596 ($sp)
# $s2: None -> t5
	# now $s2 is t5
	lw $s2 -604 ($sp)
	beq $s1 $s2 label4
	li $v0 4
	la $a0 string_5
	syscall
	# print str 5
label4:
# $s3: None -> t3
	# now $s3 is t3
	lw $s3 -596 ($sp)
# $s4: None -> t4
	# now $s4 is t4
	lw $s4 -600 ($sp)
	bne $s3 $s4 label5
	li $v0 4
	la $a0 string_6
	syscall
	# print str 6
label5:
# $s5: None -> t3
	# now $s5 is t3
	lw $s5 -596 ($sp)
# $s6: None -> t4
	# now $s6 is t4
	lw $s6 -600 ($sp)
	bgt $s5 $s6 label6
	li $v0 4
	la $a0 string_7
	syscall
	# print str 7
label6:
# $s7: None -> t3
	# now $s7 is t3
	lw $s7 -596 ($sp)
# $fp: None -> t5
	# now $fp is t5
	lw $fp -604 ($sp)
	bge $s7 $fp label7
	li $v0 4
	la $a0 string_8
	syscall
	# print str 8
label7:
# $t0: None -> t4
	# now $t0 is t4
	lw $t0 -600 ($sp)
# $t1: None -> t5
	# now $t1 is t5
	lw $t1 -604 ($sp)
	blt $t0 $t1 label8
	li $v0 4
	la $a0 string_9
	syscall
	# print str 9
label8:
# $t2: None -> t5
	# now $t2 is t5
	lw $t2 -604 ($sp)
# $t3: None -> t3
	# now $t3 is t3
	lw $t3 -596 ($sp)
	ble $t2 $t3 label9
	li $v0 4
	la $a0 string_10
	syscall
	# print str 10
label9:
# $t4: None -> t6
	# now $t4 is t6
	li $t4 12
	sw $t4 -608 ($sp)
# $t5: None -> t7
	# now $t5 is t7
	li $t5 23
	sw $t5 -612 ($sp)
# $t6: None -> t8
	# now $t6 is t8
	li $t6 -23
	sw $t6 -616 ($sp)
# $t7: None -> t8
	# now $t7 is t8
	lw $t7 -616 ($sp)
# $s0: None -> t6
	# now $s0 is t6
	lw $s0 -608 ($sp)
# $s1: None -> #18
	# now $s1 is #18
	addu $s1 $t7 $s0
# $s2: None -> t7
	# now $s2 is t7
	lw $s2 -612 ($sp)
# $s3: None -> #19
	# now $s3 is #19
	addu $s3 $s1 $s2
	beq $s3 12 label10
	li $v0 4
	la $a0 string_11
	syscall
	# print str 11
label10:
	j label11
	li $v0 4
	la $a0 string_12
	syscall
	# print str 12
label11:
# $s4: None -> t9
	# now $s4 is t9
	li $s4 9
	sw $s4 -620 ($sp)
# $s5: None -> c3
	# now $s5 is c3
	li $s5 51
	sb $s5 -5 ($sp)
# $s6: None -> c4
	# now $s6 is c4
	li $s6 52
	sb $s6 -6 ($sp)
# $s7: None -> c4
	# now $s7 is c4
	lbu $s7 -6 ($sp)
# $fp: None -> c3
	# now $fp is c3
	lbu $fp -5 ($sp)
# $t0: None -> #20
	# now $t0 is #20
	subu $t0 $s7 $fp
# $t1: None -> t9
	# now $t1 is t9
	lw $t1 -620 ($sp)
# $t2: None -> #21
	# now $t2 is #21
	addu $t2 $t0 $t1
	beq $t2 10 label12
	li $v0 4
	la $a0 string_13
	syscall
	# print str 13
label12:
label3:
# $t3: None -> in_1
	# now $t3 is in_1
	lw $t3 -528 ($sp)
	bne $t3 2 label13
	li $t9 2333
	sw $t9 -624 ($sp)
# save array: t_array1[0] = 2333
	li $t9 47
	sb $t9 -11 ($sp)
# save array: c_array1[0] = '/'
# $t4: None -> #22
	# now $t4 is #22
	li $t4 -7
# $t5: None -> t10
	# now $t5 is t10
	addi $t5 $t4 9
	sw $t5 -536 ($sp)
# $t6: None -> c5
	# now $t6 is c5
	li $t6 43
	sb $t6 -7 ($sp)
# $t7: None -> c5
	# now $t7 is c5
	lbu $t7 -7 ($sp)
# $s0: None -> c6
	# now $s0 is c6
	move $s0 $t7
	sb $s0 -8 ($sp)
# $s1: None -> c7
	# now $s1 is c7
	lbu $s1 -11($sp)
	sb $s1 -9 ($sp)
# read array: c7 = c_array1[0]
# $s2: None -> t11
	# now $s2 is t11
	li $s2 -7
	sw $s2 -540 ($sp)
# $s3: None -> t11
	# now $s3 is t11
	lw $s3 -540 ($sp)
# $s4: None -> t12
	# now $s4 is t12
	move $s4 $s3
	sw $s4 -544 ($sp)
# $s5: None -> t13
	# now $s5 is t13
	lw $s5 -624($sp)
	sw $s5 -548 ($sp)
# read array: t13 = t_array1[0]
	# save start
	sw $ra -1504 ($sp)
	addi $sp $sp -1424
	jal func_ff2
	# recover start
	addi $sp $sp 1424
	lw $ra -1504 ($sp)
	# recover end
# $s6: None -> t14
	# now $s6 is t14
	move $s6 $v0
	sw $s6 -552 ($sp)
	li $t9 121
	sw $t9 -1424 ($sp)
# push param: 'y'
	# save start
	sw $ra -1504 ($sp)
	addi $sp $sp -1424
	jal func_ff1
	# recover start
	addi $sp $sp 1424
	lw $ra -1504 ($sp)
	# recover end
# $s7: None -> c8
	# now $s7 is c8
	move $s7 $v0
	sb $s7 -10 ($sp)
# $fp: None -> t10
	# now $fp is t10
	lw $fp -536 ($sp)
# $t0: None -> c5
	# now $t0 is c5
	lbu $t0 -7 ($sp)
# $t1: None -> #23
	# now $t1 is #23
	addu $t1 $fp $t0
# $t2: None -> c6
	# now $t2 is c6
	lbu $t2 -8 ($sp)
# $t3: None -> #24
	# now $t3 is #24
	addu $t3 $t1 $t2
# $t4: None -> c7
	# now $t4 is c7
	lbu $t4 -9 ($sp)
# $t5: None -> #25
	# now $t5 is #25
	addu $t5 $t3 $t4
# $t6: None -> t11
	# now $t6 is t11
	lw $t6 -540 ($sp)
# $t7: None -> #26
	# now $t7 is #26
	addu $t7 $t5 $t6
# $s0: None -> t12
	# now $s0 is t12
	lw $s0 -544 ($sp)
# $s1: None -> #27
	# now $s1 is #27
	addu $s1 $t7 $s0
# $s2: None -> t13
	# now $s2 is t13
	lw $s2 -548 ($sp)
# $s3: None -> #28
	# now $s3 is #28
	addu $s3 $s1 $s2
# $s4: None -> t14
	# now $s4 is t14
	lw $s4 -552 ($sp)
# $s5: None -> #29
	# now $s5 is #29
	addu $s5 $s3 $s4
# $s6: None -> c8
	# now $s6 is c8
	lbu $s6 -10 ($sp)
# $s7: None -> t14
	# now $s7 is t14
	addu $s7 $s5 $s6
	sw $s7 -552 ($sp)
# $fp: None -> t11
	# now $fp is t11
	lw $fp -540 ($sp)
# $t0: None -> #30
	# now $t0 is #30
	mul $t0 $fp -7
# $t1: None -> t13
	# now $t1 is t13
	lw $t1 -548 ($sp)
# $t2: None -> #31
	# now $t2 is #31
	mul $t2 $t0 $t1
# $t3: None -> c8
	# now $t3 is c8
	lbu $t3 -10 ($sp)
# $t4: None -> #32
	# now $t4 is #32
	div $t4 $t2 $t3
# $t5: None -> t10
	# now $t5 is t10
	lw $t5 -536 ($sp)
# $t6: None -> #33
	# now $t6 is #33
	div $t6 $t4 $t5
# $t7: None -> t12
	# now $t7 is t12
	lw $t7 -544 ($sp)
# $s0: None -> #34
	# now $s0 is #34
	mul $s0 $t6 $t7
	li $v0 1
	move $a0 $s0
	syscall
	# print int #34
	li $v0 4
	la $a0 string_14
	syscall
	# print str 14
# $s1: None -> t14
	# now $s1 is t14
	lw $s1 -552 ($sp)
# $s2: None -> #35
	# now $s2 is #35
	addi $s2 $s1 4
	li $v0 1
	move $a0 $s2
	syscall
	# print int #35
	li $v0 4
	la $a0 string_14
	syscall
	# print str 14
# $s3: None -> #36
	# now $s3 is #36
	li $s3 -1
# $s4: None -> #37
	# now $s4 is #37
	subu $s4 $0 $s3
	li $v0 1
	move $a0 $s4
	syscall
	# print int #37
# $s5: None -> #38
	# now $s5 is #38
	addu $s5 $0 $0
	beq $s5 0 label14
	li $v0 4
	la $a0 string_15
	syscall
	# print str 15
	j label15
label14:
# $s6: None -> t15
	# now $s6 is t15
	li $s6 1
	sw $s6 -556 ($sp)
label15:
	
	j label17
	li $v0 4
	la $a0 string_16
	syscall
	# print str 16
	j label18
label17:
	
# $s7: None -> t15
	# now $s7 is t15
	lw $s7 -556 ($sp)
	blez $s7 label20
# $fp: None -> t15
	# now $fp is t15
	lw $fp -556 ($sp)
	bgtz $fp label21
	li $v0 4
	la $a0 string_17
	syscall
	# print str 17
	j label22
label21:
	li $v0 4
	la $a0 string_18
	syscall
	# print str 18
label22:
label20:
label19:
label18:
	j label23
label16:
	li $v0 4
	la $a0 string_19
	syscall
	# print str 19
label23:
# $t0: None -> t16
	# now $t0 is t16
	li $t0 1
	sw $t0 -560 ($sp)
# $t1: None -> t18
	# now $t1 is t18
	addu $t1 $0 $0
	sw $t1 -568 ($sp)
label24:
# $t2: None -> t16
	# now $t2 is t16
	lw $t2 -560 ($sp)
	bgt $t2 4 label25
# $t3: None -> t17
	# now $t3 is t17
	li $t3 1
	sw $t3 -564 ($sp)
label26:
# $t4: None -> t17
	# now $t4 is t17
	lw $t4 -564 ($sp)
# $t5: None -> t16
	# now $t5 is t16
	lw $t5 -560 ($sp)
	bge $t4 $t5 label27
# $t6: None -> t18
	# now $t6 is t18
	lw $t6 -568 ($sp)
# $t7: None -> t17
	# now $t7 is t17
	lw $t7 -564 ($sp)
	addu $t6 $t6 $t7
	sw $t6 -568 ($sp)
# $s0: None -> t17
	# now $s0 is t17
	lw $s0 -564 ($sp)
	addi $s0 $s0 1
	sw $s0 -564 ($sp)
	j label26
label27:
# $s1: None -> t16
	# now $s1 is t16
	lw $s1 -560 ($sp)
	addi $s1 $s1 1
	sw $s1 -560 ($sp)
	j label24
label25:
# $s2: None -> t19
	# now $s2 is t19
	addu $s2 $0 $0
	sw $s2 -572 ($sp)
# $s3: None -> t20
	# now $s3 is t20
	li $s3 2
	sw $s3 -580 ($sp)
label28:
# $s4: None -> t22
	# now $s4 is t22
	li $s4 1
	sw $s4 -588 ($sp)
# $s5: None -> t21
	# now $s5 is t21
	li $s5 2
	sw $s5 -584 ($sp)
label29:
# $s6: None -> t22
	# now $s6 is t22
	lw $s6 -588 ($sp)
# $s7: None -> t21
	# now $s7 is t21
	lw $s7 -584 ($sp)
	mul $s6 $s6 $s7
	sw $s6 -588 ($sp)
# $fp: None -> t21
	# now $fp is t21
	lw $fp -584 ($sp)
	addi $fp $fp 2
	sw $fp -584 ($sp)
# $t0: None -> t21
	# now $t0 is t21
	lw $t0 -584 ($sp)
# $t1: None -> t20
	# now $t1 is t20
	lw $t1 -580 ($sp)
	blt $t0 $t1 label29
# $t2: None -> t19
	# now $t2 is t19
	lw $t2 -572 ($sp)
# $t3: None -> t22
	# now $t3 is t22
	lw $t3 -588 ($sp)
	addu $t2 $t2 $t3
	sw $t2 -572 ($sp)
# $t4: None -> t20
	# now $t4 is t20
	lw $t4 -580 ($sp)
	addi $t4 $t4 1
	sw $t4 -580 ($sp)
# $t5: None -> t20
	# now $t5 is t20
	lw $t5 -580 ($sp)
	ble $t5 5 label28
# $t6: None -> t20
	# now $t6 is t20
	li $t6 100
	sw $t6 -580 ($sp)
label30:
# $t7: None -> t22
	# now $t7 is t22
	li $t7 1
	sw $t7 -588 ($sp)
# $s0: None -> t21
	# now $s0 is t21
	li $s0 100
	sw $s0 -584 ($sp)
label31:
# $s1: None -> t22
	# now $s1 is t22
	lw $s1 -588 ($sp)
# $s2: None -> t21
	# now $s2 is t21
	lw $s2 -584 ($sp)
	mul $s1 $s1 $s2
	sw $s1 -588 ($sp)
# $s3: None -> t21
	# now $s3 is t21
	lw $s3 -584 ($sp)
	addi $s3 $s3 -2
	sw $s3 -584 ($sp)
# $s4: None -> t21
	# now $s4 is t21
	lw $s4 -584 ($sp)
# $s5: None -> t20
	# now $s5 is t20
	lw $s5 -580 ($sp)
	bgt $s4 $s5 label31
# $s6: None -> t19
	# now $s6 is t19
	lw $s6 -572 ($sp)
# $s7: None -> t22
	# now $s7 is t22
	lw $s7 -588 ($sp)
	addu $s6 $s6 $s7
	sw $s6 -572 ($sp)
# $fp: None -> t20
	# now $fp is t20
	lw $fp -580 ($sp)
	addi $fp $fp -1
	sw $fp -580 ($sp)
# $t0: None -> t20
	# now $t0 is t20
	lw $t0 -580 ($sp)
	bge $t0 97 label30
# $t1: None -> #39
	# now $t1 is #39
	addu $t1 $0 $0
	bge $t1 1 label32
	li $v0 4
	la $a0 string_18
	syscall
	# print str 18
label32:
label33:
	
# $t2: None -> t23
	# now $t2 is t23
	addu $t2 $0 $0
	sw $t2 -592 ($sp)
label35:
# $t3: None -> t23
	# now $t3 is t23
	lw $t3 -592 ($sp)
	addi $t3 $t3 2
	sw $t3 -592 ($sp)
# $t4: None -> t23
	# now $t4 is t23
	lw $t4 -592 ($sp)
	ble $t4 60 label36
	li $v0 4
	la $a0 string_14
	syscall
	# print str 14
# $t5: None -> t18
	# now $t5 is t18
	lw $t5 -568 ($sp)
# $t6: None -> t19
	# now $t6 is t19
	lw $t6 -572 ($sp)
# $t7: None -> #40
	# now $t7 is #40
	addu $t7 $t5 $t6
# $s0: None -> t23
	# now $s0 is t23
	lw $s0 -592 ($sp)
# $s1: None -> #41
	# now $s1 is #41
	addu $s1 $t7 $s0
	li $v0 1
	move $a0 $s1
	syscall
	# print int #41
	j exit
label36:
# $s2: None -> t23
	# now $s2 is t23
	lw $s2 -592 ($sp)
	addi $s2 $s2 1
	sw $s2 -592 ($sp)
# $s3: None -> t23
	# now $s3 is t23
	lw $s3 -592 ($sp)
	blt $s3 100 label35
	j label33
label34:
	li $v0 4
	la $a0 string_20
	syscall
	# print str 20
label13:
# $s4: None -> in_1
	# now $s4 is in_1
	lw $s4 -528 ($sp)
	bne $s4 3 label37
	li $t9 1
	sw $t9 -1424 ($sp)
# push param: 1
	# save start
	sw $ra -1516 ($sp)
	addi $sp $sp -1424
	jal func_factorial
	# recover start
	addi $sp $sp 1424
	lw $ra -1516 ($sp)
	# recover end
# $s5: None -> #42
	# now $s5 is #42
	move $s5 $v0
	li $t9 2
	sw $t9 -1424 ($sp)
# push param: 2
	# save start
	sw $s5 -1448 ($sp)
	sw $ra -1516 ($sp)
	addi $sp $sp -1424
	jal func_factorial
	# recover start
	addi $sp $sp 1424
	lw $ra -1516 ($sp)
	lw $s5 -1448 ($sp)
	# recover end
# $s6: None -> #43
	# now $s6 is #43
	move $s6 $v0
# $s7: None -> #44
	# now $s7 is #44
	addu $s7 $s5 $s6
	li $t9 5
	sw $t9 -1424 ($sp)
# push param: 5
	# save start
	sw $s7 -1448 ($sp)
	sw $ra -1516 ($sp)
	addi $sp $sp -1424
	jal func_factorial
	# recover start
	addi $sp $sp 1424
	lw $ra -1516 ($sp)
	lw $s7 -1448 ($sp)
	# recover end
# $fp: None -> #45
	# now $fp is #45
	move $fp $v0
# $t0: None -> #46
	# now $t0 is #46
	addu $t0 $s7 $fp
	li $v0 1
	move $a0 $t0
	syscall
	# print int #46
# $t1: None -> _c1
	# now $t1 is _c1
	li $t1 97
	sb $t1 __c1
	li $t9 43
	sw $t9 -1424 ($sp)
# push param: '+'
	# save start
	sw $ra -1504 ($sp)
	addi $sp $sp -1424
	jal func_ff1
	# recover start
	addi $sp $sp 1424
	lw $ra -1504 ($sp)
	# recover end
	li $v0 11
# $t2: None -> _c1
	# now $t2 is _c1
	lbu $t2 __c1
	move $a0 $t2
	syscall
	# print char _c1
# $t3: None -> _c2
	# now $t3 is _c2
	li $t3 98
	sb $t3 __c2
	# save start
	sw $ra -1504 ($sp)
	addi $sp $sp -1424
	jal func_ff2
	# recover start
	addi $sp $sp 1424
	lw $ra -1504 ($sp)
	# recover end
	li $v0 11
# $t4: None -> _c2
	# now $t4 is _c2
	lbu $t4 __c2
	move $a0 $t4
	syscall
	# print char _c2
	li $t9 1
	sw $t9 -1424 ($sp)
# push param: 1
	li $t9 2
	sw $t9 -1428 ($sp)
# push param: 2
	li $t9 97
	sw $t9 -1432 ($sp)
# push param: 'a'
	li $t9 3
	sw $t9 -1436 ($sp)
# push param: 3
	li $t9 98
	sw $t9 -1440 ($sp)
# push param: 'b'
	li $t9 99
	sw $t9 -1444 ($sp)
# push param: 'c'
	# save start
	sw $ra -1544 ($sp)
	addi $sp $sp -1424
	jal func_ff3
	# recover start
	addi $sp $sp 1424
	lw $ra -1544 ($sp)
	# recover end
	# save start
	sw $ra -1500 ($sp)
	addi $sp $sp -1424
	jal func_ff4
	# recover start
	addi $sp $sp 1424
	lw $ra -1500 ($sp)
	# recover end
# $t5: None -> _c1
	# now $t5 is _c1
	li $t5 42
	sb $t5 __c1
	# save start
	sw $ra -1512 ($sp)
	addi $sp $sp -1424
	jal func_ff5
	# recover start
	addi $sp $sp 1424
	lw $ra -1512 ($sp)
	# recover end
# $t6: None -> _c4
	# now $t6 is _c4
	li $t6 6666
	sw $t6 -520 ($sp)
# $t7: None -> _t1
	# now $t7 is _t1
	li $t7 56
	sb $t7 -2 ($sp)
# $s0: None -> _c4
	# now $s0 is _c4
	lw $s0 -520 ($sp)
# $s1: None -> _t1
	# now $s1 is _t1
	lbu $s1 -2 ($sp)
# $s2: None -> #47
	# now $s2 is #47
	addu $s2 $s0 $s1
	li $v0 1
	move $a0 $s2
	syscall
	# print int #47
	li $t9 104
	sb $t9 -161 ($sp)
# save array: c_array2[50] = 'h'
# $s3: None -> #48
	# now $s3 is #48
	lbu $s3 -161($sp)
# read array: #48 = c_array2[50]
	li $v0 11
	move $a0 $s3
	syscall
	# print char #48
	li $t9 103
	sw $t9 -1424 ($sp)
# push param: 'g'
	# save start
	sw $ra -1504 ($sp)
	addi $sp $sp -1424
	jal func_ff1
	# recover start
	addi $sp $sp 1424
	lw $ra -1504 ($sp)
	# recover end
# $s4: None -> #49
	# now $s4 is #49
	move $s4 $v0
	li $v0 11
	move $a0 $s4
	syscall
	# print char #49
	li $v0 1
	li $a0 114
	syscall
	# print int 'r'
# $s5: None -> i
	# now $s5 is i
	addu $s5 $0 $0
	sw $s5 -524 ($sp)
label38:
# $s6: None -> i
	# now $s6 is i
	lw $s6 -524 ($sp)
	sll $t8 $s6 2
	addi $t8 $t8 1024
	
	subu $t8 $sp $t8
	sw $s6 ($t8)
# save array: t_array2[i] = i
# $s7: None -> i
	# now $s7 is i
	lw $s7 -524 ($sp)
	addi $s7 $s7 1
	sw $s7 -524 ($sp)
# $fp: None -> i
	# now $fp is i
	lw $fp -524 ($sp)
	blt $fp 100 label38
# $t0: None -> #50
	# now $t0 is #50
	li $t0 8
# $t1: None -> #51
	# now $t1 is #51
	mul $t1 $t0 6
# $t2: None -> #52
	# now $t2 is #52
	li $t2 12
# $t3: None -> #53
	# now $t3 is #53
	addu $t3 $t1 $t2
# $t4: None -> #54
	# now $t4 is #54
	sll $t9 $t3 2
	addi $t9 $t9 1024
	subu $t9 $sp $t9
	lw $t4 ($t9)
# read array: #54 = t_array2[#53]
# $t5: None -> #55
	# now $t5 is #55
	div $t5 $t4 23
# $t6: None -> i
	# now $t6 is i
	lw $t6 -524 ($sp)
# $t7: None -> #56
	# now $t7 is #56
	mul $t7 $t6 22
# $s0: None -> #57
	# now $s0 is #57
	div $s0 $t7 23
# $s1: None -> #58
	# now $s1 is #58
	lw $s1 -1028($sp)
# read array: #58 = t_array2[1]
# $s2: None -> #59
	# now $s2 is #59
	mul $s2 $s1 1000
# $s3: None -> #60
	# now $s3 is #60
	mul $s3 $s0 $s2
# $s4: None -> #61
	# now $s4 is #61
	div $s4 $s3 1000
# $s5: None -> #62
	# now $s5 is #62
	li $s5 3
# $s6: None -> #63
	# now $s6 is #63
	addu $s6 $s4 $s5
# $s7: None -> #64
	# now $s7 is #64
	sll $t9 $s6 2
	addi $t9 $t9 1024
	subu $t9 $sp $t9
	lw $s7 ($t9)
# read array: #64 = t_array2[#63]
# $fp: None -> #65
	# now $fp is #65
	div $fp $s7 30
# $t0: None -> #66
	# now $t0 is #66
	addu $t0 $t5 $fp
# $t1: None -> i
	# now $t1 is i
	sll $t9 $t0 2
	addi $t9 $t9 1024
	subu $t9 $sp $t9
	lw $t1 ($t9)
	sw $t1 -524 ($sp)
# read array: i = t_array2[#66]
# $t2: None -> #67
	# now $t2 is #67
	li $t2 8
# $t3: None -> #68
	# now $t3 is #68
	mul $t3 $t2 6
# $t4: None -> #69
	# now $t4 is #69
	li $t4 12
# $t5: None -> #70
	# now $t5 is #70
	addu $t5 $t3 $t4
# $t6: None -> #71
	# now $t6 is #71
	sll $t9 $t5 2
	addi $t9 $t9 1024
	subu $t9 $sp $t9
	lw $t6 ($t9)
# read array: #71 = t_array2[#70]
# $t7: None -> #72
	# now $t7 is #72
	div $t7 $t6 23
# $s0: None -> i
	# now $s0 is i
	lw $s0 -524 ($sp)
# $s1: None -> #73
	# now $s1 is #73
	mul $s1 $s0 22
# $s2: None -> #74
	# now $s2 is #74
	div $s2 $s1 23
# $s3: None -> #75
	# now $s3 is #75
	lw $s3 -1028($sp)
# read array: #75 = t_array2[1]
# $s4: None -> #76
	# now $s4 is #76
	mul $s4 $s3 1000
# $s5: None -> #77
	# now $s5 is #77
	mul $s5 $s2 $s4
# $s6: None -> #78
	# now $s6 is #78
	div $s6 $s5 1000
# $s7: None -> #79
	# now $s7 is #79
	li $s7 3
# $fp: None -> #80
	# now $fp is #80
	addu $fp $s6 $s7
# $t0: None -> #81
	# now $t0 is #81
	sll $t9 $fp 2
	addi $t9 $t9 1024
	subu $t9 $sp $t9
	lw $t0 ($t9)
# read array: #81 = t_array2[#80]
# $t1: None -> #82
	# now $t1 is #82
	div $t1 $t0 30
# $t2: None -> #83
	# now $t2 is #83
	addu $t2 $t7 $t1
# $t3: None -> #84
	# now $t3 is #84
	sll $t9 $t2 2
	addi $t9 $t9 1024
	subu $t9 $sp $t9
	lw $t3 ($t9)
# read array: #84 = t_array2[#83]
	sw $t3 -1424 ($sp)
# push param: #84
	# save start
	sw $ra -1516 ($sp)
	addi $sp $sp -1424
	jal func_factorial
	# recover start
	addi $sp $sp 1424
	lw $ra -1516 ($sp)
	# recover end
# $t4: None -> #85
	# now $t4 is #85
	move $t4 $v0
	li $v0 1
	move $a0 $t4
	syscall
	# print int #85
label37:
	j exit
exit:
