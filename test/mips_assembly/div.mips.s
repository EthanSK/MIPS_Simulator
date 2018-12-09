#author: ES5017
#expected_output: 39 8
#extra_info: tests simple div of negative and positive ints


lui $3, 0xFFFF
ori $3, $3, 0xFFF3 
#0xFFFF FFF3 =  -13 in $3

lui $4, 0x7FFF
#0x7FFF0000 = 2147418112 in $4

#therefore result should be -165186008 r 8
#in binary this is 11110110 00100111 0111011000101000 r 00000000000000000000000000001000

div $4, $3			
mflo $5
mfhi $6

srl $5, $5, 16
srl $6, $6, 0

lui $9, 0x3000
sw $5 4($9)
sw $6 4($9)

jr $0