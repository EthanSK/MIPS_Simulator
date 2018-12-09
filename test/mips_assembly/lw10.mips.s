#author: ob1717
#expected_exit_code: -11
#extra_info: loads word at last (corner) invalid memory adress: 0x10FFFFFF +4



lui     $4, 0x10FF
ori     $4, $4, 0xFFFF

lw    $2, 4($4)

jr $0