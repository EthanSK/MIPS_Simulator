#author: ES5017
#expected_exit_code: -10
#extra_info: tests simple mtlo


addi $3, $0, -10
mtlo $3
mflo $2

jr $0