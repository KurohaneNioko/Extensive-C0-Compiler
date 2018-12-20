.data
.align 2
string_4 : .asciiz " !#$%&'()*+,-./\n"
string_5 : .asciiz "0123456789:;<=>?\n"
string_2 : .asciiz "1\n"
string_6 : .asciiz "@ABCDEFGHIJKLMNOPQRSTUVWXYZ\n"
string_33 : .asciiz "CompareEqual\n"
string_38 : .asciiz "CompareGreaterEqual\n"
string_37 : .asciiz "CompareGreater\n"
string_36 : .asciiz "CompareLessEqual\n"
string_35 : .asciiz "CompareLess\n"
string_34 : .asciiz "CompareNotEqual\n"
string_12 : .asciiz "Condition ::= Expr CompareOp Expr\n"
string_11 : .asciiz "Condition ::= Expr\n"
string_15 : .asciiz "Decremental for\n"
string_18 : .asciiz "Decremental while\n"
string_8 : .asciiz "Deeply Nested ParenExpr\n"
string_14 : .asciiz "I = \n"
string_13 : .asciiz "Incremental for\n"
string_17 : .asciiz "Incremental while\n"
string_19 : .asciiz "Never while\n"
string_43 : .asciiz "Please input an integer for CompareOp:\n"
string_42 : .asciiz "Please input two integers:\n"
string_41 : .asciiz "Result: false\n"
string_40 : .asciiz "Result: true\n"
string_9 : .asciiz "SingleString\n"
string_10 : .asciiz "StringAndExpression\n"
string_32 : .asciiz "Unknown CompareOp: \n"
string_39 : .asciiz "Unknown CompareOp\n"
string_7 : .asciiz "[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\n"
string_3 : .asciiz "\\n\\t\\f\\r\\\\\\'\\a\\b\n"
string_1 : .asciiz "\n"
string_23 : .asciiz "else\n"
string_16 : .asciiz "for: execute only once\n"
string_22 : .asciiz "if else\n"
string_21 : .asciiz "if if else\n"
string_20 : .asciiz "if if if\n"
string_28 : .asciiz "while for for for if\n"
string_27 : .asciiz "while for for for\n"
string_31 : .asciiz "while if while while for\n"
string_30 : .asciiz "while if\n"
string_26 : .asciiz "while while if for\n"
string_25 : .asciiz "while while if\n"
string_24 : .asciiz "while while while\n"
string_29 : .asciiz "while\n"
.text
.globl main
func_tokentest_string:
	li $v0 4
	la $a0 string_1
	syscall
	# print str 1
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
	li $v0 4
	la $a0 string_5
	syscall
	# print str 5
	li $v0 4
	la $a0 string_6
	syscall
	# print str 6
	li $v0 4
	la $a0 string_7
	syscall
	# print str 7
	jr $ra
func_tokentest_number:
	li $v0 1
	li $a0 0
	syscall
	# print int 000000
	li $v0 1
	li $a0 1
	syscall
	# print int 000001
	li $v0 1
	li $a0 123456
	syscall
	# print int 123456
# $t0: None -> #1
	# now $t0 is #1
	add $t0 $0 $0
	li $v0 1
	move $a0 $t0
	syscall
	# print int #1
	li $v0 1
	li $a0 0
	syscall
	# print int 00000
	li $v0 1
	li $a0 12345
	syscall
	# print int 12345
# $t1: None -> #2
	# now $t1 is #2
	li $t1 -12345
	li $v0 1
	move $a0 $t1
	syscall
	# print int #2
	jr $ra
func_tokentest_character:
	li $v0 11
	li $a0 43
	syscall
	# print char '+'
	li $v0 11
	li $a0 45
	syscall
	# print char '-'
	li $v0 11
	li $a0 42
	syscall
	# print char '*'
	li $v0 11
	li $a0 47
	syscall
	# print char '/'
	li $v0 11
	li $a0 97
	syscall
	# print char 'a'
	li $v0 11
	li $a0 98
	syscall
	# print char 'b'
	li $v0 11
	li $a0 99
	syscall
	# print char 'c'
	li $v0 11
	li $a0 100
	syscall
	# print char 'd'
	li $v0 11
	li $a0 48
	syscall
	# print char '0'
	li $v0 11
	li $a0 49
	syscall
	# print char '1'
	li $v0 11
	li $a0 50
	syscall
	# print char '2'
	li $v0 11
	li $a0 51
	syscall
	# print char '3'
	jr $ra
func_tokentest_identifier:
	li $v0 1
	li $a0 1
	syscall
	# print int 1
	li $v0 1
	li $a0 2
	syscall
	# print int 2
	li $v0 1
	li $a0 3
	syscall
	# print int 3
	jr $ra
func_tokentest_caseignored:
	li $v0 1
	li $a0 1
	syscall
	# print int 1
	jr $ra
func_test_binop:
# $t0: None -> #3
	# now $t0 is #3
	li $t0 98
	li $v0 1
	move $a0 $t0
	syscall
	# print int #3
# $t1: None -> #4
	# now $t1 is #4
	li $t1 -96
	li $v0 1
	move $a0 $t1
	syscall
	# print int #4
# $t2: None -> #5
	# now $t2 is #5
	li $t2 97
	li $v0 1
	move $a0 $t2
	syscall
	# print int #5
