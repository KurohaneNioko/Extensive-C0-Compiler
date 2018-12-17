.data
_m : .word 0
_n : .word 0
_stack : .space 48
_sum : .word 0
_used : .space 48
string_1 : .asciiz " \n"
string_4 : .asciiz "You can choose m numbers permutations from n numbers ? \n"
string_2 : .asciiz "___________\n"
string_5 : .asciiz "error input: 0 < m <= n <= 10\n"
string_3 : .asciiz "test for success\n"
.text
.globl main
func_permutations:
# $t0: None -> i
	# now $t0 is i
	add $t0 $0 $0
	sw $t0 -20 ($sp)
# $t1: None -> a
	# now $t1 is a
	lw $t1 -0 ($sp)
# $t2: None -> m
	# now $t2 is m
	lw $t2 _m
	bne $t1 $t2 label1
label2:
# $t3: None -> i
	# now $t3 is i
	lw $t3 -20 ($sp)
# $t4: None -> m
	# now $t4 is m
	lw $t4 _m
	bge $t3 $t4 label3
	li $v0 4
	la $a0 string_1
	syscall
	# print str 1
# $t5: None -> i
	# now $t5 is i
	lw $t5 -20 ($sp)
# $t6: None -> #1
	# now $t6 is #1
	sll $t9 $t5 2
	lw $t6 _stack($t9)
	
# read array: #1 = stack[i]
	li $v0 1
	move $a0 $t6
	syscall
	# print int #1
# $t7: None -> i
	# now $t7 is i
	lw $t7 -20 ($sp)
# $s0: None -> #2
	# now $s0 is #2
	add $s0 $t7 1
# $s1: None -> i
	# now $s1 is i
	move $s1 $s0
	sw $s1 -20 ($sp)
	j label2
label3:
	li $v0 4
	la $a0 string_2
	syscall
	# print str 2
	jr $ra
label1:
# $s2: None -> i
	# now $s2 is i
	li $s2 1
	sw $s2 -20 ($sp)
label4:
# $s3: None -> i
	# now $s3 is i
	lw $s3 -20 ($sp)
# $s4: None -> #3
	# now $s4 is #3
	sll $t9 $s3 2
	lw $s4 _used($t9)
	
# read array: #3 = used[i]
	beq $s4 0 label5
	j label6
label5:
# $s5: None -> i
	# now $s5 is i
	lw $s5 -20 ($sp)
# $s6: None -> a
	# now $s6 is a
	lw $s6 -0 ($sp)
	sll $t8 $s6 2
	sw $s5 _stack ($t8)
# save array: stack[a] = i
	li $t9 1
# $s7: None -> i
	# now $s7 is i
	lw $s7 -20 ($sp)
	sll $t8 $s7 2
	sw $t9 _used ($t8)
# save array: used[i] = 1
# $fp: None -> a
	# now $fp is a
	lw $fp -0 ($sp)
# $t0: None -> #4
	# now $t0 is #4
	add $t0 $fp 1
	sw $t0 -96 ($sp)
# push param: #4
	# save start
	sw $ra -188 ($sp)
	addi $sp $sp -96
	jal func_permutations
	# recover start
	addi $sp $sp 96
	lw $ra -188 ($sp)
	# recover end
	li $t9 0
# $t1: None -> i
	# now $t1 is i
	lw $t1 -20 ($sp)
	sll $t8 $t1 2
	sw $t9 _used ($t8)
# save array: used[i] = 0
label6:
# $t2: None -> i
	# now $t2 is i
	lw $t2 -20 ($sp)
	add $t2 $t2 1
	sw $t2 -20 ($sp)
# $t3: None -> i
	# now $t3 is i
	lw $t3 -20 ($sp)
# $t4: None -> n
	# now $t4 is n
	lw $t4 _n
	ble $t3 $t4 label4
	jr $ra
func_get_max_num_1:
	li $v0 10
	jr $ra
	jr $ra
func_get_max_num_2:
# $t0: None -> max_num
	# now $t0 is max_num
	li $t0 10
	sw $t0 -0 ($sp)
