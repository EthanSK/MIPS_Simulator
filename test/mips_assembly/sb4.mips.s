#author: ob1717
#expected_exit_code: 70
#extra_info: stores byte at second (corner) valid memory adress: 0x24000000 -1


lui $4, 0x2400

ori	$3, $0, 0x0046


sb		$3, -1($4)	
nop 
lb		$2, -1($4)		
	


jr $0