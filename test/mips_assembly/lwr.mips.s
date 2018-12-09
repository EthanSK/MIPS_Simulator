#author: ES5017
#expected_exit_code: -119
#extra_info: test simple case for lwr 

lui $1, 0x2000

lui $3, 0x6789
addi $3, $3, 0x7BCD
#we have in $3 0x6789ABCD

sw $3, 4($1)
lwr $2, 6($1)
nop
srl $2, $2, 8
jr $0

