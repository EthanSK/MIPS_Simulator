#author: ES5017
#expected_exit_code: 79
#extra_info: does a simple test of subu

addi $7, $0, 10
addi $3, $0, -69

subu $2, $7, $3

jr $0