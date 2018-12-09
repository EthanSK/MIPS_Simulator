#author: ES5017
#expected_exit_code: 1
#extra_info: tests simple case for slt and ensures numbers are compared as signed

lui $1, 0xFFFF
addi $2, $0, 18

slt $2, $1, $2

jr $0
