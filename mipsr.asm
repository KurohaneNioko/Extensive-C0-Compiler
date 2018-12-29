.data
_var4 : .byte 0
_varraychar : .space 20
.align 2
_var1 : .word 0
_var2 : .word 0
_varray : .space 40
string_7 : .asciiz "! #$%&'()*+,-./0123456789:;<=>?@ABCXYZabcxyz[\\]^_{|}~\n"
string_6 : .asciiz "error!\n"
string_4 : .asciiz "error\n"
string_3 : .asciiz "fib number is:\n"
string_1 : .asciiz "fibnum is too big\n"
string_2 : .asciiz "fibnum is too small\n"
string_5 : .asciiz "your input is correct!\n"
.text
.globl main
func_add:
# $t0: None -> a
	# now $t0 is a
	lw $t0 -0 ($sp)
# $t1: None -> b
	# now $t1 is b
	lw $t1 -4 ($sp)
# $t2: None -> c
	# now $t2 is c
	addu $t2 $t0 $t1
	sw $t2 -12 ($sp)
# $t3: None -> c
	# now $t3 is c
	lw $t3 -12 ($sp)
	move $v0 $t3
	jr $ra
	jr $ra
func_fortest:
# $t0: None -> i
	# now $t0 is i
	addu $t0 $0 $0
	sw $t0 -20 ($sp)
label1:
# $t1: None -> i
	# now $t1 is i
	lw $t1 -20 ($sp)
	bne $t1 7 label2
	li $v0 1
# $t2: None -> i
	# now $t2 is i
	lw $t2 -20 ($sp)
	move $a0 $t2
	syscall
	# print int i
	j label3
label2:
# $t3: None -> i
	# now $t3 is i
	lw $t3 -20 ($sp)
	bne $t3 8 label4
	li $v0 1
# $t4: None -> i
	# now $t4 is i
	lw $t4 -20 ($sp)
	move $a0 $t4
	syscall
	# print int i
label4:
label3:
# $t5: None -> i
	# now $t5 is i
	lw $t5 -20 ($sp)
	addi $t5 $t5 2
	sw $t5 -20 ($sp)
# $t6: None -> i
	# now $t6 is i
	lw $t6 -20 ($sp)
	ble $t6 10 label1
# $t7: None -> i
	# now $t7 is i
	addu $t7 $0 $0
	sw $t7 -20 ($sp)
label5:
# $s0: None -> #1
	# now $s0 is #1
	li $s0 1
# $s1: None -> #2
	# now $s1 is #2
	li $s1 3
# $s2: None -> #3
	# now $s2 is #3
	li $s2 6
# $s3: None -> #4
	# now $s3 is #4
	addu $s3 $0 $0
# $s4: None -> var1
	# now $s4 is var1
	li $s4 10
	sw $s4 _var1
label6:
# $s5: None -> var1
	# now $s5 is var1
	lw $s5 _var1
	addi $s5 $s5 -8
	sw $s5 _var1
# $s6: None -> var1
	# now $s6 is var1
	lw $s6 _var1
	bgez $s6 label6
# $s7: None -> i
	# now $s7 is i
	lw $s7 -20 ($sp)
	addi $s7 $s7 -5
	sw $s7 -20 ($sp)
	bne $s3 0 label5
	li $v0 1
# $fp: None -> var1
	# now $fp is var1
	lw $fp _var1
	move $a0 $fp
	syscall
	# print int var1
	jr $ra
	jr $ra
func_exptest:
	li $v0 5
	syscall
# $t0: None -> a
	# now $t0 is a
	move $t0 $v0
	sw $t0 -20 ($sp)
	# read int a
	li $v0 12
	syscall
# $t1: None -> b
	# now $t1 is b
	move $t1 $v0
	sb $t1 -0 ($sp)
	# read char b
# $t2: None -> #5
	# now $t2 is #5
	li $t2 -10
# $t3: None -> #6
	# now $t3 is #6
	li $t3 10
# $t4: None -> a
	# now $t4 is a
	lw $t4 -20 ($sp)
# $t5: None -> #7
	# now $t5 is #7
	mul $t5 $t4 10
# $t6: None -> a
	# now $t6 is a
	divu $t6 $t5 5
	sw $t6 -20 ($sp)
# $t7: None -> #8
	# now $t7 is #8
	li $t7 -97
