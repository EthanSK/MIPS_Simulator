#author: ES5017
#expected_exit_code: -11
#extra_info: tests lb reading at addr_data - 1 throws exception

lui $3, 0x2345
ori $3, $3, 0x787A

#memory address
lui $4, 0x2000
addi $4, $4, -1

sw $3, 1($4) 
lb $2, 0($4)
nop
jr $0