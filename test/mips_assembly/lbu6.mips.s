#author: ob1717
#expected_exit_code: -11
#extra_info: loads byte at last (corner) invalid memory adress: 0x10FFFFFF +1


lui     $4, 0x10FF
ori     $4, $4, 0xFFFF

lbu    $2, 1($4)

jr $0