#author: ob1717
#expected_exit_code: 122
#extra_info: loads half word at second (corner) valid memory adress: 0x23FFFFFF and store

lui $3, 0x2345
ori $3, $3, 0x787A


lui   $4, 0x2400


sw		$3, -4($4)		


lh    $2, -2($4)

jr $0