#author: ob1717
#expected_exit_code: 122
#extra_info: loads word at first (corner) valid memory adress: 0x20000000 and store

lui $3, 0x2345
ori $3, $3, 0x787A


lui   $4, 0x2000
ori		$4, $4, 0x0000

sw		$3, 0($4)		

lw    $2, 0($4)

jr $0