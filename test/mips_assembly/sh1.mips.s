#author: ES5017
#expected_exit_code: 0
#extra_info: tests that only bottom halfword is stored

#assumes lw works (and others ofc)

lui $18, 0xFEDC
ori $18, $18, 0xABCD

lui $29, 0x1FFF
ori $29, $29, 0xFFFC


sh $18 8($29)

lw $2 8($29)
nop
srl $2, $2, 8

jr $0