# $s0: None -> b
	# now $s0 is b
	lbu $s0 -0 ($sp)
# $s1: None -> c
	# now $s1 is c
	addi $s1 $s0 -97
	sw $s1 -24 ($sp)
# $s2: None -> c
	# now $s2 is c
	lw $s2 -24 ($sp)
	move $v0 $s2
	jr $ra
	jr $ra
func_arraytest:
	li $t9 1
	sw $t9 _varray+0
# save array: varray[0] = 1
	li $t9 2
	sw $t9 _varray+4
# save array: varray[1] = 2
	li $t9 3
	sw $t9 _varray+8
# save array: varray[2] = 3
	li $t9 4
	sw $t9 _varray+12
# save array: varray[3] = 4
	li $t9 5
	sw $t9 _varray+16
# save array: varray[4] = 5
# $t0: None -> #9
	# now $t0 is #9
	lw $t0 _varray+0
# read array: #9 = varray[0]
# $t1: None -> #10
	# now $t1 is #10
	lw $t1 _varray+0
# read array: #10 = varray[0]
# $t2: None -> #11
	# now $t2 is #11
	sll $t9 $t1 2
	lw $t2 _varray($t9)
	
# read array: #11 = varray[#10]
# $t3: None -> #12
	# now $t3 is #12
	addu $t3 $t0 $t2
# $t4: None -> #13
	# now $t4 is #13
	lw $t4 _varray+8
# read array: #13 = varray[2]
# $t5: None -> #14
	# now $t5 is #14
	addu $t5 $t3 $t4
# $t6: None -> #15
	# now $t6 is #15
	lw $t6 _varray+12
# read array: #15 = varray[3]
# $t7: None -> #16
	# now $t7 is #16
	addu $t7 $t5 $t6
# $s0: None -> #17
	# now $s0 is #17
	lw $s0 _varray+16
# read array: #17 = varray[4]
	move $v0 $t7
	jr $ra
	jr $ra
func_fib:
# $t0: None -> a
	# now $t0 is a
	lw $t0 -0 ($sp)
	bne $t0 1 label7
	li $v0 1
	jr $ra
label7:
# $t1: None -> a
	# now $t1 is a
	lw $t1 -0 ($sp)
	bne $t1 2 label8
	li $v0 1
	jr $ra
label8:
# $t2: None -> a
	# now $t2 is a
	lw $t2 -0 ($sp)
# $t3: None -> #18
	# now $t3 is #18
	addi $t3 $t2 -1
	sw $t3 -96 ($sp)
# push param: #18
	# save start
	sw $ra -188 ($sp)
	addi $sp $sp -96
	jal func_fib
	# recover start
	addi $sp $sp 96
	lw $ra -188 ($sp)
	# recover end
# $t4: None -> #19
	# now $t4 is #19
	move $t4 $v0
# $t5: None -> a
	# now $t5 is a
	lw $t5 -0 ($sp)
# $t6: None -> #20
	# now $t6 is #20
	addi $t6 $t5 -2
	sw $t6 -96 ($sp)
# push param: #20
	# save start
	sw $t4 -120 ($sp)
	sw $ra -188 ($sp)
	addi $sp $sp -96
	jal func_fib
	# recover start
	addi $sp $sp 96
	lw $ra -188 ($sp)
	lw $t4 -120 ($sp)
	# recover end
# $t7: None -> #21
	# now $t7 is #21
	move $t7 $v0
	move $v0 $t4
	jr $ra
	jr $ra
func_whiletest:
label9:
# $t0: None -> a
	# now $t0 is a
	lw $t0 -0 ($sp)
	blez $t0 label10
# $t1: None -> a
	# now $t1 is a
	lw $t1 -0 ($sp)
	addi $t1 $t1 -3
	sw $t1 -0 ($sp)
	j label9
label10:
# $t2: None -> #22
	# now $t2 is #22
	li $t2 -2
# $t3: None -> a
	# now $t3 is a
	lw $t3 -0 ($sp)
	bne $t3 -2 label11
label12:
# $t4: None -> a
	# now $t4 is a
	lw $t4 -0 ($sp)
	bge $t4 15 label13
# $t5: None -> a
	# now $t5 is a
	lw $t5 -0 ($sp)
	addi $t5 $t5 5
	sw $t5 -0 ($sp)
# $t6: None -> a
	# now $t6 is a
	lw $t6 -0 ($sp)
	bne $t6 13 label14
