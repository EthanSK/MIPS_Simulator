#author: ob1717
#expected_exit_code: -11
#extra_info: loads byte at invalid valid memory adress: 0x10000000 -1


lui $4, 0x0FFF
ori	$4, $4, 0xFFFF

lbu	$2, 0($4)

jr $0
