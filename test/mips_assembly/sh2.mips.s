#author: ES5017
#expected_output: 99 84 122
#extra_info: tests that sh triggers stdout


lui $18, 0xFE7A
ori $18, $18, 0x5463

lui $22, 0x3000

sh $18 6($22)
srl $18, $18, 8
sh $18 6($22)
srl $18, $18, 8
sh $18 6($22)

jr $0
