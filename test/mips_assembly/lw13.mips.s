#author: ob1717
#expected_exit_code: 122
#extra_info: loads word at second (corner) valid memory adress: 0x23FFFFFC and store

lui $3, 0x2345
ori $3, $3, 0x787A


lui   $4, 0x2400


sw		$3, -4($4)		


lw    $2, -4($4)

jr $0