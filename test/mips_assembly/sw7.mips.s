#author: ob1717
#expected_exit_code: -11
#extra_info: stores byte at second (corner) invalid memory adress: 0x24000000 


lui 	$4, 0x2400

sw		$3, 0($4)	
		
jr 		$0