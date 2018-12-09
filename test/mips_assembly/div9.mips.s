#expected_output: 254 255 255 255
#author: ob1717
#extra_info: a/a tets lo/quotient

addi $4, $0, 0xFFFF
addi $3, $0, 0xFFFF

div $4, $3

mflo     $4

lui     $3, 0xFFFF
ori    $3, $3, 0xFFFF
xor     $4, $4, $3

lui     $9, 0x3000
sw         $4, 4($9)
srl     $4, $4, 8
sw         $4, 4($9)
srl     $4, $4, 8
sw         $4, 4($9)
srl     $4, $4, 8
sw         $4, 4($9)

jr         $0
nop