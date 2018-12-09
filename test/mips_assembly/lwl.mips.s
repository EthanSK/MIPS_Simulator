#author: ES5017
#expected_exit_code: -51
#extra_info: test simple case for lwl 

lui $1, 0x2000

lui $3, 0x6789
addi $3, $3, 0xABCD
#we have in $3 0x6789ABCD

sw $3, 0($1)
lwl $4, 1($1)
srl $2, $4, 8

 
jr $0

