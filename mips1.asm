.data
char1 : .byte 'a'
char2 : .byte 'b'
int1 : .word 757326
chararray : .space 14
int2 : .word 757326
a : .asciiz "fdwsaa12\\n"
aa : .asciiz "3rr34e\n"
x2: .byte 5
x1 : .word 49
.extern x 3
.extern y 8
.text
fun1:
lui $t5 '4'
.globl main
main:
li $t1 -26
sub $t2 $t1 20
li $a0 -4096
sra $a0 $a0 10
li $v0 1
syscall

# mul $s0 $a0 -3
