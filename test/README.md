THE MIPS PARSER LISCENCE IS IN THE LISCENCE FILE IN test/mips-parser. WE DID NOT MAKE IT. The project can be found here: https://github.com/olly-larkin/mips-parser
We use this instead of mips-linux-gnu-gcc because it is cross platform and easier to develop with on macos

Tests are written in assembly and stored in txt files in test/mips_assembly

The file name must be of the instruction being tested, multiple files testing the same instruction must have a numerical identifier at the end, for example, add1.txt, lw3.txt

Running the testbench converts the assembly to readable binary format in test/mips_binary before running the simulator and passing every binary file in that directory as input through each test

information about the test is denoted by a hashtag, the name of the info field, a colon, then the value, for example:

'#author: bob s.'
'#extra_info: tests the add instruction for the simple case'

These fields will be placed in the message column of the output csv. Each field is separated by the | character

to write to stdout, use this snippet:

lui $9, 0x3000
sw $5 4($9)

stdin is 

lui $9, 0x3000
sw $5 0($9)