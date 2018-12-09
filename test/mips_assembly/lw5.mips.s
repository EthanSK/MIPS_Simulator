#author: ES5017
#expected_exit_code: -11
#extra_info: tests misaligned word 

addi $3, $0, 9
lui $4, 0x2000

lw $2, 81($4)
nop
jr $0