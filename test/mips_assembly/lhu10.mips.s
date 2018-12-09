#author: ob1717
#expected_exit_code: -11
#extra_info: loads half word at second (corner) invalid memory adress: 0x23FFFFFF +2



lui   $4, 0x23FF
ori		$4, $4, 0xFFFF

lhu    $2, 2($4)

jr $0