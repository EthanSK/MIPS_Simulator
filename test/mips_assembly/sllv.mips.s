#author: ES5017
#expected_exit_code: 96
#extra_info: tests case for sllv making sure to only use low 5 order bits of gpr

addi $1, $0, 0x2305
addi $2, $0, 3

sllv $2, $2, $1
jr $0
