#include <stdint.h>
#include <cstdlib>
#include <iostream>
#include <bitset>
#include "memory.hpp"
#include "registers.hpp"
#include "instructions.hpp"
#include "exceptions.hpp"

using namespace std;

/* this program uses types as containers, not full values. You will only see 32 bit types to represent binary */

void custom_exit(int exit_code, Memory *memory, File_io *file_io, Registers *registers, Instruction_helper *instruction_helper)
{
    //cerr << "custom exiting" << endl;
    delete memory;
    delete file_io;
    delete registers;
    delete instruction_helper;
    cerr << endl
         << endl;
    std::exit(exit_code);
}

int main(int argc, char *argv[])
{
    cerr << "programme path: " << argv[0] << endl;

    Memory *memory = new Memory();
    File_io *file_io = new File_io();
    Registers *registers = new Registers();
    Instruction_helper *instruction_helper = new Instruction_helper(registers, memory);

    try
    {
        if (argc != 2)
            throw Environment_error(); //incorrect number of command line args

        file_io->get_binary_file(argv[1]);
        memory->set_instructions(file_io->instructions, file_io->number_of_instructions);
        instruction_helper->number_of_instructions = file_io->number_of_instructions;
        //Load_delay::should_delayed_load = false;

        // bool has_program_finished = false;
        // int test_counter = 0;
        while (true)
        {
            //test_counter++;
            uint32_t next_instruction = memory->get_instruction(registers->get_program_counter());
            instruction_helper->decode_and_execute(next_instruction); //THE BIG BOI FUNCTION

            // if (registers->get_program_counter() > Memory::ADDR_INSTR + 100 || test_counter > 100)
            // {
            //     has_program_finished = true;
            // }
        }
    }
    catch (const End_of_program &e)
    {
        cerr << "\n*** terminating execution due to end of binary file ***" << endl; //flush buffer
        uint8_t exit_code = Bitwise_helper::extract_char(0, registers->get_register(2));
        custom_exit(exit_code, memory, file_io, registers, instruction_helper);
    }
    catch (const Mips_exception &e)
    {
        cerr << "Mips exception thrown: ";
        std::cerr << e.what() << '\n';
        custom_exit(e.exit_code(), memory, file_io, registers, instruction_helper);
    }
    catch (...)
    {
        custom_exit(Internal_error().exit_code(), memory, file_io, registers, instruction_helper); //HAX 4 DAYS
    }

    return 0;
}