# $t7: None -> a
	# now $t7 is a
	lw $t7 -0 ($sp)
	addi $t7 $t7 2
	sw $t7 -0 ($sp)
label14:
	j label12
label13:
label11:
	li $v0 1
# $s0: None -> a
	# now $s0 is a
	lw $s0 -0 ($sp)
	move $a0 $s0
	syscall
	# print int a
	jr $ra
func_calltest3:
# $t0: None -> var2
	# now $t0 is var2
	lw $t0 _var2
# $t1: None -> #23
	# now $t1 is #23
	addi $t1 $t0 -100
# $t2: None -> #24
	# now $t2 is #24
	lw $t2 _varray+12
# read array: #24 = varray[3]
# $t3: None -> #25
	# now $t3 is #25
	addu $t3 $t1 $t2
	beq $t3 0 label15
# $t4: None -> a
	# now $t4 is a
	lbu $t4 -0 ($sp)
	bne $t4 97 label16
# $t5: None -> a
	# now $t5 is a
	lbu $t5 -0 ($sp)
# $t6: None -> b
	# now $t6 is b
	lbu $t6 -4 ($sp)
# $t7: None -> #26
	# now $t7 is #26
	addu $t7 $t5 $t6
# $s0: None -> c
	# now $s0 is c
	lbu $s0 -8 ($sp)
# $s1: None -> #27
	# now $s1 is #27
	addu $s1 $t7 $s0
# $s2: None -> d
	# now $s2 is d
	lbu $s2 -12 ($sp)
# $s3: None -> #28
	# now $s3 is #28
	addu $s3 $s1 $s2
# $s4: None -> #29
	# now $s4 is #29
	move $s4 $s3
	li $v0 1
	move $a0 $s4
	syscall
	# print int #29
label16:
label15:
	jr $ra
func_calltest2:
# $t0: None -> var2
	# now $t0 is var2
	li $t0 100
	sw $t0 _var2
	li $t9 97
	sw $t9 -76 ($sp)
# push param: 97
	li $t9 42
	sw $t9 -80 ($sp)
# push param: 42
	li $t9 43
	sw $t9 -84 ($sp)
# push param: 43
	li $t9 56
	sw $t9 -88 ($sp)
# push param: 56
	# save start
	sw $ra -192 ($sp)
	addi $sp $sp -76
	jal func_calltest3
	# recover start
	addi $sp $sp 76
	lw $ra -192 ($sp)
	# recover end
# $t1: None -> var2
	# now $t1 is var2
	li $t1 30
	sw $t1 _var2
	jr $ra
func_calltest1:
	# save start
	sw $ra -148 ($sp)
	addi $sp $sp -76
	jal func_calltest2
	# recover start
	addi $sp $sp 76
	lw $ra -148 ($sp)
	# recover end
# $t0: None -> var2
	# now $t0 is var2
	li $t0 50
	sw $t0 _var2
	move $v0 $0
	jr $ra
	jr $ra
func_chartest:
	li $v0 72
	jr $ra
	jr $ra
func_chara:
# $t0: None -> x
	# now $t0 is x
	lw $t0 -0 ($sp)
	bne $t0 97 label17
	li $v0 97
	jr $ra
	j label18
label17:
	li $v0 122
	jr $ra
label18:
	jr $ra
main:
	li $t9 10
	sw $t9 -44 ($sp)
# push param: 10
	li $t9 20
	sw $t9 -48 ($sp)
# push param: 20
	# save start
	sw $ra -128 ($sp)
	addi $sp $sp -44
	jal func_add
	# recover start
	addi $sp $sp 44
	lw $ra -128 ($sp)
	# recover end
# $t0: None -> result
	# now $t0 is result
	move $t0 $v0
	li $v0 1
	move $a0 $t0
	syscall
	# print int result
	# save start
	sw $ra -140 ($sp)
	addi $sp $sp -44
	jal func_exptest
	# recover start
	addi $sp $sp 44
	lw $ra -140 ($sp)
	# recover end
# $t1: None -> #30
	# now $t1 is #30
	move $t1 $v0
	li $v0 1
	move $a0 $t1
	syscall
	# print int #30
	# save start
	sw $ra -152 ($sp)
	addi $sp $sp -44
	jal func_arraytest
	# recover start
	addi $sp $sp 44
	lw $ra -152 ($sp)
	# recover end
