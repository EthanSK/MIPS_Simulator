#author: ob1717
#expected_exit_code: -11
#extra_info: loads word at first corner invalid memory adress: 0x10000000 -4


lui $4, 0x1000

lw	$2, -4($4)

jr $0
