#author: ES5017
#expected_output: 137 103 170 171
#extra_info: tests lwl with lwr and register merge is correct

lui $1, 0x2000

lui $3, 0x6789
ori $3, $3, 0xABAA
#we have in $3 0x6789ABAA

sw $3, 0($1)
sw $3, 4($1)


addi $9, $0, 0x1234

lwl $9, 2($1) 
nop
lwr $9, 5($1) 

#hte value in $9 should be 0xABAA6789

lui $10, 0x3000

sw $9 4($10)
srl $9, $9, 8
sw $9 4($10)
srl $9, $9, 8
sw $9 4($10)
srl $9, $9, 8
sw $9 4($10)


jr $0

