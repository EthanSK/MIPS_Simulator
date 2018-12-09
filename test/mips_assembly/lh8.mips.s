#author: ob1717
#expected_exit_code: 69
#extra_info: loads half word at first (corner) valid memory adress: 0x20000000 and store

lui $3, 0x2345
ori $3, $3, 0x787A


lui   $4, 0x2000
ori		$4, $4, 0x0000

sw		$3, 0($4)		


lh    $2, 0($4)

jr $0