# $t3: None -> #6
	# now $t3 is #6
	add $t3 $0 $0
	li $v0 1
	move $a0 $t3
	syscall
	# print int #6
	jr $ra
func_test_parenexpr:
	li $v0 4
	la $a0 string_8
	syscall
	# print str 8
	li $v0 1
	li $a0 1
	syscall
	# print int 1
# $t0: None -> #7
	# now $t0 is #7
	li $t0 3
# $t1: None -> #8
	# now $t1 is #8
	li $t9 1
	div $t1 $t9 $t0
# $t2: None -> #9
	# now $t2 is #9
	sub $t9 $t1 3
	sub $t2 $0 $t9
# $t3: None -> #10
	# now $t3 is #10
	mul $t3 $t2 2
# $t4: None -> #11
	# now $t4 is #11
	add $t4 $t3 1
# $t5: None -> #12
	# now $t5 is #12
	li $t5 12
# $t6: None -> #13
	# now $t6 is #13
	add $t6 $t5 1
# $t7: None -> #14
	# now $t7 is #14
	sub $t7 $t4 $t6
	li $v0 1
	move $a0 $t7
	syscall
	# print int #14
	jr $ra
func_test_unaryop:
# $t0: None -> #15
	# now $t0 is #15
	li $t0 -1
	li $v0 1
	move $a0 $t0
	syscall
	# print int #15
	li $v0 1
	li $a0 1
	syscall
	# print int 1
# $t1: None -> #16
	# now $t1 is #16
	li $t1 -97
	li $v0 1
	move $a0 $t1
	syscall
	# print int #16
	li $v0 1
	li $a0 97
	syscall
	# print int 97
# $t2: None -> #17
	# now $t2 is #17
	li $t2 -1
# $t3: None -> #18
	# now $t3 is #18
	sub $t3 $0 $t2
	li $v0 1
	move $a0 $t3
	syscall
	# print int #18
	li $v0 1
	li $a0 1
	syscall
	# print int 1
# $t4: None -> #19
	# now $t4 is #19
	li $t4 -1
# $t5: None -> #20
	# now $t5 is #20
	sub $t5 $0 $t4
# $t6: None -> #21
	# now $t6 is #21
	sub $t6 $0 $t5
	li $v0 1
	move $a0 $t6
	syscall
	# print int #21
	jr $ra
func_test_subscript:
# $t0: None -> #22
	# now $t0 is #22
	lw $t0 -16($sp)
# read array: #22 = intarray[1]
	li $v0 1
	move $a0 $t0
	syscall
	# print int #22
# $t1: None -> #23
	# now $t1 is #23
	lbu $t1 -1($sp)
# read array: #23 = chararray[1]
	li $v0 11
	move $a0 $t1
	syscall
	# print char #23
	jr $ra
func_test_functionvoid_void:
	jr $ra
func_test_functionint_int:
# $t0: None -> int1
	# now $t0 is int1
	lw $t0 -0 ($sp)
	move $v0 $t0
	jr $ra
	jr $ra
func_test_functionchar_intchar:
# $t0: None -> char2
	# now $t0 is char2
	lbu $t0 -4 ($sp)
	move $v0 $t0
	jr $ra
	jr $ra
func_test_functionint_charcharchar:
	li $v0 1
	jr $ra
	jr $ra
func_test_call:
	# save start
	sw $ra -148 ($sp)
	addi $sp $sp -76
	jal func_test_functionvoid_void
	# recover start
	addi $sp $sp 76
	lw $ra -148 ($sp)
	# recover end
	li $t9 1
	sw $t9 -76 ($sp)
# push param: 1
	# save start
	sw $ra -152 ($sp)
	addi $sp $sp -76
	jal func_test_functionint_int
	# recover start
	addi $sp $sp 76
	lw $ra -152 ($sp)
	# recover end
	li $t9 1
	sw $t9 -76 ($sp)
# push param: 1
	li $t9 97
	sw $t9 -80 ($sp)
# push param: 'a'
	# save start
	sw $ra -156 ($sp)
	addi $sp $sp -76
	jal func_test_functionchar_intchar
	# recover start
	addi $sp $sp 76
	lw $ra -156 ($sp)
	# recover end
	li $t9 97
	sw $t9 -76 ($sp)
# push param: 'a'
	li $t9 98
	sw $t9 -80 ($sp)
# push param: 'b'
	li $t9 99
	sw $t9 -84 ($sp)
# push param: 'c'
	# save start
	sw $ra -160 ($sp)
	addi $sp $sp -76
	jal func_test_functionint_charcharchar
	# recover start
	addi $sp $sp 76
	lw $ra -160 ($sp)
	# recover end
	jr $ra
func_test_expr:
# $t0: None -> singleintvariable
	# now $t0 is singleintvariable
	li $t0 1
	sw $t0 -104 ($sp)
	li $t9 1
	sw $t9 -96 ($sp)
# save array: intarray[0] = 1
	li $t9 2
	sw $t9 -100 ($sp)
# save array: intarray[1] = 2
# $t1: None -> singleintvariable
	# now $t1 is singleintvariable
	lw $t1 -104 ($sp)
# $t2: None -> #24
	# now $t2 is #24
	sub $t2 $t1 2
