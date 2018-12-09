#author: ES5017
#expected_exit_code: 115
#extra_info: tests simple case for andi

addi $3, $0, 0xF073
andi $2, $3, 0x0FFF
jr $0
