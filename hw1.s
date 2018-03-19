.data
.text
main:

	addi $t1, $s0, 1
	addi $t2, $s0, 0
	addi $t3, $s0, 1

	jal fib
	li   $v0, 10               # program stop
	syscall
   
fib:
	add $t0, $t1, $t2
	addi $t2, $t1, 0
	addi $t1, $t0, 0
	addi $t3, $t3, 1
	bne $t3, 25, fib
    jr $ra
