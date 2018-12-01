.data
a : .asciiz "fdwsafa12"
x2: .byte 5
x1 : .word 49
.text
fun1:
lui $t5 32
.globl main
main:
li $t1 26
sw $t1 x1
la $a0 a
la $s1 x1

.
