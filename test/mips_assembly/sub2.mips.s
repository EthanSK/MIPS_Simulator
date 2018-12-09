#expected_exit_code: -10
#author: ob1717
#extra_info: tests corner case of sub trap initiated

lui $2, 0x8001
lui $3, 0x0002

sub $4, $2, $3


#if trap isnt met outputs r4 to answer to further investigate
lui $9, 0x3000
sw $4, 4($9)
jr $0