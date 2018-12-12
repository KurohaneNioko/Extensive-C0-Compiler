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
	j label2
label1:
# $t0: None -> #1
	# now $t0 is #1
	lw $t0 -4 ($sp)
	sw $t0 -92 ($sp)
	sw $t0 -108 ($sp)
	sw $t1 -112 ($sp)
	sw $t2 -116 ($sp)
	sw $t3 -120 ($sp)
	sw $t4 -124 ($sp)
	sw $t5 -128 ($sp)
	sw $t6 -132 ($sp)
	sw $t7 -136 ($sp)
	sw $s0 -140 ($sp)
	sw $s1 -144 ($sp)
	sw $s2 -148 ($sp)
	sw $s3 -152 ($sp)
	sw $s4 -156 ($sp)
	sw $s5 -160 ($sp)
	sw $s6 -164 ($sp)
	sw $s7 -168 ($sp)
	sw $fp -172 ($sp)
	sw $ra -176 ($sp)
	sw $sp -180 ($sp)
	addi $sp $sp -92
	jal func_fact
label2:
exit:
