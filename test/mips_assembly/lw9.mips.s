#author: ob1717
#expected_exit_code: 0
#extra_info: loads word at last (corner) valid memory adress: 0x10FFFFC

lui $3, 0x2345
ori $3, $3, 0x787A


lui     $4, 0x10FF
ori     $4, $4, 0xFFFC

lw   $2, 0($4)

jr $0