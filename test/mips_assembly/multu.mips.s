#author: ES5017
#expected_output: 13 127
#extra_info: tests simple multiply unsigned


lui $3, 0xFFFF
ori $3, $3, 0xFFF3 
#0xFFFF FFF3 = 4294967283 in $3

lui $4, 0x7FFF
#0x7FFF0000 = 2147418112 in $4

#therefore result should be 9223090533961629696
#in hex this is 7ffefff9800d0000
#in binary this is 01111111111111101111111111111001 10000000000011010000000000000000

multu $3, $4			
mflo $5
mfhi $6

srl $5, $5, 16
srl $6, $6, 24

lui $9, 0x3000
sw $5 4($9)
sw $6 4($9)

jr $0