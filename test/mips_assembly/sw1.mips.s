#author: ES5017
#expected_output: 104 115
#extra_info: tests sw with stdout

#doesnt need to rely on lw working

addi $31, $0, 104
addi $30, $0, 0xF373

lui $9, 0x3000
sw $31 4($9)
sw $30 4($9)

jr $0
