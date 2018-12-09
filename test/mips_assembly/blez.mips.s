#author: ES5017
#expected_exit_code: 4
#expected_output: 7
#extra_info: tests simple case for blez and branch delay slot

addi $3, $0, 0

#should branch to next instruction address + 8 (8 is 2<< 2)
blez $3, 2

addi $4, $0, 7

addi $5, $0, 2

#should branch to here
#would be 3+2=5 if branch not taken
addi $2, $5, 4

#should have added 7 to $4 if branch delay slot works
lui $9, 0x3000
sw $4, 4($9)


jr $0
