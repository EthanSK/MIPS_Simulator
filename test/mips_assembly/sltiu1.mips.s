#author: ES5017
#expected_exit_code: 0
#extra_info: tests simple case for sltiu condition not met

lui $1, 0x0FFF

sltiu $2, $1, 0x7FFF

jr $0
