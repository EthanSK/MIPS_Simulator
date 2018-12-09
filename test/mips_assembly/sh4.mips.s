#author: ob1717
#expected_exit_code: 18
#extra_info: stores half word at first (corner) valid memory adress: 0x20000000 


lui $4, 0x2000

ori	$3, $0, 0x1246


sh		$3, 0($4)	
nop 
lb		$2, 0($4)		
	


jr $0