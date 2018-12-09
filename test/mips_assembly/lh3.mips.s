#author: ob1717
#expected_exit_code: -11
#extra_info: loads byte at first corner invalid memory adress: 0x10000000 -2


lui $4, 0x1000

lh	$2, -2($4)

jr $0
