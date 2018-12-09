#author: ES5017
#expected_exit_code: 0
#extra_info: tests simple case for slt condition not met

lui $1, 0x6FFF
addi $2, $0, 18

slt $2, $1, $2

jr $0
