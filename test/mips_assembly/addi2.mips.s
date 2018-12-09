#author: ES5017
#expected_exit_code: -120
#extra_info: tests addi result at nth bit

#0xabcd = 43981
#0x6789 = 1737031680
#the result may look weird, remember the immediate is signed
lui $3, 0x6789
addi $2, $3, 0xABCD
srl $2, $2, 16
jr $0
