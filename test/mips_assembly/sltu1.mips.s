#author: ES5017
#expected_exit_code: 0
#extra_info: tests simple case for sltu condition not met

lui $1, 0xCFFF
addi $2, $0, 18

sltu $2, $1, $2

jr $0
