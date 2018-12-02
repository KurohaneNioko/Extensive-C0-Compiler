.data
a : .asciiz "fdwsafa12\n"
x2: .byte 5
x1 : .word 49
.extern x 3
.extern y 8
.text
fun1:
lui $t5 32
.globl main
main:
li $t1 26
sw $t1 x1
la $a0 a
la $s1 x1
sw $t1, 0x10010008
seq $t9, $0, $0