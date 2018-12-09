#expected_exit_code: 8
#author: ES5017
#extra_info: tests simple case for add


addi $2, $0, 5
addi $3, $0, 3

add $2, $2, $3
jr $0
