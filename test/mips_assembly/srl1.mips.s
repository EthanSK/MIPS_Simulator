#author: ES5017
#expected_output: 2
#extra_info: tests another simple case for srl

lui $1, 0x8069

srl $2, $1, 30

lui $9, 0x3000
sw $2 4($9)

jr $0
