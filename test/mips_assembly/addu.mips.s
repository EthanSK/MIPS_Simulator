#author: ES5017
#expected_exit_code: 31
#extra_info: does a simple test of addu

addi $7, $0, 100
addi $3, $0, -69

addu $2, $7, $3

jr $0