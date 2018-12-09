#author: ES5017
#expected_exit_code: 3
#extra_info: tests case for srlv making sure to only use low 5 order bits of gpr

addi $1, $0, 0x2305
addi $2, $0, 96

srlv $2, $2, $1
jr $0


