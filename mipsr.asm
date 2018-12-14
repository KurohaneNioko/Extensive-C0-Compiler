.data
_testchar1 : .byte 0
_testchar2 : .byte 0
_x : .word 0
_xxxx : .word 0
_yyy : .space 28
_zzzzzzz : .word 0
string_1 : .asciiz "!@#$%%abcd114514ABCD963287~;: "
string_2 : .asciiz "1 hit "
string_3 : .asciiz "2 hit"
string_4 : .asciiz "3 hit "
string_5 : .asciiz "4 hit "
string_6 : .asciiz "5 hit "
string_7 : .asciiz "6 hit "
.text
.globl main
func_fact:
# $t0: None -> t
	# now $t0 is t
	lw $t0 -0 ($sp)
	bge $t0 3 label1
	move $v0 $t0
	jr $ra
	j label2
label1:
# $t1: None -> #1
	# now $t1 is #1
	sub $t1 $t0 1
	sw $t1 -92 ($sp)
# push param: #1
	# save start
	sw $t0 -96 ($sp)
	sw $ra -100 ($sp)
	sw $sp -104 ($sp)
	addi $sp $sp -92
	jal func_fact
	# recover start
	addi $sp $sp 92
	lw $ra -100 ($sp)
	lw $t0 -96 ($sp)
	# recover end
# $t2: None -> #2
	# now $t2 is #2
	move $t2 $v0
# $t3: None -> #3
	# now $t3 is #3
	mul $t3 $t2 $t0
	move $v0 $t3
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
	li $v0 65
	jr $ra
	jr $ra
main:
# $t0: None -> x
	# now $t0 is x
	li $t0 -1
# $t1: None -> #13
	# now $t1 is #13
	li $t1 -4
# $t2: None -> r
	# now $t2 is r
	move $t2 $t1
# $t3: None -> aa
	# now $t3 is aa
	li $t3 6
	sw $t3 -216 ($sp)
# push param: aa
	# save start
	sw $t0 -220 ($sp)
	sw $t1 -224 ($sp)
	sw $t2 -228 ($sp)
	sw $t3 -232 ($sp)
	sw $ra -236 ($sp)
	sw $sp -240 ($sp)
	addi $sp $sp -216
	jal func_fact
	# recover start
	addi $sp $sp 216
	lw $ra -236 ($sp)
	lw $t3 -232 ($sp)
	lw $t2 -228 ($sp)
	lw $t1 -224 ($sp)
	lw $t0 -220 ($sp)
	# recover end
# $t4: None -> #14
	# now $t4 is #14
	move $t4 $v0
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
	sub $s2 $t0 $t2
	sw $s2 -216 ($sp)
# push param: #20
	sw $t3 -220 ($sp)
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
	sw $t0 -240 ($sp)
	sw $t1 -244 ($sp)
	sw $t4 -248 ($sp)
	sw $t5 -252 ($sp)
	sw $t6 -256 ($sp)
	sw $t7 -260 ($sp)
	sw $s0 -264 ($sp)
	sw $s1 -268 ($sp)
	sw $s2 -272 ($sp)
	sw $ra -276 ($sp)
	sw $sp -280 ($sp)
	addi $sp $sp -216
	jal func_fun2
	# recover start
	addi $sp $sp 216
	lw $ra -276 ($sp)
	lw $s2 -272 ($sp)
	lw $s1 -268 ($sp)
	lw $s0 -264 ($sp)
	lw $t7 -260 ($sp)
	lw $t6 -256 ($sp)
	lw $t5 -252 ($sp)
	lw $t4 -248 ($sp)
	lw $t1 -244 ($sp)
	lw $t0 -240 ($sp)
	# recover end
# $s3: None -> #21
	# now $s3 is #21
	move $s3 $v0
	li $t9 4
	sw $t9 -216 ($sp)
# push param: 4
	# save start
	sw $t0 -220 ($sp)
	sw $t1 -224 ($sp)
	sw $t4 -228 ($sp)
	sw $t5 -232 ($sp)
	sw $t6 -236 ($sp)
	sw $t7 -240 ($sp)
	sw $s0 -244 ($sp)
	sw $s1 -248 ($sp)
	sw $s2 -252 ($sp)
	sw $s3 -256 ($sp)
	sw $ra -260 ($sp)
	sw $sp -264 ($sp)
	addi $sp $sp -216
	jal func_fact
	# recover start
	addi $sp $sp 216
	lw $ra -260 ($sp)
	lw $s3 -256 ($sp)
	lw $s2 -252 ($sp)
	lw $s1 -248 ($sp)
	lw $s0 -244 ($sp)
	lw $t7 -240 ($sp)
	lw $t6 -236 ($sp)
	lw $t5 -232 ($sp)
	lw $t4 -228 ($sp)
	lw $t1 -224 ($sp)
	lw $t0 -220 ($sp)
	# recover end
# $s4: None -> #22
	# now $s4 is #22
	move $s4 $v0
