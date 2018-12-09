#author: ES5017
#expected_exit_code: 0
#extra_info: tests simple case for slti condition not met


addi $1, $0, 3

slti $2, $1, 0x9324

jr $0
