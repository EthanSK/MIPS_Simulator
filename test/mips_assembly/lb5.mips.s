#author: ob1717
#expected_exit_code: 60
#extra_info: loads half word at first (corner) valid memory adress: 0x10000000

lui $3, 0x2345
ori $3, $3, 0x787A


lui     $4, 0x1000

lb    $2, 0($4)

jr $0