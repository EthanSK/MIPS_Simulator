#author: ES5017
#expected_exit_code: 9
#extra_info: tests simple case for load word

addi $3, $0, 9
lui $4, 0x2000


sw $3, 8($4) 
lw $2, 8($4)
nop
jr $0