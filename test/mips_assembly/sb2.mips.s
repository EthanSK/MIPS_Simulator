#author: ob1717
#expected_exit_code: -11
#extra_info: stores byte at first (corner) invalid memory adress: 0x20000000 -1


lui $4, 0x1000


sb		$t3, -1($s4)		


jr $0