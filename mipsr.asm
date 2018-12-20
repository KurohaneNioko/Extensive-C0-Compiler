.data
_c1 : .byte 0
_c2 : .byte 0
.align 2
__abc : .word 0
_data : .space 40
_i : .word 0
_m : .word 0
_n : .word 0
_t : .word 0
_x : .word 0
_y : .word 0
_z : .word 0
string_3 : .asciiz "...abs is: \n"
string_2 : .asciiz "...fibo result is :\n"
string_5 : .asciiz "...for error\n"
string_4 : .asciiz "...for loop work well\n"
string_1 : .asciiz "\\n! ~}|{abcABC<=+-$%&*()/\n"
.text
.globl main
func_add:
# $t0: None -> a
	# now $t0 is a
	lw $t0 -0 ($sp)
# $t1: None -> b
	# now $t1 is b
	lw $t1 -4 ($sp)
# $t2: None -> #1
	# now $t2 is #1
	add $t2 $t0 $t1
# $t3: None -> c
	# now $t3 is c
	lw $t3 -8 ($sp)
# $t4: None -> #2
	# now $t4 is #2
	add $t4 $t2 $t3
# $t5: None -> d
	# now $t5 is d
	lw $t5 -12 ($sp)
# $t6: None -> #3
	# now $t6 is #3
	add $t6 $t4 $t5
# $t7: None -> e
	# now $t7 is e
	lw $t7 -16 ($sp)
# $s0: None -> #4
	# now $s0 is #4
	add $s0 $t6 $t7
# $s1: None -> f
	# now $s1 is f
	lw $s1 -20 ($sp)
# $s2: None -> #5
	# now $s2 is #5
	add $s2 $s0 $s1
	move $v0 $s2
	jr $ra
	jr $ra
func_fool:
	li $v0 84
	jr $ra
	jr $ra
func_getabs:
# $t0: None -> x
	# now $t0 is x
	lw $t0 -0 ($sp)
	blez $t0 label1
# $t1: None -> x
	# now $t1 is x
	lw $t1 -0 ($sp)
	move $v0 $t1
	jr $ra
label1:
# $t2: None -> x
	# now $t2 is x
	lw $t2 -0 ($sp)
	bne $t2 0 label2
	li $v0 0
	jr $ra
	j label3
label2:
# $t3: None -> x
	# now $t3 is x
	lw $t3 -0 ($sp)
	beq $t3 0 label4
# $t4: None -> x
	# now $t4 is x
	lw $t4 -0 ($sp)
# $t5: None -> #6
	# now $t5 is #6
	sub $t5 $0 $t4
	move $v0 $t5
	jr $ra
label4:
label3:
	jr $ra
func_fibo:
# $t0: None -> n
	# now $t0 is n
	lw $t0 -0 ($sp)
	bge $t0 3 label5
	li $v0 1
	jr $ra
	j label6
label5:
# $t1: None -> n
	# now $t1 is n
	lw $t1 -0 ($sp)
# $t2: None -> #7
	# now $t2 is #7
	sub $t2 $t1 1
	sw $t2 -100 ($sp)
# push param: #7
	# save start
	sw $ra -196 ($sp)
	addi $sp $sp -100
	jal func_fibo
	# recover start
	addi $sp $sp 100
	lw $ra -196 ($sp)
	# recover end
# $t3: None -> #8
	# now $t3 is #8
	move $t3 $v0
# $t4: None -> n
	# now $t4 is n
	lw $t4 -0 ($sp)
# $t5: None -> #9
	# now $t5 is #9
	sub $t5 $t4 2
	sw $t5 -100 ($sp)
# push param: #9
	# save start
	sw $t3 -128 ($sp)
	sw $ra -196 ($sp)
	addi $sp $sp -100
	jal func_fibo
	# recover start
	addi $sp $sp 100
	lw $ra -196 ($sp)
	lw $t3 -128 ($sp)
	# recover end
# $t6: None -> #10
	# now $t6 is #10
	move $t6 $v0
# $t7: None -> #11
	# now $t7 is #11
	add $t7 $t3 $t6
	move $v0 $t7
	jr $ra
label6:
	jr $ra
func_test_strelement:
	li $v0 4
	la $a0 string_1
	syscall
	# print str 1
	jr $ra
func_test_chartypetrans:
# $t0: None -> ch
	# now $t0 is ch
	lbu $t0 -0 ($sp)
# $t1: None -> #12
	# now $t1 is #12
	add $t1 $t0 1
	move $v0 $t1
	jr $ra
	jr $ra
func_test_condition:
# $t0: None -> #13
	# now $t0 is #13
	li $t0 12
# $t1: None -> x
	# now $t1 is x
	lw $t1 -0 ($sp)
