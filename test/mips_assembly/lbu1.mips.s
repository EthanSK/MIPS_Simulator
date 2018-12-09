#author: ES5017
#expected_exit_code: 11
#extra_info: tests lbu zero extension

lui $3, 0x3345
ori $3, $3, 0x98BA

#memory address
lui $4, 0x2000

sw $3, 8($4) 
lbu $2, 11($4)
nop
srl $2, $2, 4
jr $0