# $t3: None -> singleintvariable
	# now $t3 is singleintvariable
	lw $t3 -104 ($sp)
# $t4: None -> #25
	# now $t4 is #25
	sll $t9 $t3 2
	addi $t9 $t9 96
	sub $t9 $sp $t9
	lw $t4 ($t9)
# read array: #25 = intarray[singleintvariable]
# $t5: None -> #26
	# now $t5 is #26
	sll $t9 $t4 2
	addi $t9 $t9 96
	sub $t9 $sp $t9
	lw $t5 ($t9)
# read array: #26 = intarray[#25]
# $t6: None -> singleintvariable
	# now $t6 is singleintvariable
	lw $t6 -104 ($sp)
# $t7: None -> #27
	# now $t7 is #27
	add $t7 $t6 $t5
# $s0: None -> singleintvariable
	# now $s0 is singleintvariable
	lw $s0 -104 ($sp)
# $s1: None -> #28
	# now $s1 is #28
	sll $t9 $s0 2
	addi $t9 $t9 96
	sub $t9 $sp $t9
	lw $s1 ($t9)
# read array: #28 = intarray[singleintvariable]
# $s2: None -> #29
	# now $s2 is #29
	add $s2 $t7 $s1
# $s3: None -> #30
	# now $s3 is #30
	div $s3 $t2 $s2
# $s4: None -> singleintvariable
	# now $s4 is singleintvariable
	lw $s4 -104 ($sp)
# $s5: None -> #31
	# now $s5 is #31
	mul $s5 $s4 $s3
	li $v0 1
	move $a0 $s5
	syscall
	# print int #31
# $s6: None -> singleintvariable
	# now $s6 is singleintvariable
	lw $s6 -104 ($sp)
# $s7: None -> #32
	# now $s7 is #32
	add $s7 $s6 1
# $fp: None -> singleintvariable
	# now $fp is singleintvariable
	lw $fp -104 ($sp)
# $t0: None -> #33
	# now $t0 is #33
	mul $t0 $fp 2
# $t1: None -> #34
	# now $t1 is #34
	sll $t9 $t0 2
	addi $t9 $t9 96
	sub $t9 $sp $t9
	lw $t1 ($t9)
# read array: #34 = intarray[#33]
# $t2: None -> #35
	# now $t2 is #35
	mul $t2 $t1 2
# $t3: None -> #36
	# now $t3 is #36
	mul $t3 $s7 $t2
	li $v0 1
	move $a0 $t3
	syscall
	# print int #36
# $t4: None -> singleintvariable
	# now $t4 is singleintvariable
	lw $t4 -104 ($sp)
# $t5: None -> #37
	# now $t5 is #37
	mul $t5 $t4 $t4
# $t6: None -> singleintvariable
	# now $t6 is singleintvariable
	lw $t6 -104 ($sp)
# $t7: None -> #38
	# now $t7 is #38
	mul $t7 $t5 $t6
# $s0: None -> #39
	# now $s0 is #39
	move $s0 $0
# $s1: None -> #40
	# now $s1 is #40
	sll $t9 $s0 2
	addi $t9 $t9 96
	sub $t9 $sp $t9
	lw $s1 ($t9)
# read array: #40 = intarray[#39]
	li $v0 1
	move $a0 $s1
	syscall
	# print int #40
# $s2: None -> singleintvariable
	# now $s2 is singleintvariable
	lw $s2 -104 ($sp)
# $s3: None -> #41
	# now $s3 is #41
	sll $t9 $s2 2
	addi $t9 $t9 96
	sub $t9 $sp $t9
	lw $s3 ($t9)
# read array: #41 = intarray[singleintvariable]
# $s4: None -> #42
	# now $s4 is #42
	mul $s4 $s3 4
# $s5: None -> #43
	# now $s5 is #43
	move $s5 $0
# $s6: None -> singleintvariable
	# now $s6 is singleintvariable
	lw $s6 -104 ($sp)
# $s7: None -> #44
	# now $s7 is #44
	add $s7 $s5 $s6
# $fp: None -> singleintvariable
	# now $fp is singleintvariable
	lw $fp -104 ($sp)
# $t0: None -> #45
	# now $t0 is #45
	sub $t0 $s7 $fp
# $t1: None -> #46
	# now $t1 is #46
	sll $t9 $t0 2
	addi $t9 $t9 96
	sub $t9 $sp $t9
	lw $t1 ($t9)
# read array: #46 = intarray[#45]
	li $v0 1
	move $a0 $t1
	syscall
	# print int #46
	jr $ra
func_test_empty:
label1:
	
	j label1
label2:
label3:
	
	j label3
label4:
	
label5:
	
label6:
# $t0: None -> i
	# now $t0 is i
	li $t0 1
	sw $t0 -4 ($sp)
label7:
# $t1: None -> i
	# now $t1 is i
	lw $t1 -4 ($sp)
	add $t1 $t1 1
	sw $t1 -4 ($sp)
# $t2: None -> i
	# now $t2 is i
	lw $t2 -4 ($sp)
	bne $t2 0 label7
# $t3: None -> i
	# now $t3 is i
	li $t3 1
	sw $t3 -4 ($sp)
label8:
# $t4: None -> i
	# now $t4 is i
	lw $t4 -4 ($sp)
	add $t4 $t4 1
	sw $t4 -4 ($sp)
