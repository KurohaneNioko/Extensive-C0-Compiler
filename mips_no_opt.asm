.data
.align 2
_x : .word 0
.text
.globl main
func_add:
# $t0: None -> i
	# now $t0 is i
	addu $t0 $0 $0
	sw $t0 -28 ($sp)
label1:
# $t1: None -> x
	# now $t1 is x
	lw $t1 _x
# $t2: None -> a
	# now $t2 is a
	lw $t2 -0 ($sp)
# $t3: None -> #1
	# now $t3 is #1
	addu $t3 $t1 $t2
# $t4: None -> i
	# now $t4 is i
	lw $t4 -28 ($sp)
# $t5: None -> b
	# now $t5 is b
	lw $t5 -4 ($sp)
# $t6: None -> #2
	# now $t6 is #2
	mul $t6 $t4 $t5
# $t7: None -> #3
	# now $t7 is #3
	addu $t7 $t3 $t6
# $s0: None -> c
	# now $s0 is c
	lw $s0 -8 ($sp)
# $s1: None -> x
	# now $s1 is x
	subu $s1 $t7 $s0
	sw $s1 _x
# $s2: None -> i
	# now $s2 is i
	lw $s2 -28 ($sp)
	addi $s2 $s2 1
	sw $s2 -28 ($sp)
# $s3: None -> i
	# now $s3 is i
	lw $s3 -28 ($sp)
	blt $s3 10 label1
	jr $ra
func_t:
# $t0: None -> a
	# now $t0 is a
	lw $t0 -0 ($sp)
	ble $t0 3 label2
# $t1: None -> a
	# now $t1 is a
	lw $t1 -0 ($sp)
# $t2: None -> #4
	# now $t2 is #4
	addi $t2 $t1 -3
	li $v0 1
	move $a0 $t2
	syscall
	# print int #4
label2:
	jr $ra
main:
# $t0: None -> a
	# now $t0 is a
	li $t0 5
	sw $t0 -32 ($sp)
# $t1: None -> b
	# now $t1 is b
	li $t1 4
	sw $t1 -36 ($sp)
# $t2: None -> x
	# now $t2 is x
	li $t2 3
	sw $t2 _x
# $t3: None -> #5
	# now $t3 is #5
	li $t3 25
# $t4: None -> #6
	# now $t4 is #6
	li $t4 16
# $t5: None -> #7
	# now $t5 is #7
	li $t5 9
# $t6: None -> #8
	# now $t6 is #8
	li $t6 9
# $t7: None -> #9
	# now $t7 is #9
	addu $t7 $0 $0
# $s0: None -> d
	# now $s0 is d
	li $s0 25
	sw $s0 -44 ($sp)
# $s1: None -> #10
	# now $s1 is #10
	li $s1 625
# $s2: None -> #11
	# now $s2 is #11
	li $s2 576
# $s3: None -> c
	# now $s3 is c
	li $s3 49
	sw $s3 -40 ($sp)
	li $v0 1
	li $a0 49
	syscall
	# print int 49
exit:
