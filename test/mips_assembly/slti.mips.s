#author: ES5017
#expected_exit_code: 1
#extra_info: tests simple case for slti and ensures numbers are compared as signed

lui $2, 0xF013

slti $2, $2, 1

jr $0