# $t2: None -> #31
	# now $t2 is #31
	move $t2 $v0
# $t3: None -> result
	# now $t3 is result
	addi $t3 $t2 5
	sw $t3 -40 ($sp)
	li $v0 1
# $t4: None -> result
	# now $t4 is result
	lw $t4 -40 ($sp)
	move $a0 $t4
	syscall
	# print int result
	li $v0 5
	syscall
# $t5: None -> fibnum
	# now $t5 is fibnum
	move $t5 $v0
	sw $t5 -36 ($sp)
	# read int fibnum
# $t6: None -> fibnum
	# now $t6 is fibnum
	lw $t6 -36 ($sp)
	ble $t6 10 label19
	li $v0 4
	la $a0 string_1
	syscall
	# print str 1
	j label20
label19:
# $t7: None -> fibnum
	# now $t7 is fibnum
	lw $t7 -36 ($sp)
	bge $t7 1 label21
	li $v0 4
	la $a0 string_2
	syscall
	# print str 2
	j label22
label21:
	li $v0 4
	la $a0 string_3
	syscall
	# print str 3
# $s0: None -> fibnum
	# now $s0 is fibnum
	lw $s0 -36 ($sp)
	sw $s0 -44 ($sp)
# push param: fibnum
	# save start
	sw $ra -136 ($sp)
	addi $sp $sp -44
	jal func_fib
	# recover start
	addi $sp $sp 44
	lw $ra -136 ($sp)
	# recover end
# $s1: None -> #32
	# now $s1 is #32
	move $s1 $v0
	li $v0 1
	move $a0 $s1
	syscall
	# print int #32
label22:
label20:
	li $t9 10
	sw $t9 -44 ($sp)
# push param: 10
	# save start
	sw $ra -124 ($sp)
	addi $sp $sp -44
	jal func_whiletest
	# recover start
	addi $sp $sp 44
	lw $ra -124 ($sp)
	# recover end
	# save start
	sw $ra -136 ($sp)
	addi $sp $sp -44
	jal func_fortest
	# recover start
	addi $sp $sp 44
	lw $ra -136 ($sp)
	# recover end
	li $v0 12
	syscall
# $s2: None -> var4
	# now $s2 is var4
	move $s2 $v0
	sb $s2 _var4
	# read char var4
# $s3: None -> #33
	# now $s3 is #33
	addu $s3 $0 $0
# $s4: None -> #34
	# now $s4 is #34
	lw $s4 _varray+0
# read array: #34 = varray[0]
# $s5: None -> #35
	# now $s5 is #35
	move $s5 $s4
# $s6: None -> #36
	# now $s6 is #36
	addi $s6 $s5 -1
	beq $s6 0 label23
	li $v0 4
	la $a0 string_4
	syscall
	# print str 4
label23:
	
# $s7: None -> var4
	# now $s7 is var4
	lbu $s7 _var4
# $fp: None -> #37
	# now $fp is #37
	move $fp $s7
	sw $fp -44 ($sp)
# push param: #37
	# save start
	sw $s3 -52 ($sp)
	sw $ra -120 ($sp)
	addi $sp $sp -44
	jal func_chara
	# recover start
	addi $sp $sp 44
	lw $ra -120 ($sp)
	lw $s3 -52 ($sp)
	# recover end
# $t0: None -> #38
	# now $t0 is #38
	move $t0 $v0
	bne $t0 97 label25
	li $v0 4
	la $a0 string_5
	syscall
	# print str 5
	j label26
label25:
	li $v0 4
	la $a0 string_6
	syscall
	# print str 6
label26:
label24:
	li $v0 4
	la $a0 string_7
	syscall
	# print str 7
	# save start
	sw $s3 -48 ($sp)
	sw $ra -116 ($sp)
	addi $sp $sp -44
	jal func_chartest
	# recover start
	addi $sp $sp 44
	lw $ra -116 ($sp)
	lw $s3 -48 ($sp)
	# recover end
# $t3: None -> #39
	# now $t3 is #39
	move $t3 $v0
	li $v0 11
	move $a0 $t3
	syscall
	# print char #39
	# save start
	sw $s3 -48 ($sp)
	sw $ra -116 ($sp)
	addi $sp $sp -44
	jal func_calltest1
	# recover start
	addi $sp $sp 44
	lw $ra -116 ($sp)
	lw $s3 -48 ($sp)
	# recover end
exit:
