#author: ES5017
#expected_exit_code: 2
#extra_info: ensures div does not crash or throw exception when dividing by 0



lui $4, 0x7FFF

div $4, $3			
mflo $5
mfhi $6

srl $5, $5, 16
srl $6, $6, 0

lui $9, 0x3000
sw $5 4($9)
sw $6 4($9)
addi $2, $0, 2

jr $0