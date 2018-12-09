#author: ES5017
#expected_exit_code: -11
#extra_info: tests load word reading outside addr_data range throws exception

addi $3, $0, 9
lui $4, 0x2000
addi $4, $4, -4

sw $3, 0($4) 
lw $2, 0($4)
nop
jr $0