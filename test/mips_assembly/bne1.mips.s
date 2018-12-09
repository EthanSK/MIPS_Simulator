#author: ES5017
#expected_exit_code: -11
#extra_info: tests out of instruction range branch (should throw memory error)

addi $3, $0, 8

bne $3, $0, -3
nop

addi $2, $0, 6

jr $0
