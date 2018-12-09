#author: ES5017
#expected_exit_code: 36
#extra_info: tests simple case for jump and link with branch delay slot

jal function
addi $2, $2, 21
jr $0
nop

function: addi $2, $2, 15
jr $ra
nop
