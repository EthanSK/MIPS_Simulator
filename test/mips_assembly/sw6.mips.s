#author: ob1717
#expected_exit_code: 18
#extra_info: stores word at second (corner) valid memory adress: 0x24000000 -4


lui $4, 0x2400

lui	$3, 0x1246


sw		$3, -4($4)	
nop 
lb		$2, -4($4)		
	


jr $0