# $t2: None -> #14
	# now $t2 is #14
	sub $t2 $t1 $t0
# $t3: None -> #15
	# now $t3 is #15
	li $t3 12
# $t4: None -> #16
	# now $t4 is #16
	add $t4 $t2 $t3
	beq $t4 0 label7
	li $v0 1
	jr $ra
	j label8
label7:
	li $v0 0
	jr $ra
label8:
	jr $ra
func_call_fibo:
	li $v0 5
	syscall
# $t0: None -> m
	# now $t0 is m
	move $t0 $v0
	sw $t0 _m
	# read int m
# $t1: None -> m
	# now $t1 is m
	lw $t1 _m
	sw $t1 -80 ($sp)
# push param: m
	# save start
	sw $ra -176 ($sp)
	addi $sp $sp -80
	jal func_fibo
	# recover start
	addi $sp $sp 80
	lw $ra -176 ($sp)
	# recover end
# $t2: None -> #17
	# now $t2 is #17
	move $t2 $v0
# $t3: None -> t
	# now $t3 is t
	move $t3 $t2
	sw $t3 _t
	li $v0 4
	la $a0 string_2
	syscall
	# print str 2
	li $v0 1
# $t4: None -> t
	# now $t4 is t
	lw $t4 _t
	move $a0 $t4
	syscall
	# print int t
	jr $ra
func_test_arrayindex:
	li $t9 100
	sw $t9 _data+4
# save array: data[1] = 100
# $t0: None -> #18
	# now $t0 is #18
	li $t0 5
	li $t9 200
	sll $t8 $t0 2
	sw $t9 _data ($t8)
# save array: data[#18] = 200
	li $t9 400
	sw $t9 _data+32
# save array: data[8] = 400
	jr $ra
func_test_arrayassign:
# $t0: None -> i
	# now $t0 is i
	add $t0 $0 $0
	sw $t0 _i
label9:
# $t1: None -> i
	# now $t1 is i
	lw $t1 _i
	bge $t1 10 label10
	li $t9 0
	sw $t9 -92 ($sp)
# push param: 0
# $t2: None -> i
	# now $t2 is i
	lw $t2 _i
# $t3: None -> #19
	# now $t3 is #19
	sub $t3 $t2 2
	sw $t3 -96 ($sp)
# push param: #19
	li $t9 0
	sw $t9 -100 ($sp)
# push param: 0
	li $t9 1
	sw $t9 -104 ($sp)
# push param: 1
	li $t9 1
	sw $t9 -108 ($sp)
# push param: 1
	li $t9 0
	sw $t9 -112 ($sp)
# push param: 0
	# save start
	sw $ra -208 ($sp)
	addi $sp $sp -92
	jal func_add
	# recover start
	addi $sp $sp 92
	lw $ra -208 ($sp)
	# recover end
# $t4: None -> #20
	# now $t4 is #20
	move $t4 $v0
# $t5: None -> i
	# now $t5 is i
	lw $t5 _i
# $t6: None -> #21
	# now $t6 is #21
	add $t6 $t5 1
	sll $t8 $t4 2
	sw $t6 _data ($t8)
# save array: data[#20] = #21
# $t7: None -> i
	# now $t7 is i
	lw $t7 _i
# $s0: None -> #22
	# now $s0 is #22
	add $s0 $t7 1
# $s1: None -> i
	# now $s1 is i
	move $s1 $s0
	sw $s1 _i
	j label9
label10:
	jr $ra
func_test_for:
# $t0: None -> #23
	# now $t0 is #23
	add $t0 $0 $0
# $t1: None -> _abc
	# now $t1 is _abc
	move $t1 $t0
	sw $t1 __abc
# $t2: None -> i
	# now $t2 is i
	add $t2 $0 $0
	sw $t2 _i
label11:
# $t3: None -> i
	# now $t3 is i
	lw $t3 _i
# $t4: None -> #24
	# now $t4 is #24
	sll $t9 $t3 2
	lw $t4 _data($t9)
	
# read array: #24 = data[i]
# $t5: None -> _abc
	# now $t5 is _abc
	lw $t5 __abc
# $t6: None -> #25
	# now $t6 is #25
	add $t6 $t5 $t4
# $t7: None -> _abc
	# now $t7 is _abc
	move $t7 $t6
	sw $t7 __abc
# $s0: None -> i
	# now $s0 is i
	lw $s0 _i
	add $s0 $s0 1
	sw $s0 _i
# $s1: None -> i
	# now $s1 is i
	lw $s1 _i
# $s2: None -> n
	# now $s2 is n
	lw $s2 _n
	blt $s1 $s2 label11
# $s3: None -> _abc
	# now $s3 is _abc
	lw $s3 __abc
	move $v0 $s3
	jr $ra
	jr $ra
