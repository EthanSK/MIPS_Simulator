#author: ES5017
#expected_exit_code: -102
#extra_info: tests simple case for lbu

lui $3, 0x2345
ori $3, $3, 0x789A

#memory address
lui $4, 0x2000

sw $3, 8($4) 
lbu $2, 11($4)
nop
jr $0