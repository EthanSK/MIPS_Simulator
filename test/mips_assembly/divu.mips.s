#author: ES5017
#expected_output: 2 243
#extra_info: tests simple divu of unsigned ints


lui $3, 0xFFFF
ori $3, $3, 0xFFF3 
#0xFFFF FFF3 = 4294967283 in $3

lui $4, 0x7FFF
#0x7FFF0000 = 2147418112 in $4

#therefore result should be 2 r 131059
#in binary this is 00000000000000000000000000000010 r 00000000000000011111111111110011

divu $3, $4			
mflo $5
mfhi $6

# srl $5, $5, 16
# srl $6, $6, 0

lui $9, 0x3000
sw $5 4($9)
sw $6 4($9)

jr $0