func_test_bra_statement:
	jr $ra
func_call_abs:
	li $v0 5
	syscall
# $t0: None -> m
	# now $t0 is m
	move $t0 $v0
	sw $t0 _m
	# read int m
# $t1: None -> m
	# now $t1 is m
	lw $t1 _m
	sw $t1 -80 ($sp)
# push param: m
	# save start
	sw $ra -160 ($sp)
	addi $sp $sp -80
	jal func_getabs
	# recover start
	addi $sp $sp 80
	lw $ra -160 ($sp)
	# recover end
# $t2: None -> #26
	# now $t2 is #26
	move $t2 $v0
# $t3: None -> t
	# now $t3 is t
	move $t3 $t2
	sw $t3 _t
	li $v0 4
	la $a0 string_3
	syscall
	# print str 3
	li $v0 1
# $t4: None -> t
	# now $t4 is t
	lw $t4 _t
	move $a0 $t4
	syscall
	# print int t
	jr $ra
main:
# $t0: None -> #27
	# now $t0 is #27
	li $t0 -99
# $t1: None -> a
	# now $t1 is a
	move $t1 $t0
	sw $t1 -76 ($sp)
# $t2: None -> x
	# now $t2 is x
	li $t2 3
	sw $t2 _x
# $t3: None -> #28
	# now $t3 is #28
	li $t3 -4
# $t4: None -> y
	# now $t4 is y
	move $t4 $t3
	sw $t4 _y
# $t5: None -> c1
	# now $t5 is c1
	li $t5 84
	sb $t5 _c1
# $t6: None -> x
	# now $t6 is x
	lw $t6 _x
# $t7: None -> y
	# now $t7 is y
	lw $t7 _y
# $s0: None -> #29
	# now $s0 is #29
	mul $s0 $t6 $t7
# $s1: None -> a
	# now $s1 is a
	lw $s1 -76 ($sp)
# $s2: None -> x
	# now $s2 is x
	lw $s2 _x
# $s3: None -> #30
	# now $s3 is #30
	div $s3 $s1 $s2
# $s4: None -> #31
	# now $s4 is #31
	add $s4 $s0 $s3
# $s5: None -> x
	# now $s5 is x
	lw $s5 _x
# $s6: None -> y
	# now $s6 is y
	lw $s6 _y
# $s7: None -> #32
	# now $s7 is #32
	add $s7 $s5 $s6
# $fp: None -> a
	# now $fp is a
	lw $fp -76 ($sp)
# $t0: None -> #33
	# now $t0 is #33
	mul $t0 $s7 $fp
# $t1: None -> #34
	# now $t1 is #34
	sub $t1 $s4 $t0
# $t2: None -> z
	# now $t2 is z
	move $t2 $t1
	sw $t2 _z
	li $t9 114
	sw $t9 -80 ($sp)
# push param: 'r'
	# save start
	sw $ra -160 ($sp)
	addi $sp $sp -80
	jal func_test_chartypetrans
	# recover start
	addi $sp $sp 80
	lw $ra -160 ($sp)
	# recover end
# $t3: None -> #35
	# now $t3 is #35
	move $t3 $v0
# $t4: None -> i
	# now $t4 is i
	move $t4 $t3
	sw $t4 _i
# $t5: None -> x
	# now $t5 is x
	lw $t5 _x
	sw $t5 -80 ($sp)
# push param: x
# $t6: None -> y
	# now $t6 is y
	lw $t6 _y
	sw $t6 -84 ($sp)
# push param: y
# $t7: None -> z
	# now $t7 is z
	lw $t7 _z
	sw $t7 -88 ($sp)
# push param: z
# $s0: None -> i
	# now $s0 is i
	lw $s0 _i
	sw $s0 -92 ($sp)
# push param: i
# $s1: None -> x
	# now $s1 is x
	lw $s1 _x
	sw $s1 -96 ($sp)
# push param: x
	li $t9 0
	sw $t9 -100 ($sp)
# push param: 0
	li $t9 0
	sw $t9 -104 ($sp)
# push param: 0
# $s2: None -> y
	# now $s2 is y
	lw $s2 _y
	sw $s2 -108 ($sp)
# push param: y
	li $t9 0
	sw $t9 -112 ($sp)
# push param: 0
	li $t9 0
	sw $t9 -116 ($sp)
# push param: 0
	# save start
	sw $ra -212 ($sp)
	addi $sp $sp -96
	jal func_add
	# recover start
	addi $sp $sp 96
	lw $ra -212 ($sp)
	# recover end
# $s3: None -> #36
	# now $s3 is #36
	move $s3 $v0
	sw $s3 -96 ($sp)
# push param: #36
	li $t9 0
	sw $t9 -100 ($sp)