# $t5: None -> i
	# now $t5 is i
	lw $t5 -4 ($sp)
	bne $t5 0 label8
	jr $ra
func_test_read:
	li $v0 5
	syscall
# $t0: None -> singleintvariable
	# now $t0 is singleintvariable
	move $t0 $v0
	sw $t0 -20 ($sp)
	# read int singleintvariable
	li $v0 12
	syscall
# $t1: None -> singlecharvariable
	# now $t1 is singlecharvariable
	move $t1 $v0
	sb $t1 -3 ($sp)
	# read char singlecharvariable
	li $v0 5
	syscall
# $t2: None -> _1
	# now $t2 is _1
	move $t2 $v0
	sw $t2 -8 ($sp)
	# read int _1
	li $v0 5
	syscall
# $t3: None -> _2
	# now $t3 is _2
	move $t3 $v0
	sw $t3 -12 ($sp)
	# read int _2
	li $v0 5
	syscall
# $t4: None -> _3
	# now $t4 is _3
	move $t4 $v0
	sw $t4 -16 ($sp)
	# read int _3
	li $v0 12
	syscall
# $t5: None -> _4
	# now $t5 is _4
	move $t5 $v0
	sb $t5 -0 ($sp)
	# read char _4
	li $v0 12
	syscall
# $t6: None -> _5
	# now $t6 is _5
	move $t6 $v0
	sb $t6 -1 ($sp)
	# read char _5
	li $v0 12
	syscall
# $t7: None -> _6
	# now $t7 is _6
	move $t7 $v0
	sb $t7 -2 ($sp)
	# read char _6
	jr $ra
func_test_write:
	li $v0 4
	la $a0 string_9
	syscall
	# print str 9
# $t0: None -> #47
	# now $t0 is #47
	lw $t0 -32($sp)
# read array: #47 = intarray[1]
# $t1: None -> #48
	# now $t1 is #48
	lw $t1 -32($sp)
# read array: #48 = intarray[1]
# $t2: None -> #49
	# now $t2 is #49
	add $t2 $t0 $t1
	li $v0 1
	move $a0 $t2
	syscall
	# print int #49
	li $v0 4
	la $a0 string_10
	syscall
	# print str 10
# $t3: None -> #50
	# now $t3 is #50
	lw $t3 -32($sp)
# read array: #50 = intarray[1]
# $t4: None -> #51
	# now $t4 is #51
	sll $t9 $t3 2
	addi $t9 $t9 28
	sub $t9 $sp $t9
	lw $t4 ($t9)
# read array: #51 = intarray[#50]
# $t5: None -> #52
	# now $t5 is #52
	mul $t5 $t4 1
	li $v0 1
	move $a0 $t5
	syscall
	# print int #52
	jr $ra
func_test_return_void:
	jr $ra
	jr $ra
func_test_return_char:
# $t0: None -> charvariable
	# now $t0 is charvariable
	lbu $t0 -2 ($sp)
	move $v0 $t0
	jr $ra
# $t1: None -> #53
	# now $t1 is #53
	lbu $t1 -1($sp)
# read array: #53 = chararray[1]
	move $v0 $t1
	jr $ra
	li $v0 97
	jr $ra
	# save start
	sw $ra -164 ($sp)
	addi $sp $sp -84
	jal func_test_return_char
	# recover start
	addi $sp $sp 84
	lw $ra -164 ($sp)
	# recover end
# $t2: None -> #54
	# now $t2 is #54
	move $t2 $v0
	move $v0 $t2
	jr $ra
	li $v0 97
	jr $ra
	jr $ra
func_test_return_int:
	li $v0 1
	jr $ra
# $t0: None -> intvariable
	# now $t0 is intvariable
	lw $t0 -24 ($sp)
	move $v0 $t0
	jr $ra
	# save start
	sw $ra -196 ($sp)
	addi $sp $sp -100
	jal func_test_return_int
	# recover start
	addi $sp $sp 100
	lw $ra -196 ($sp)
	# recover end
# $t1: None -> #55
	# now $t1 is #55
	move $t1 $v0
	move $v0 $t1
	jr $ra
# $t2: None -> #56
	# now $t2 is #56
	lw $t2 -20($sp)
# read array: #56 = intarray[1]
	move $v0 $t2
	jr $ra
# $t3: None -> intvariable
	# now $t3 is intvariable
	lw $t3 -24 ($sp)
# $t4: None -> #57
	# now $t4 is #57
	sll $t9 $t3 2
	addi $t9 $t9 16
	sub $t9 $sp $t9
	lw $t4 ($t9)
# read array: #57 = intarray[intvariable]
	move $v0 $t4
	jr $ra
	li $v0 1
	jr $ra
	jr $ra
func_test_compound_empty:
	jr $ra
func_test_compound_noconstdecl:
	li $v0 1
# $t0: None -> intvariable
	# now $t0 is intvariable
	lw $t0 -4 ($sp)
	move $a0 $t0
	syscall
	# print int intvariable
	jr $ra
func_test_compound_novardecl:
	li $v0 1
	li $a0 1
	syscall
	# print int 1
	jr $ra
func_test_compound_nostmts:
	jr $ra
func_test_if:
# $t0: None -> number
	# now $t0 is number
	lw $t0 -0 ($sp)
