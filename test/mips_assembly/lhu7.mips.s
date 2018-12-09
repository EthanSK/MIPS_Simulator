#author: ob1717
#expected_exit_code: -11
#extra_info: loads half word at first (corner) invalid memory adress: 0x20000000 -2


lui $4, 0x1FFF
ori $4, $4, 0xFFFE

lhu	$2, 0($4)

jr $0
