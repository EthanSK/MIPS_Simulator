#author: ES5017
#expected_exit_code: 1
#extra_info: tests simple case for sltu and ensures numbers are compared as unsigned

addi $2, $0, 18

sltiu $2, $2, 0xFFFF

jr $0
