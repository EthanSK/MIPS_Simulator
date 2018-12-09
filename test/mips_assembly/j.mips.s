#author: ES5017
#expected_exit_code: 40
#extra_info: tests simple case for jump with branch delay slot

j 5
addi $2, $2, 21
addi $2, $2, 69
addi $2, $2, 420
addi $2, $2, 666
addi $2, $2, 19

jr $0
