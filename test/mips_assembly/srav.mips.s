#author: ES5017
#expected_exit_code: -2
#extra_info: tests simple case for srav

lui $1, 0x8069
addi $3, $0, 30

srav $2, $1, $3


jr $0
