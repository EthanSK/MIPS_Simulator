#author: ES5017
#expected_output: 170 3
#extra_info: tests simple divu of a signed int that should be interpreted as unsigned


lui $3, 0xFFFF
ori $3, $3, 0xAAAB
#0xffff AAab = 4294945451 in $3

ori $4, $0, 0x4
#4 in $4

#therefore result should be 170 r 3
#in binary this is 00000000000000000000000011100111 r 00000000000000000000000000000010

divu $3, $4			
mflo $5
mfhi $6

# srl $5, $5, 16
# srl $6, $6, 0

lui $9, 0x3000
sw $5 4($9)
sw $6 4($9)

jr $0