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
	jr $ra
	j label2
label1:
# $t1: None -> #1
	# now $t1 is #1
	lw $t1 -4 ($sp)
	sw $t1 -92 ($sp)
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
	jr $ra
label2:
	jr $ra
func_rt15:
	jr $ra
	jr $ra
func_fun2:
	jr $ra
	jr $ra
main:
# $t0: None -> aa
	# now $t0 is aa
	lw $t0 -136 ($sp)
	sw $t0 -216 ($sp)
	# save start
	sw $t0 -220 ($sp)
	sw $ra -224 ($sp)
	sw $sp -228 ($sp)
	addi $sp $sp -216
	jal func_fact
	# recover start
	addi $sp $sp 216
	lw $ra -224 ($sp)
	lw $t0 -220 ($sp)
	# recover end
# $t1: None -> #20
	# now $t1 is #20
	lw $t1 -32 ($sp)
	sw $t1 -216 ($sp)
	sw $t0 -220 ($sp)
	li $t9 1
	sw $t9 -224 ($sp)
	li $t9 4
	sw $t9 -228 ($sp)
	li $t9 2
	sw $t9 -232 ($sp)
	li $t9 -2
	sw $t9 -236 ($sp)
	# save start
	sw $t1 -240 ($sp)
	sw $ra -244 ($sp)
	sw $sp -248 ($sp)
	addi $sp $sp -216
	jal func_fun2
	# recover start
	addi $sp $sp 216
	lw $ra -244 ($sp)
	lw $t1 -240 ($sp)
	# recover end
	li $t9 4
	sw $t9 -216 ($sp)
	# save start
	sw $t1 -220 ($sp)
	sw $ra -224 ($sp)
	sw $sp -228 ($sp)
	addi $sp $sp -216
	jal func_fact
	# recover start
	addi $sp $sp 216
	lw $ra -224 ($sp)
	lw $t1 -220 ($sp)
	# recover end
	# save start
	sw $t1 -216 ($sp)
	sw $ra -220 ($sp)
	sw $sp -224 ($sp)
	addi $sp $sp -216
	jal func_rt15
	# recover start
	addi $sp $sp 216
	lw $ra -220 ($sp)
	lw $t1 -216 ($sp)
	# recover end
# $t2: None -> a
	# now $t2 is a
	lw $t2 -132 ($sp)
	blez $t2 label3
# $t3: None -> x
	# now $t3 is x
	lw $t3 _x
	bgtz $t3 label4
label4:
label3:
	beq $t3 0 label5
# $t4: None -> #38
	# now $t4 is #38
	lw $t4 -104 ($sp)
	bne $t2 $t4 label6
label6:
label5:
	bgez $t2 label7
	bltz $t3 label8
label8:
	j label9
label7:
label9:
label10:
	blt $t2 3 label10
label11:
	blez $t3 label12
	j label11
label12:
exit:
