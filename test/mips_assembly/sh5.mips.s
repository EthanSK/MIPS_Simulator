#author: ob1717
#expected_exit_code: 18
#extra_info: stores half word at second (corner) valid memory adress: 0x24000000 -2


lui $4, 0x2400

ori	$3, $0, 0x1246


sh		$3, -2($4)	
nop 
lb		$2, -2($4)		
	


jr $0