# push param: 0
	# save start
	sw $ra -196 ($sp)
	addi $sp $sp -80
	jal func_add
	# recover start
	addi $sp $sp 80
	lw $ra -196 ($sp)
	# recover end
# $s4: None -> #37
	# now $s4 is #37
	move $s4 $v0
# $s5: None -> t
	# now $s5 is t
	move $s5 $s4
	sw $s5 _t
	li $v0 1
# $s6: None -> t
	# now $s6 is t
	lw $s6 _t
	move $a0 $s6
	syscall
	# print int t
	# save start
	sw $ra -152 ($sp)
	addi $sp $sp -80
	jal func_test_bra_statement
	# recover start
	addi $sp $sp 80
	lw $ra -152 ($sp)
	# recover end
	li $v0 5
	syscall
# $s7: None -> n
	# now $s7 is n
	move $s7 $v0
	sw $s7 _n
	# read int n
	# save start
	sw $ra -156 ($sp)
	addi $sp $sp -80
	jal func_test_arrayindex
	# recover start
	addi $sp $sp 80
	lw $ra -156 ($sp)
	# recover end
	# save start
	sw $ra -168 ($sp)
	addi $sp $sp -80
	jal func_test_arrayassign
	# recover start
	addi $sp $sp 80
	lw $ra -168 ($sp)
	# recover end
# $fp: None -> n
	# now $fp is n
	lw $fp _n
	blez $fp label12
	# save start
	sw $ra -164 ($sp)
	addi $sp $sp -80
	jal func_test_for
	# recover start
	addi $sp $sp 80
	lw $ra -164 ($sp)
	# recover end
# $t0: None -> #38
	# now $t0 is #38
	move $t0 $v0
# $t1: None -> n
	# now $t1 is n
	lw $t1 _n
# $t2: None -> #39
	# now $t2 is #39
	add $t2 $t1 1
# $t3: None -> n
	# now $t3 is n
	lw $t3 _n
# $t4: None -> #40
	# now $t4 is #40
	mul $t4 $t3 $t2
# $t5: None -> #41
	# now $t5 is #41
	div $t5 $t4 2
	bne $t0 $t5 label13
	li $v0 4
	la $a0 string_4
	syscall
	# print str 4
	j label14
label13:
	li $v0 4
	la $a0 string_5
	syscall
	# print str 5
label14:
	j label15
label12:
# $t6: None -> n
	# now $t6 is n
	lw $t6 _n
	bne $t6 0 label16
	# save start
	sw $ra -164 ($sp)
	addi $sp $sp -80
	jal func_test_for
	# recover start
	addi $sp $sp 80
	lw $ra -164 ($sp)
	# recover end
# $t7: None -> #42
	# now $t7 is #42
	move $t7 $v0
	bne $t7 1 label17
	li $v0 4
	la $a0 string_4
	syscall
	# print str 4
	j label18
label17:
	li $v0 4
	la $a0 string_5
	syscall
	# print str 5
label18:
label16:
label15:
	# save start
	sw $ra -156 ($sp)
	addi $sp $sp -80
	jal func_call_fibo
	# recover start
	addi $sp $sp 80
	lw $ra -156 ($sp)
	# recover end
	# save start
	sw $ra -156 ($sp)
	addi $sp $sp -80
	jal func_call_abs
	# recover start
	addi $sp $sp 80
	lw $ra -156 ($sp)
	# recover end
# $s0: None -> #43
	# now $s0 is #43
	li $s0 100
# $s1: None -> y
	# now $s1 is y
	move $s1 $s0
	sw $s1 _y
# $s2: None -> y
	# now $s2 is y
	lw $s2 _y
	bne $s2 100 label19
	# save start
	sw $ra -152 ($sp)
	addi $sp $sp -80
	jal func_fool
	# recover start
	addi $sp $sp 80
	lw $ra -152 ($sp)
	# recover end
# $s3: None -> #44
	# now $s3 is #44
	move $s3 $v0
	li $v0 11
	move $a0 $s3
	syscall
	# print char #44
label19:
	# save start
	sw $ra -152 ($sp)
	addi $sp $sp -80
	jal func_test_strelement
	# recover start
	addi $sp $sp 80
	lw $ra -152 ($sp)
	# recover end
# $s4: None -> n
	# now $s4 is n
	lw $s4 _n
	sw $s4 -80 ($sp)
# push param: n
	# save start
	sw $ra -172 ($sp)
	addi $sp $sp -80
	jal func_test_condition
	# recover start
	addi $sp $sp 80
	lw $ra -172 ($sp)
	# recover end
# $s5: None -> #45
	# now $s5 is #45
	move $s5 $v0
	li $v0 1
	move $a0 $s5
	syscall
	# print int #45
	j exit
exit:
