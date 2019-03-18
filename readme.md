####Mips simulator

Simulates MIPS core instructions and includes a testbench written in bash.
Conforms to this spec:
https://github.com/m8pple/arch2-2018-cw

###To use:

make clean
make simulator
make testbench
bin/mips_testbench  bin/mips_simulator


###Results:

Testing & Simulation: 64/80 = 80%

###Comments:
- Excellent simulator; passed all tests.
- Excellent simulator memory footprint; no issues at all under memory stress test.
- Well written simulator making good use of OOP features. Avoid leaving old code behind; you can always use git to roll back. Largely undocumented.
- Reasonably comprehensive testbench but hits some implementation-defined memory behaviours.
- Around 1/3 of tests passed even when buggy behaviour was injected for those instructions, so tests could've been better crafted to exercise their intended targets.
- Nicely writen testbench: builds binaries, neat handling of metadata, seems to be easily extensible. Again, avoid leaving old code behind.