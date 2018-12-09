#author: ES5017
#expected_exit_code: 17
#extra_info: tests simple case for sub


addi $2, $0, 50
addi $3, $0, 33

sub $2, $2, $3
jr $0