# $t1: None -> #58
	# now $t1 is #58
	mul $t1 $t0 $t0
# $t2: None -> #59
	# now $t2 is #59
	div $t2 $t1 2
# $t3: None -> number
	# now $t3 is number
	lw $t3 -0 ($sp)
# $t4: None -> #60
	# now $t4 is #60
	add $t4 $t3 $t2
	beq $t4 0 label9
	li $v0 4
	la $a0 string_11
	syscall
	# print str 11
label9:
# $t5: None -> number
	# now $t5 is number
	lw $t5 -0 ($sp)
# $t6: None -> #61
	# now $t6 is #61
	add $t6 $t5 1
# $t7: None -> number
	# now $t7 is number
	lw $t7 -0 ($sp)
# $s0: None -> #62
	# now $s0 is #62
	mul $s0 $t7 2
	bgt $t6 $s0 label10
	li $v0 4
	la $a0 string_12
	syscall
	# print str 12
label10:
	jr $ra
func_test_for:
	li $v0 4
	la $a0 string_13
	syscall
	# print str 13
# $t0: None -> i
	# now $t0 is i
	add $t0 $0 $0
	sw $t0 -4 ($sp)
label11:
	li $v0 4
	la $a0 string_14
	syscall
	# print str 14
	li $v0 1
# $t1: None -> i
	# now $t1 is i
	lw $t1 -4 ($sp)
	move $a0 $t1
	syscall
	# print int i
# $t2: None -> i
	# now $t2 is i
	lw $t2 -4 ($sp)
	add $t2 $t2 1
	sw $t2 -4 ($sp)
# $t3: None -> i
	# now $t3 is i
	lw $t3 -4 ($sp)
	blt $t3 10 label11
	li $v0 4
	la $a0 string_15
	syscall
	# print str 15
# $t4: None -> i
	# now $t4 is i
	li $t4 10
	sw $t4 -4 ($sp)
label12:
	li $v0 4
	la $a0 string_14
	syscall
	# print str 14
	li $v0 1
# $t5: None -> i
	# now $t5 is i
	lw $t5 -4 ($sp)
	move $a0 $t5
	syscall
	# print int i
# $t6: None -> i
	# now $t6 is i
	lw $t6 -4 ($sp)
	sub $t6 $t6 1
	sw $t6 -4 ($sp)
# $t7: None -> i
	# now $t7 is i
	lw $t7 -4 ($sp)
	bgez $t7 label12
	li $v0 4
	la $a0 string_16
	syscall
	# print str 16
# $s0: None -> i
	# now $s0 is i
	add $s0 $0 $0
	sw $s0 -4 ($sp)
label13:
	li $v0 4
	la $a0 string_14
	syscall
	# print str 14
	li $v0 1
# $s1: None -> i
	# now $s1 is i
	lw $s1 -4 ($sp)
	move $a0 $s1
	syscall
	# print int i
# $s2: None -> i
	# now $s2 is i
	lw $s2 -4 ($sp)
	sub $s2 $s2 1
	sw $s2 -4 ($sp)
# $s3: None -> i
	# now $s3 is i
	lw $s3 -4 ($sp)
	bgt $s3 10 label13
	jr $ra
func_test_while:
	li $v0 4
	la $a0 string_17
	syscall
	# print str 17
# $t0: None -> i
	# now $t0 is i
	add $t0 $0 $0
	sw $t0 -12 ($sp)
label14:
# $t1: None -> i
	# now $t1 is i
	lw $t1 -12 ($sp)
	bge $t1 10 label15
	li $v0 4
	la $a0 string_14
	syscall
	# print str 14
	li $v0 1
# $t2: None -> i
	# now $t2 is i
	lw $t2 -12 ($sp)
	move $a0 $t2
	syscall
	# print int i
# $t3: None -> i
	# now $t3 is i
	lw $t3 -12 ($sp)
# $t4: None -> #63
	# now $t4 is #63
	add $t4 $t3 1
# $t5: None -> i
	# now $t5 is i
	move $t5 $t4
	sw $t5 -12 ($sp)
	j label14
label15:
	li $v0 4
	la $a0 string_18
	syscall
	# print str 18
# $t6: None -> i
	# now $t6 is i
	li $t6 10
	sw $t6 -12 ($sp)
label16:
# $t7: None -> i
	# now $t7 is i
	lw $t7 -12 ($sp)
	bltz $t7 label17
	li $v0 4
	la $a0 string_14
	syscall
	# print str 14
	li $v0 1
# $s0: None -> i
	# now $s0 is i
	lw $s0 -12 ($sp)
	move $a0 $s0
	syscall
	# print int i
# $s1: None -> i
	# now $s1 is i
	lw $s1 -12 ($sp)
# $s2: None -> #64
	# now $s2 is #64
	sub $s2 $s1 1
# $s3: None -> i
	# now $s3 is i
	move $s3 $s2
	sw $s3 -12 ($sp)
	j label16
label17:
# $s4: None -> i
	# now $s4 is i
	add $s4 $0 $0
	sw $s4 -12 ($sp)
label18:
# $s5: None -> i
	# now $s5 is i
	lw $s5 -12 ($sp)
	ble $s5 10 label19
	li $v0 4
	la $a0 string_19
	syscall
	# print str 19
	j label18
