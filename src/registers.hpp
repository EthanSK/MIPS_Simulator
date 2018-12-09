#include <vector>
#include <cstdint>

#pragma once

class Registers
{
    std::vector<int> registers;
    uint32_t program_counter;
    int hi_register;
    int lo_register;

  public:
    Registers(); 
    void set_register(int index, int value);
    int get_register(int index);
    void set_program_counter(uint32_t value); //should enforce multiple of 4 or throw exception??
    uint32_t get_program_counter();
    void advance_program_counter(); //for maintainablitiy and neatness
    void set_hi(int value);
    void set_lo(int value);
    int get_hi();
    int get_lo();

    
};
