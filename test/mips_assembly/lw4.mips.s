#author: ES5017
#expected_exit_code: 0
#extra_info: tests uninitialised word 

addi $3, $0, 9
lui $4, 0x2000

lw $2, 80($4)
nop
jr $0