#author: ES5017
#expected_exit_code: -51
#extra_info: tests simple case for sw

#assumes lw works (and others ofc)

lui $18, 0xFEDC
ori $18, $18, 0xABCD

lui $29, 0x2000

sw $18 0($29)

lw $2 0($29)
nop

jr $0
