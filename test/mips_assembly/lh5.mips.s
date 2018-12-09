#author: ob1717
#expected_exit_code: 0
#extra_info: loads byte at last (corner) valid memory adress: 0x10FFFFE

lui $3, 0x2345
ori $3, $3, 0x787A


lui     $4, 0x1100

lh    $2, -2($4)

jr $0