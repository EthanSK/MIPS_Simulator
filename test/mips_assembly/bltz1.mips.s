#author: ES5017
#expected_exit_code: 5
#extra_info: tests if bltz doesnt occur when register in positive


addi $3, $0, 0

#should not branch
bltz $3, 2

addi $4, $0, 7

addi $5, $0, 2

#would be 3+2=5 if branch not taken
addi $2, $5, 3



jr $0
