#author: ob1717
#expected_exit_code: 70
#extra_info: stores byte at first (corner) valid memory adress: 0x20000000 -1


lui $4, 0x2000

ori	$3, $0, 0x0046


sb		$3, 0($4)	
nop 
lb		$2, 0($4)		
	


jr $0