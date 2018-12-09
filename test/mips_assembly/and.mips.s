#author: ES5017
#expected_exit_code: 17
#extra_info: tests simple case for and

addi $1, $0, 0xF1
addi $2, $0, 0x1F

and $2, $2, $1
jr $0