label19:
	jr $ra
func_test_assign:
# $t0: None -> singleintvariable
	# now $t0 is singleintvariable
	li $t0 1
	sw $t0 -12 ($sp)
	li $t9 1
	sw $t9 -4 ($sp)
# save array: intarray[0] = 1
	li $t9 2
	sw $t9 -8 ($sp)
# save array: intarray[1] = 2
	jr $ra
func_test_stmt:
	
	
	
	li $v0 4
	la $a0 string_20
	syscall
	# print str 20
	j label23
label22:
	li $v0 4
	la $a0 string_21
	syscall
	# print str 21
label23:
	j label24
label21:
	li $v0 4
	la $a0 string_22
	syscall
	# print str 22
label24:
	j label25
label20:
	li $v0 4
	la $a0 string_23
	syscall
	# print str 23
label25:
label26:
	
label28:
	
label30:
	
	li $v0 4
	la $a0 string_24
	syscall
	# print str 24
	j label30
label31:
	
	li $v0 4
	la $a0 string_25
	syscall
	# print str 25
# $t0: None -> i
	# now $t0 is i
	add $t0 $0 $0
	sw $t0 -4 ($sp)
label33:
	li $v0 4
	la $a0 string_26
	syscall
	# print str 26
# $t1: None -> i
	# now $t1 is i
	lw $t1 -4 ($sp)
	add $t1 $t1 1
	sw $t1 -4 ($sp)
# $t2: None -> i
	# now $t2 is i
	lw $t2 -4 ($sp)
	blt $t2 4 label33
label32:
	j label28
label29:
# $t3: None -> i
	# now $t3 is i
	add $t3 $0 $0
	sw $t3 -4 ($sp)
label34:
# $t4: None -> i
	# now $t4 is i
	add $t4 $0 $0
	sw $t4 -4 ($sp)
label35:
# $t5: None -> i
	# now $t5 is i
	add $t5 $0 $0
	sw $t5 -4 ($sp)
label36:
	li $v0 4
	la $a0 string_27
	syscall
	# print str 27
	
	li $v0 4
	la $a0 string_28
	syscall
	# print str 28
label37:
# $t6: None -> i
	# now $t6 is i
	lw $t6 -4 ($sp)
	add $t6 $t6 1
	sw $t6 -4 ($sp)
# $t7: None -> i
	# now $t7 is i
	lw $t7 -4 ($sp)
	blt $t7 4 label36
# $s0: None -> i
	# now $s0 is i
	lw $s0 -4 ($sp)
	add $s0 $s0 1
	sw $s0 -4 ($sp)
# $s1: None -> i
	# now $s1 is i
	lw $s1 -4 ($sp)
	blt $s1 3 label35
# $s2: None -> i
	# now $s2 is i
	lw $s2 -4 ($sp)
	add $s2 $s2 1
	sw $s2 -4 ($sp)
# $s3: None -> i
	# now $s3 is i
	lw $s3 -4 ($sp)
	blt $s3 2 label34
	li $v0 4
	la $a0 string_29
	syscall
	# print str 29
	
	li $v0 4
	la $a0 string_30
	syscall
	# print str 30
label39:
	
label41:
	
# $s4: None -> i
	# now $s4 is i
	add $s4 $0 $0
	sw $s4 -4 ($sp)
label43:
	li $v0 4
	la $a0 string_31
	syscall
	# print str 31
# $s5: None -> i
	# now $s5 is i
	lw $s5 -4 ($sp)
	add $s5 $s5 1
	sw $s5 -4 ($sp)
# $s6: None -> i
	# now $s6 is i
	lw $s6 -4 ($sp)
	blt $s6 5 label43
	j label41
label42:
	j label39
label40:
label38:
	j label26
label27:
	jr $ra
func_threewayscompare:
# $t0: None -> a
	# now $t0 is a
	lw $t0 -0 ($sp)
# $t1: None -> b
	# now $t1 is b
	lw $t1 -4 ($sp)
	ble $t0 $t1 label44
	li $v0 1
	jr $ra
label44:
# $t2: None -> a
	# now $t2 is a
	lw $t2 -0 ($sp)
# $t3: None -> b
	# now $t3 is b
	lw $t3 -4 ($sp)
	bge $t2 $t3 label45
# $t4: None -> #65
	# now $t4 is #65
	li $t4 -1
	move $v0 $t4
	jr $ra
label45:
	li $v0 0
	jr $ra
	jr $ra
func_richcompare:
# $t0: None -> a
	# now $t0 is a
	lw $t0 -0 ($sp)
	sw $t0 -120 ($sp)
# push param: a
# $t1: None -> b
	# now $t1 is b
	lw $t1 -4 ($sp)
	sw $t1 -124 ($sp)
# push param: b
	# save start
	sw $ra -204 ($sp)
	addi $sp $sp -120
	jal func_threewayscompare
	# recover start
	addi $sp $sp 120
	lw $ra -204 ($sp)
	# recover end
# $t2: None -> #66
	# now $t2 is #66
	move $t2 $v0
# $t3: None -> order
	# now $t3 is order
	move $t3 $t2
	sw $t3 -44 ($sp)
# $t4: None -> compareop
	# now $t4 is compareop
	lw $t4 -8 ($sp)
	bne $t4 0 label46
