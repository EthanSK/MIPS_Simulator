#author: ob1717
#expected_exit_code: -11
#extra_info: stores half at first (corner) invalid memory adress: 0x20000000 -2


lui $4, 0x1000


sh	$3, -2($4)		


jr $0