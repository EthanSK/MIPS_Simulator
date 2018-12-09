#author: ES5017
#expected_exit_code: 19
#extra_info: test memory mapped input without memory mapped output

#adds the ascii decimal numbers and returns the low 8 bits of the result as exit code low 8 bits of 531 is 19. ascii for 'hello', which is what is in the wibble.txt file we use for testbench input test

lui $9, 0x3000
addi $6, $0, 6
next_input:
lw $5 0($9)
nop
addu $2, $2, $5
addi $1, $1, 1
bne $1, $6, next_input
nop
jr $0
