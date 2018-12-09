#author: ES5017
#expected_exit_code: -85
#extra_info: tests simple case for sh

#assumes lw works (and others ofc)

lui $18, 0xFEDC
ori $18, $18, 0xABCD

lui $29, 0x1FFF
ori $29, $29, 0xFFFC


sh $18 10($29)

lw $2 8($29)
nop
srl $2, $2, 8

jr $0
