#author: ES5017
#expected_output: 103
#extra_info: tests simple case for lui

lui $1, 0x6789

srl $1, $1, 24
lui $9, 0x3000
sw $1 4($9)

jr $0
