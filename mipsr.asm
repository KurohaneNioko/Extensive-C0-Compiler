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
# $t0: None -> x
	# now $t0 is x
	li $t0 2
	sw $t0 _x
	li $v0 1
# $t1: None -> x
	# now $t1 is x
	lw $t1 _x
	move $a0 $t1
	syscall
	# print int x
# $t2: None -> x
	# now $t2 is x
	lw $t2 _x
	subu $t2 $0 $t2
	sw $t2 _x
	li $v0 1
# $t3: None -> x
	# now $t3 is x
	lw $t3 _x
	move $a0 $t3
	syscall
	# print int x
# $t4: None -> x
	# now $t4 is x
	lw $t4 _x
	subu $t4 $0 $t4
	sw $t4 _x
	li $v0 1
# $t5: None -> x
	# now $t5 is x
	lw $t5 _x
	move $a0 $t5
	syscall
	# print int x
# $t6: None -> x
	# now $t6 is x
	lw $t6 _x
	addi $t6 $t6 30
	sw $t6 _x
	li $v0 1
# $t7: None -> x
	# now $t7 is x
	lw $t7 _x
	move $a0 $t7
	syscall
	# print int x
# $s0: None -> x
	# now $s0 is x
	lw $s0 _x
	addi $s0 $s0 2
	sw $s0 _x
	li $v0 1
# $s1: None -> x
	# now $s1 is x
	lw $s1 _x
	move $a0 $s1
	syscall
	# print int x
exit:
