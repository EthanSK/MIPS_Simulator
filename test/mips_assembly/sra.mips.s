#author: ES5017
#expected_exit_code: -2
#extra_info: tests simple case for sra

lui $1, 0x8069

sra $2, $1, 30

jr $0