# $t5: None -> order
	# now $t5 is order
	lw $t5 -44 ($sp)
	bne $t5 0 label47
	li $v0 1
	jr $ra
	j label48
label47:
	li $v0 0
	jr $ra
label48:
	j label49
label46:
# $t6: None -> compareop
	# now $t6 is compareop
	lw $t6 -8 ($sp)
	bne $t6 2 label50
# $t7: None -> #67
	# now $t7 is #67
	li $t7 -1
# $s0: None -> order
	# now $s0 is order
	lw $s0 -44 ($sp)
	bne $s0 $t7 label51
	li $v0 1
	jr $ra
	j label52
label51:
	li $v0 0
	jr $ra
label52:
	j label53
label50:
# $s1: None -> compareop
	# now $s1 is compareop
	lw $s1 -8 ($sp)
	bne $s1 4 label54
# $s2: None -> order
	# now $s2 is order
	lw $s2 -44 ($sp)
	bne $s2 1 label55
	li $v0 1
	jr $ra
	j label56
label55:
	li $v0 0
	jr $ra
label56:
	j label57
label54:
# $s3: None -> compareop
	# now $s3 is compareop
	lw $s3 -8 ($sp)
	bne $s3 1 label58
# $s4: None -> a
	# now $s4 is a
	lw $s4 -0 ($sp)
	sw $s4 -120 ($sp)
# push param: a
# $s5: None -> b
	# now $s5 is b
	lw $s5 -4 ($sp)
	sw $s5 -124 ($sp)
# push param: b
	li $t9 0
	sw $t9 -128 ($sp)
# push param: 0
	# save start
	sw $ra -236 ($sp)
	addi $sp $sp -120
	jal func_richcompare
	# recover start
	addi $sp $sp 120
	lw $ra -236 ($sp)
	# recover end
# $s6: None -> #68
	# now $s6 is #68
	move $s6 $v0
# $s7: None -> order
	# now $s7 is order
	move $s7 $s6
	sw $s7 -44 ($sp)
# $fp: None -> order
	# now $fp is order
	lw $fp -44 ($sp)
	beq $fp 0 label59
	li $v0 0
	jr $ra
	j label60
label59:
	li $v0 1
	jr $ra
label60:
	j label61
label58:
# $t0: None -> compareop
	# now $t0 is compareop
	lw $t0 -8 ($sp)
	bne $t0 3 label62
# $t1: None -> a
	# now $t1 is a
	lw $t1 -0 ($sp)
	sw $t1 -120 ($sp)
# push param: a
# $t2: None -> b
	# now $t2 is b
	lw $t2 -4 ($sp)
	sw $t2 -124 ($sp)
# push param: b
	li $t9 4
	sw $t9 -128 ($sp)
# push param: 4
	# save start
	sw $ra -236 ($sp)
	addi $sp $sp -120
	jal func_richcompare
	# recover start
	addi $sp $sp 120
	lw $ra -236 ($sp)
	# recover end
# $t3: None -> #69
	# now $t3 is #69
	move $t3 $v0
# $t4: None -> order
	# now $t4 is order
	move $t4 $t3
	sw $t4 -44 ($sp)
# $t5: None -> order
	# now $t5 is order
	lw $t5 -44 ($sp)
	beq $t5 0 label63
	li $v0 0
	jr $ra
	j label64
label63:
	li $v0 1
	jr $ra
label64:
	j label65
label62:
# $t6: None -> compareop
	# now $t6 is compareop
	lw $t6 -8 ($sp)
	bne $t6 5 label66
# $t7: None -> a
	# now $t7 is a
	lw $t7 -0 ($sp)
	sw $t7 -120 ($sp)
# push param: a
# $s0: None -> b
	# now $s0 is b
	lw $s0 -4 ($sp)
	sw $s0 -124 ($sp)
# push param: b
	li $t9 2
	sw $t9 -128 ($sp)
# push param: 2
	# save start
	sw $ra -236 ($sp)
	addi $sp $sp -120
	jal func_richcompare
	# recover start
	addi $sp $sp 120
	lw $ra -236 ($sp)
	# recover end
# $s1: None -> #70
	# now $s1 is #70
	move $s1 $v0
# $s2: None -> order
	# now $s2 is order
	move $s2 $s1
	sw $s2 -44 ($sp)
# $s3: None -> order
	# now $s3 is order
	lw $s3 -44 ($sp)
	beq $s3 0 label67
	li $v0 0
	jr $ra
	j label68
label67:
	li $v0 1
	jr $ra
label68:
	j label69
label66:
	li $v0 4
	la $a0 string_32
	syscall
	# print str 32
	li $v0 1
# $s4: None -> compareop
	# now $s4 is compareop
	lw $s4 -8 ($sp)
	move $a0 $s4
	syscall
	# print int compareop
# $s5: None -> #71
	# now $s5 is #71
	li $s5 -1
	move $v0 $s5
	jr $ra
label69:
label65:
label61:
label57:
label53:
label49:
# $s6: None -> #72
	# now $s6 is #72
	li $s6 -1
	move $v0 $s6
	jr $ra
	jr $ra
func_printcompareop:
# $t0: None -> op
	# now $t0 is op
	lw $t0 -0 ($sp)
	bne $t0 0 label70
	li $v0 4
	la $a0 string_33
	syscall
	# print str 33
	j label71