# $t1: None -> max_num
	# now $t1 is max_num
	lw $t1 -0 ($sp)
	move $v0 $t1
	jr $ra
	jr $ra
func_get_2:
	li $v0 2
	jr $ra
	jr $ra
func_compute:
# $t0: None -> op
	# now $t0 is op
	lbu $t0 -8 ($sp)
	bne $t0 43 label7
# $t1: None -> b
	# now $t1 is b
	lw $t1 -4 ($sp)
# $t2: None -> #5
	# now $t2 is #5
	mul $t2 $t1 2
# $t3: None -> a
	# now $t3 is a
	lw $t3 -0 ($sp)
# $t4: None -> #6
	# now $t4 is #6
	add $t4 $t3 $t2
# $t5: None -> b
	# now $t5 is b
	lw $t5 -4 ($sp)
# $t6: None -> #7
	# now $t6 is #7
	sub $t6 $t4 $t5
	move $v0 $t6
	jr $ra
	j label8
label7:
# $t7: None -> op
	# now $t7 is op
	lbu $t7 -8 ($sp)
	bne $t7 45 label9
# $s0: None -> b
	# now $s0 is b
	lw $s0 -4 ($sp)
# $s1: None -> #8
	# now $s1 is #8
	add $s1 $s0 $s0
# $s2: None -> #9
	# now $s2 is #9
	div $s2 $s1 2
# $s3: None -> a
	# now $s3 is a
	lw $s3 -0 ($sp)
# $s4: None -> #10
	# now $s4 is #10
	sub $s4 $s3 $s2
	move $v0 $s4
	jr $ra
	j label10
label9:
# $s5: None -> op
	# now $s5 is op
	lbu $s5 -8 ($sp)
	bne $s5 42 label11
# $s6: None -> a
	# now $s6 is a
	lw $s6 -0 ($sp)
# $s7: None -> b
	# now $s7 is b
	lw $s7 -4 ($sp)
# $fp: None -> #11
	# now $fp is #11
	mul $fp $s6 $s7
	move $v0 $fp
	jr $ra
	j label12
label11:
# $t0: None -> b
	# now $t0 is b
	lw $t0 -4 ($sp)
	beq $t0 0 label13
# $t1: None -> a
	# now $t1 is a
	lw $t1 -0 ($sp)
# $t2: None -> b
	# now $t2 is b
	lw $t2 -4 ($sp)
# $t3: None -> #12
	# now $t3 is #12
	div $t3 $t1 $t2
	move $v0 $t3
	jr $ra
	j label14
label13:
# $t4: None -> #13
	# now $t4 is #13
	li $t4 3
# $t5: None -> #14
	# now $t5 is #14
	mul $t5 $t4 3
# $t6: None -> #15
	# now $t6 is #15
	sub $t6 $t5 4
# $t7: None -> #16
	# now $t7 is #16
	div $t7 $t6 5
# $s0: None -> #17
	# now $s0 is #17
	mul $s0 $t7 6
# $s1: None -> #18
	# now $s1 is #18
	add $s1 $s0 -7
# $s2: None -> #19
	# now $s2 is #19
	add $s2 $s1 1
	move $v0 $s2
	jr $ra
label14:
label12:
label10:
label8:
	jr $ra
func_get_permutations_sy:
	li $v0 0
	jr $ra
	jr $ra
func_judge:
	li $v0 11
	li $a0 0
	syscall
	# print char 0
	# save start
	sw $ra -156 ($sp)
	addi $sp $sp -88
	jal func_get_max_num_1
	# recover start
	addi $sp $sp 88
	lw $ra -156 ($sp)
	# recover end
# $t0: None -> #20
	# now $t0 is #20
	move $t0 $v0
# $t1: None -> #21
	# now $t1 is #21
	add $t1 $t0 1
# $t2: None -> n
	# now $t2 is n
	lw $t2 -0 ($sp)
	blt $t2 $t1 label15
	li $v0 70
	jr $ra
label15:
# $t3: None -> m
	# now $t3 is m
	lw $t3 -4 ($sp)
# $t4: None -> n
	# now $t4 is n
	lw $t4 -0 ($sp)
	ble $t3 $t4 label16
	li $v0 70
	jr $ra
label16:
# $t5: None -> m
	# now $t5 is m
	lw $t5 -4 ($sp)
	bgtz $t5 label17
	li $v0 70
	jr $ra
label17:
	li $v0 84
	jr $ra
	jr $ra
func_preparation:
	# save start
	sw $ra -264 ($sp)
	addi $sp $sp -196
	jal func_get_max_num_1
	# recover start
	addi $sp $sp 196
	lw $ra -264 ($sp)
	# recover end
# $t0: None -> #22
	# now $t0 is #22
	move $t0 $v0
	sw $t0 -196 ($sp)
# push param: #22
	li $t9 1
	sw $t9 -200 ($sp)
# push param: 1
	li $t9 43
	sw $t9 -204 ($sp)
# push param: '+'
	# save start
	sw $ra -336 ($sp)
	addi $sp $sp -196
	jal func_compute
	# recover start
	addi $sp $sp 196
	lw $ra -336 ($sp)
	# recover end
# $t1: None -> #23
	# now $t1 is #23
	move $t1 $v0
# $t2: None -> n
	# now $t2 is n
	move $t2 $t1
	sw $t2 -120 ($sp)
label18:
# $t3: None -> n
	# now $t3 is n
	lw $t3 -120 ($sp)
	beq $t3 0 label19
# $t4: None -> #24
	# now $t4 is #24
	li $t4 -1
# $t5: None -> n
	# now $t5 is n
	lw $t5 -120 ($sp)
# $t6: None -> #25
	# now $t6 is #25
	add $t6 $t4 $t5
# $t7: None -> n
	# now $t7 is n
	move $t7 $t6
	sw $t7 -120 ($sp)
	li $t9 0
# $s0: None -> n
	# now $s0 is n
	lw $s0 -120 ($sp)
	sll $t8 $s0 2
	sw $t9 _used ($t8)
# save array: used[n] = 0
	li $t9 10086
# $s1: None -> n
	# now $s1 is n
	lw $s1 -120 ($sp)
	sll $t8 $s1 2
	addi $t8 $t8 68
	
	sub $t8 $sp $t8
	sw $t9 ($t8)
# save array: array[n] = 10086
	j label18
label19:
	li $t9 10
	sw $t9 -196 ($sp)
# push param: 10
	# save start
	sw $ra -272 ($sp)
	addi $sp $sp -196
	jal func_get_2
	# recover start
	addi $sp $sp 196
	lw $ra -272 ($sp)
	# recover end
# $s2: None -> #26
	# now $s2 is #26
	move $s2 $v0
	sw $s2 -200 ($sp)
# push param: #26
	li $t9 43
	sw $t9 -204 ($sp)
# push param: '+'
	# save start
	sw $ra -336 ($sp)
	addi $sp $sp -196
	jal func_compute
	# recover start
	addi $sp $sp 196
	lw $ra -336 ($sp)
	# recover end
# $s3: None -> #27
	# now $s3 is #27
	move $s3 $v0
# $s4: None -> #28
	# now $s4 is #28
	sub $s4 $s3 1
# $s5: None -> n
	# now $s5 is n
	move $s5 $s4
	sw $s5 -120 ($sp)
label20:
# $s6: None -> n
	# now $s6 is n
	lw $s6 -120 ($sp)
# $s7: None -> #29
	# now $s7 is #29
	sub $s7 $s6 1
# $fp: None -> #30
	# now $fp is #30
	li $fp 1
# $t0: None -> #31
	# now $t0 is #31
	sub $t0 $0 $fp
# $t1: None -> #32
	# now $t1 is #32
	li $t1 6
# $t2: None -> #33
	# now $t2 is #33
	add $t2 $t0 $t1
# $t3: None -> #34
	# now $t3 is #34
	mul $t3 $t2 4
# $t4: None -> n
	# now $t4 is n
	lw $t4 -120 ($sp)
# $t5: None -> #35
	# now $t5 is #35
	add $t5 $t4 $t3
# $t6: None -> #36
	# now $t6 is #36
	sub $t6 $t5 21
# $t7: None -> #37
	# now $t7 is #37
	sll $t9 $t6 2
	addi $t9 $t9 68
	sub $t9 $sp $t9
	lw $t7 ($t9)
# read array: #37 = array[#36]
# $s0: None -> #38
	# now $s0 is #38
	sub $s0 $t7 10086
	sll $t8 $s7 2
	sw $s0 _stack ($t8)
# save array: stack[#29] = #38
# $s1: None -> n
	# now $s1 is n
	lw $s1 -120 ($sp)
	sub $s1 $s1 1
	sw $s1 -120 ($sp)
# $s2: None -> n
	# now $s2 is n
	lw $s2 -120 ($sp)
	bne $s2 0 label20
	jr $ra
	jr $ra
func_test_for:
# $t0: None -> i
	# now $t0 is i
	li $t0 1
	sw $t0 -0 ($sp)
label21:
	li $v0 4
	la $a0 string_3
	syscall
	# print str 3
# $t1: None -> i
	# now $t1 is i
	lw $t1 -0 ($sp)
	add $t1 $t1 1
	sw $t1 -0 ($sp)
	
	jr $ra
func_test_6_para:
# $t0: None -> a1
	# now $t0 is a1
	lw $t0 -0 ($sp)
# $t1: None -> a2
	# now $t1 is a2
	lw $t1 -4 ($sp)
# $t2: None -> #39
	# now $t2 is #39
	add $t2 $t0 $t1
# $t3: None -> a3
	# now $t3 is a3
	lw $t3 -8 ($sp)
# $t4: None -> #40
	# now $t4 is #40
	add $t4 $t2 $t3
# $t5: None -> a4
	# now $t5 is a4
	lw $t5 -12 ($sp)
# $t6: None -> #41
	# now $t6 is #41
	add $t6 $t4 $t5
# $t7: None -> a5
	# now $t7 is a5
	lw $t7 -16 ($sp)
# $s0: None -> #42
	# now $s0 is #42
	add $s0 $t6 $t7
# $s1: None -> a6
	# now $s1 is a6
	lw $s1 -20 ($sp)
# $s2: None -> #43
	# now $s2 is #43
	add $s2 $s0 $s1
	move $v0 $s2
	jr $ra
	jr $ra
main:
	# save start
	sw $ra -100 ($sp)
	addi $sp $sp -28
	jal func_test_for
	# recover start
	addi $sp $sp 28
	lw $ra -100 ($sp)
	# recover end
	li $v0 5
	syscall
# $t0: None -> a
	# now $t0 is a
	move $t0 $v0
	sw $t0 -20 ($sp)
	# read int a
	li $v0 5
	syscall
# $t1: None -> b
	# now $t1 is b
	move $t1 $v0
	sw $t1 -24 ($sp)
	# read int b
	li $v0 12
	syscall
# $t2: None -> op
	# now $t2 is op
	move $t2 $v0
	sb $t2 -1 ($sp)
	# read char op
# $t3: None -> a
	# now $t3 is a
	lw $t3 -20 ($sp)
	sw $t3 -28 ($sp)
# push param: a
# $t4: None -> b
	# now $t4 is b
	lw $t4 -24 ($sp)
	sw $t4 -32 ($sp)
# push param: b
# $t5: None -> op
	# now $t5 is op
	lbu $t5 -1 ($sp)
	sw $t5 -36 ($sp)
# push param: op
	# save start
	sw $ra -168 ($sp)
	addi $sp $sp -28
	jal func_compute
	# recover start
	addi $sp $sp 28
	lw $ra -168 ($sp)
	# recover end
# $t6: None -> #44
	# now $t6 is #44
	move $t6 $v0
