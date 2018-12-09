#author: ES5017
#expected_exit_code: -7
#extra_info: tests lb sign extension

lui $3, 0x3345
ori $3, $3, 0x987A

#memory address
lui $4, 0x2000

sw $3, 8($4) 
lb $2, 10($4)
nop
srl $2, $2, 4
jr $0
