#author: ES5017
#expected_exit_code: 6
#expected_output: 8
#extra_info: tests simple case for bltzal and branch delay slot with a function assuming stdout works

addi $3, $0, -1
lui $9, 0x3000

bltzal $3, function

addi $4, $0, 8

addi $5, $0, 2
addi $2, $5, 4

#should have added 7 to $4 if branch delay slot works
jr $0
nop

function: sw $4, 4($9)
jr $31
nop

