#author: ES5017
#expected_exit_code: -10
#extra_info: tests that add correctly traps overflow with negative numbers

lui $6, -1

#most negative 32 bit number:
lui $4, 0x8000

add $5, $4, $6

jr $0