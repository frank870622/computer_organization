main:
    	addi $t1, $s0, 1
	addi $t2, $s0, 0
	addi $t3, $s0, 1
loop:
	add $t0, $t1, $t2
	addi $t2, $t1, 0
	addi $t1, $t0, 0
	addi $t3, $t3, 1
	bne $t3, 25, loop
    

    jr $ra
