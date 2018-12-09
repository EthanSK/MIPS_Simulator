#author: ES5017
#expected_exit_code: 127
#extra_info: tests simple case for or

addi $3, $0, 0x0073
addi $4, $0, 0x006F

or $2, $3, $4

jr $0
