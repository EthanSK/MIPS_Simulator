#expected_output: 255 255 255 255
#author: ob1717
#extra_info: 0 / a where a > 0 tets lo/quotient

addi	$4, $0, 0
addi 	$3, $0, 5 

div 	$4, $3

mfhi	$4

lui 	$3, 0xFFFF
ori		$3, $3, 0xFFFF
xor 	$4, $4, $3

lui 	$9, 0x3000
sw 		$4, 4($9)
srl 	$4, $4, 8
sw 		$4, 4($9)
srl 	$4, $4, 8
sw 		$4, 4($9)
srl 	$4, $4, 8
sw 		$4, 4($9)

jr		 $0
nop





