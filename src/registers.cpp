#include "registers.hpp"
#include "memory.hpp"
#include "instructions.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

Registers::Registers()
{
    cerr << "initialising registers " << endl;
    program_counter = Memory::ADDR_INSTR;
    hi_register = 0;
    lo_register = 0;
    // registers.reserve(32);
    // fill(registers.begin(), registers.end(), 0); //init to 0 - doesn't even work ugh
    for (size_t i = 0; i < 32; i++)
    {
        registers.push_back(0);
        //cerr << "intited register value at i = " << i << ": " << registers[i];
    }
}

void Registers::set_register(int index, int value)
{
    if (index != 0) //$zero is grounded to zero
    {
        registers[index] = value;
    }
}
int Registers::get_register(int index)
{
    return registers[index];
}
void Registers::set_program_counter(uint32_t value)
{
    program_counter = value;
}
uint32_t Registers::get_program_counter()
{
    return program_counter;
}

void Registers::advance_program_counter()
{
    set_program_counter(get_program_counter() + 4);
}
void Registers::set_hi(int value)
{
    hi_register = value;
}
void Registers::set_lo(int value)
{
    lo_register = value;
}
int Registers::get_hi()
{
    return hi_register;
}
int Registers::get_lo()
{
    return lo_register;
}
