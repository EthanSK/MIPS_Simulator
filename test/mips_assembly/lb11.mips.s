#author: ob1717
#expected_exit_code: -11
#extra_info: loads byte at second (corner) invalid memory adress: 0x23FFFFFF +1

lui   $4, 0x23FF
ori		$4, $4, 0xFFFF

lb    $2, 1($4)

jr $0