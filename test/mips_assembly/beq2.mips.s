#author: ES5017
#expected_exit_code: 5
#extra_info: tests if beq doesnt occur when registers are not equal


 addi $3, $0, 1

#should not branch
beq $3, $0, 2

addi $4, $0, 7

addi $5, $0, 2

#would be 3+2=5 if branch not taken
addi $2, $5, 3



jr $0
