#author: ES5017
#expected_exit_code: 0
#extra_info: test memory mapped input with lb assuming memory mapped output works

#expected_output: 104 101 108 108 111


#the above expected outputs are ascii for 'hello', which is what is in the wibble.txt file we use for testbench input test
#cat test/wibble.txt | bin/mips_simulator test/mips_binary/lh2.mips.bin

lui $9, 0x3000
ori $9, $9, 0x0002
addi $6, $0, 5

next_input:
lb $5 1($9)
nop
#write the input back to output so we can check it correctly read the input
sb $5 5($9)
addi $1, $1, 1
#don't branch if the counter has reached 5, the number of characters in the wibble.txt
bne $1, $6, next_input
nop
jr $0