#author: ES5017
#expected_output: 13 255
#extra_info: tests simple multiply of negative and positive ints


lui $3, 0xFFFF
ori $3, $3, 0xFFF3 
#0xFFFF FFF3 =  -13 in $3

lui $4, 0x7FFF
#0x7FFF0000 = 2147418112 in $4

#therefore result should be -27916435456
#in binary this is 11111111111111111111111111111001 10000000000011010000000000000000

mult $3, $4			
mflo $5
mfhi $6

srl $5, $5, 16
srl $6, $6, 24

lui $9, 0x3000
sw $5 4($9)
sw $6 4($9)

jr $0