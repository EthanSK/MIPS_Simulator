#author: ob1717
#expected_exit_code: 0
#extra_info: loads byte at last (corner) valid memory adress: 0x10FFFFF

lui     $4, 0x10FF
ori     $4, $4, 0xFFFF

lb    $2, 0($4)

jr $0