#author: ES5017
#expected_exit_code: -51
#extra_info: tests simple case for sb

#assumes lw works (and others ofc)

lui $18, 0xFEDC
ori $18, $18, 0xABCD

lui $29, 0x1FFF
ori $29, $29, 0xFFFC


sb $18 11($29)

lw $2 8($29)
nop

jr $0
