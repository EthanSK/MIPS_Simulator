#author: ES5017
#expected_exit_code: 9
#extra_info: tests lhu zero extension

lui $3, 0x3345
ori $3, $3, 0x987A

#memory address
lui $4, 0x2000

sw $3, 8($4) 
lhu $2, 10($4)
nop
srl $2, $2, 12
jr $0