label70:
# $t1: None -> op
	# now $t1 is op
	lw $t1 -0 ($sp)
	bne $t1 1 label72
	li $v0 4
	la $a0 string_34
	syscall
	# print str 34
	j label73
label72:
# $t2: None -> op
	# now $t2 is op
	lw $t2 -0 ($sp)
	bne $t2 2 label74
	li $v0 4
	la $a0 string_35
	syscall
	# print str 35
	j label75
label74:
# $t3: None -> op
	# now $t3 is op
	lw $t3 -0 ($sp)
	bne $t3 3 label76
	li $v0 4
	la $a0 string_36
	syscall
	# print str 36
	j label77
label76:
# $t4: None -> op
	# now $t4 is op
	lw $t4 -0 ($sp)
	bne $t4 4 label78
	li $v0 4
	la $a0 string_37
	syscall
	# print str 37
	j label79
label78:
# $t5: None -> op
	# now $t5 is op
	lw $t5 -0 ($sp)
	bne $t5 5 label80
	li $v0 4
	la $a0 string_38
	syscall
	# print str 38
	j label81
label80:
	li $v0 4
	la $a0 string_39
	syscall
	# print str 39
label81:
label79:
label77:
label75:
label73:
label71:
	jr $ra
func_printallcompareop:
# $t0: None -> i
	# now $t0 is i
	add $t0 $0 $0
	sw $t0 -4 ($sp)
label82:
# $t1: None -> i
	# now $t1 is i
	lw $t1 -4 ($sp)
	sw $t1 -80 ($sp)
# push param: i
	# save start
	sw $ra -156 ($sp)
	addi $sp $sp -80
	jal func_printcompareop
	# recover start
	addi $sp $sp 80
	lw $ra -156 ($sp)
	# recover end
	li $v0 1
# $t2: None -> i
	# now $t2 is i
	lw $t2 -4 ($sp)
	move $a0 $t2
	syscall
	# print int i
# $t3: None -> i
	# now $t3 is i
	lw $t3 -4 ($sp)
	add $t3 $t3 1
	sw $t3 -4 ($sp)
# $t4: None -> i
	# now $t4 is i
	lw $t4 -4 ($sp)
	blt $t4 6 label82
	jr $ra
func_printresult:
# $t0: None -> bool
	# now $t0 is bool
	lw $t0 -0 ($sp)
	beq $t0 0 label83
	li $v0 4
	la $a0 string_40
	syscall
	# print str 40
	j label84
label83:
	li $v0 4
	la $a0 string_41
	syscall
	# print str 41
label84:
	jr $ra
main:
	# save start
	sw $ra -100 ($sp)
	addi $sp $sp -24
	jal func_printallcompareop
	# recover start
	addi $sp $sp 24
	lw $ra -100 ($sp)
	# recover end
	li $v0 4
	la $a0 string_42
	syscall
	# print str 42
	li $v0 5
	syscall
# $t0: None -> a
	# now $t0 is a
	move $t0 $v0
	sw $t0 -8 ($sp)
	# read int a
	li $v0 5
	syscall
# $t1: None -> b
	# now $t1 is b
	move $t1 $v0
	sw $t1 -12 ($sp)
	# read int b
	li $v0 4
	la $a0 string_43
	syscall
	# print str 43
	li $v0 5
	syscall
# $t2: None -> compareop
	# now $t2 is compareop
	move $t2 $v0
	sw $t2 -16 ($sp)
	# read int compareop
# $t3: None -> a
	# now $t3 is a
	lw $t3 -8 ($sp)
	sw $t3 -24 ($sp)
# push param: a
# $t4: None -> b
	# now $t4 is b
	lw $t4 -12 ($sp)
	sw $t4 -28 ($sp)
# push param: b
# $t5: None -> compareop
	# now $t5 is compareop
	lw $t5 -16 ($sp)
	sw $t5 -32 ($sp)
# push param: compareop
	# save start
	sw $ra -140 ($sp)
	addi $sp $sp -24
	jal func_richcompare
	# recover start
	addi $sp $sp 24
	lw $ra -140 ($sp)
	# recover end
# $t6: None -> #73
	# now $t6 is #73
	move $t6 $v0
# $t7: None -> result
	# now $t7 is result
	move $t7 $t6
	sw $t7 -20 ($sp)
# $s0: None -> result
	# now $s0 is result
	lw $s0 -20 ($sp)
	bgez $s0 label85
	j exit
label85:
	li $v0 4
	la $a0 string_1
	syscall
	# print str 1
# $s1: None -> compareop
	# now $s1 is compareop
	lw $s1 -16 ($sp)
	sw $s1 -24 ($sp)
# push param: compareop
	# save start
	sw $ra -100 ($sp)
	addi $sp $sp -24
	jal func_printcompareop
	# recover start
	addi $sp $sp 24
	lw $ra -100 ($sp)
	# recover end
# $s2: None -> result
	# now $s2 is result
	lw $s2 -20 ($sp)
	sw $s2 -24 ($sp)
# push param: result
	# save start
	sw $ra -100 ($sp)
	addi $sp $sp -24
	jal func_printresult
	# recover start
	addi $sp $sp 24
	lw $ra -100 ($sp)
	# recover end
exit:
