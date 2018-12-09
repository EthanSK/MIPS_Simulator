#author: ES5017
#expected_exit_code: 0
#extra_info: tests that $0 cannot be written to

addi $0, $0, 0xFFFF
addi $2, $0, 0

jr $0