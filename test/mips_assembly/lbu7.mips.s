#author: ob1717
#expected_exit_code: -11
#extra_info: loads byte at first (corner) invalid memory adress: 0x20000000 -1

lui $4, 0x1FFFF
ori	$4, $4, 0xFFFF

lbu	$2, 0($4)

jr $0
