#author: ES5017
#expected_exit_code: 1
#extra_info: tests simple case for sltu and ensures numbers are compared as unsigned

lui $1, 0xFFFF
addi $2, $0, 18

sltu $2, $2, $1

jr $0
