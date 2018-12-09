#author: ES5017
#expected_exit_code: 122
#extra_info: tests simple case for lb

lui $3, 0x2345
ori $3, $3, 0x787A

#memory address
lui $4, 0x2000

sw $3, 8($4) 
lb $2, 11($4)
nop
jr $0