# $t7: None -> n
	# now $t7 is n
	move $t7 $t6
	sw $t7 _n
	li $v0 11
	li $a0 0
	syscall
	# print char 0
	li $v0 1
# $s0: None -> n
	# now $s0 is n
	lw $s0 _n
	move $a0 $s0
	syscall
	# print int n
	li $v0 5
	syscall
# $s1: None -> m
	# now $s1 is m
	move $s1 $v0
	sw $s1 _m
	# read int m
# $s2: None -> n
	# now $s2 is n
	lw $s2 _n
	sw $s2 -28 ($sp)
# push param: n
# $s3: None -> m
	# now $s3 is m
	lw $s3 _m
	sw $s3 -32 ($sp)
# push param: m
	# save start
	sw $ra -112 ($sp)
	addi $sp $sp -28
	jal func_judge
	# recover start
	addi $sp $sp 28
	lw $ra -112 ($sp)
	# recover end
# $s4: None -> #45
	# now $s4 is #45
	move $s4 $v0
# $s5: None -> sy
	# now $s5 is sy
	move $s5 $s4
	sb $s5 -2 ($sp)
# $s6: None -> a
	# now $s6 is a
	lw $s6 -20 ($sp)
	sw $s6 -28 ($sp)
# push param: a
# $s7: None -> b
	# now $s7 is b
	lw $s7 -24 ($sp)
	sw $s7 -32 ($sp)
# push param: b
# $fp: None -> n
	# now $fp is n
	lw $fp _n
	sw $fp -36 ($sp)
# push param: n
# $t0: None -> m
	# now $t0 is m
	lw $t0 _m
	sw $t0 -40 ($sp)
# push param: m
	li $t9 1
	sw $t9 -44 ($sp)
# push param: 1
	li $t9 2
	sw $t9 -48 ($sp)
# push param: 2
	# save start
	sw $ra -140 ($sp)
	addi $sp $sp -28
	jal func_test_6_para
	# recover start
	addi $sp $sp 28
	lw $ra -140 ($sp)
	# recover end
# $t1: None -> #46
	# now $t1 is #46
	move $t1 $v0
# $t2: None -> sum
	# now $t2 is sum
	move $t2 $t1
	sw $t2 _sum
	li $v0 1
# $t3: None -> sum
	# now $t3 is sum
	lw $t3 _sum
	move $a0 $t3
	syscall
	# print int sum
	li $v0 4
	la $a0 string_4
	syscall
	# print str 4
	li $v0 11
# $t4: None -> sy
	# now $t4 is sy
	lbu $t4 -2 ($sp)
	move $a0 $t4
	syscall
	# print char sy
	li $v0 4
	la $a0 string_2
	syscall
	# print str 2
	# save start
	sw $ra -96 ($sp)
	addi $sp $sp -28
	jal func_get_permutations_sy
	# recover start
	addi $sp $sp 28
	lw $ra -96 ($sp)
	# recover end
# $t5: None -> #47
	# now $t5 is #47
	move $t5 $v0
# $t7: None -> nor_sy
	# now $t7 is nor_sy
	move $t7 $t5
	sb $t7 -0 ($sp)
# $s0: None -> sy
	# now $s0 is sy
	lbu $s0 -2 ($sp)
# $s1: None -> nor_sy
	# now $s1 is nor_sy
	lbu $s1 -0 ($sp)
	beq $s0 $s1 label22
	li $v0 4
	la $a0 string_5
	syscall
	# print str 5
	j label23
label22:
	# save start
	sw $ra -220 ($sp)
	addi $sp $sp -28
	jal func_preparation
	# recover start
	addi $sp $sp 28
	lw $ra -220 ($sp)
	# recover end
	li $t9 0
	sw $t9 -28 ($sp)
# push param: 0
	# save start
	sw $ra -120 ($sp)
	addi $sp $sp -28
	jal func_permutations
	# recover start
	addi $sp $sp 28
	lw $ra -120 ($sp)
	# recover end
label23:
exit:
