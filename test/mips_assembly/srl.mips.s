#author: ES5017
#expected_exit_code: 7
#extra_info: tests simple case for srl

addi $1, $0, 0x7000
srl $2, $1, 12
jr $0
