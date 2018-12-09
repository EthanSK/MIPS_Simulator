#author: ES5017
#expected_exit_code: -11
#extra_info: loads a word from unreadable memory and throws exception

addi $3, $0, 9
lui $4, 0x3000

sw $3, 8($4) 
lw $2, 8($4)
nop
jr $0