# $s5: None -> #23
	# now $s5 is #23
	move $s5 $0
	# save start
	sw $t0 -216 ($sp)
	sw $t1 -220 ($sp)
	sw $t4 -224 ($sp)
	sw $t5 -228 ($sp)
	sw $t6 -232 ($sp)
	sw $t7 -236 ($sp)
	sw $s0 -240 ($sp)
	sw $s1 -244 ($sp)
	sw $s2 -248 ($sp)
	sw $s3 -252 ($sp)
	sw $s4 -256 ($sp)
	sw $s5 -260 ($sp)
	sw $ra -264 ($sp)
	sw $sp -268 ($sp)
	addi $sp $sp -216
	jal func_rt15
	# recover start
	addi $sp $sp 216
	lw $ra -264 ($sp)
	lw $s5 -260 ($sp)
	lw $s4 -256 ($sp)
	lw $s3 -252 ($sp)
	lw $s2 -248 ($sp)
	lw $s1 -244 ($sp)
	lw $s0 -240 ($sp)
	lw $t7 -236 ($sp)
	lw $t6 -232 ($sp)
	lw $t5 -228 ($sp)
	lw $t4 -224 ($sp)
	lw $t1 -220 ($sp)
	lw $t0 -216 ($sp)
	# recover end
# $s6: None -> #26
	# now $s6 is #26
	move $s6 $v0
# $s7: None -> #27
	# now $s7 is #27
# $fp: None -> #25
	# now $fp is #25
	lw $fp -52 ($sp)
	add $s7 $fp $s6
# $t2: #28 -> #28
	# now $t2 is #28
	mul $t2 $s7 1
# $t3: #29 -> #29
	# now $t3 is #29
	sub $t3 $0 $t2
	sw $t4 -8 ($sp)
# MemAccess $t4: #30 -> #30
	# now $t4 is #30
	li $t4 36
	sw $t5 -12 ($sp)
# MemAccess $t5: #31 -> #31
	# now $t5 is #31
	sub $t9 $t4 2
	sub $t5 $0 $t9
	sw $t6 -16 ($sp)
# MemAccess $t6: #32 -> #32
	# now $t6 is #32
	add $t6 $t3 $t5
	sw $t7 -20 ($sp)
# MemAccess $t7: #33 -> #33
	# now $t7 is #33
	li $t7 218
	sw $s0 -24 ($sp)
# MemAccess $s0: #34 -> #34
	# now $s0 is #34
	add $s0 $t6 $t7
	sw $s1 -28 ($sp)
# MemAccess $s1: aa -> aa
	# now $s1 is aa
	move $s1 $s0
	sw $s2 -32 ($sp)
# MemAccess $s2: a -> a
	# now $s2 is a
	move $s2 $s1
	blez $s2 label3
	bgtz $t0 label4
	sw $s3 -36 ($sp)
# MemAccess $s3: #35 -> #35
	# now $s3 is #35
	div $s3 $s2 $t0
	sw $s4 -40 ($sp)
# MemAccess $s4: #36 -> #36
	# now $s4 is #36
	mul $s4 $s3 $s2
	sw $s5 -44 ($sp)
# MemAccess $s5: r -> r
	# now $s5 is r
	move $s5 $s4
label4:
	sw $s6 -56 ($sp)
# MemAccess $s6: #37 -> #37
	# now $s6 is #37
	add $s6 $s5 $s1
	move $s5 $s6
label3:
	beq $t0 0 label5
	sw $s7 -60 ($sp)
# MemAccess $s7: #38 -> #38
	# now $s7 is #38
	li $s7 -4
	bne $s2 $s7 label6
	sw $fp -52 ($sp)
# MemAccess $fp: #39 -> #39
	# now $fp is #39
	add $fp $s5 1
	move $s5 $fp
label6:
label5:
	bgez $s2 label7
	bltz $t0 label8
	sw $t0 _x
# MemAccess $t0: #40 -> #40
	# now $t0 is #40
	add $t0 $s5 $s2
	move $s5 $t0
label8:
	j label9
label7:
# $s2: #41 -> #41
	# now $s2 is #41
	mul $s2 $s5 -1
	move $s5 $s2
label9:
	sw $t1 -4 ($sp)
# MemAccess $t1: #42 -> #42
	# now $t1 is #42
	li $t1 -2
	sw $t2 -64 ($sp)
# MemAccess $t2: a -> a
	# now $t2 is a
	move $t2 $t1
label10:
	sw $t3 -68 ($sp)
# MemAccess $t3: #43 -> #43
	# now $t3 is #43
	sw $s3 -92 ($sp)
# MemAccess $s3: x -> x
	# now $s3 is x
	lw $s3 _x
	add $t3 $s3 4
	move $s3 $t3
	add $t2 $t2 1
	blt $t2 3 label10
label11:
	blez $s3 label12
	sw $s4 -96 ($sp)
# MemAccess $s4: #44 -> #44
	# now $s4 is #44
	sub $s4 $s3 2
	move $s3 $s4
	j label11
label12:
exit:
