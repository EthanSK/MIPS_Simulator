#author: ES5017
#expected_exit_code: 40
#extra_info: tests simple case for jalr with branch delay slot


nop
nop

lui $10, 0x1000
addi $10, $10, 0x20

jalr $9, $10
addi $2, $2, 25
jr $0
nop


addi $2, $2, 15
jr $9
nop
