#include "memory.hpp"
#include <iostream>
#include "helpers.hpp"
#include "exceptions.hpp"
#include <algorithm>

using namespace std;

Memory::Memory()
{
    //only allocating each element once it is written to, when reading, return 0 if key does not exist
}

//==============================================private functions==============================================

void Memory::set_address(int address, unsigned char data)
{
    memory[address] = data;
}

unsigned char Memory::get_address(int address)
{
    if (memory.find(address) == memory.end())
    {
        return 0; //if the address has not been allocated yet
    }
    return memory[address];
}

void Memory::set_n_bytes(int n, int start_address, uint32_t value) //maximum of 4 bytes
{
    // cerr << hex << "n is: " << n << endl;

    for (int i = 0; i < n; i++)
    {
        // cerr << "nexloop" << endl;
        int index = start_address + i;
        unsigned char address_data = Bitwise_helper::extract_char(n - 1 - i, value);
        // cerr << hex << "addresss data: 0x" << (int)address_data << " index: 0x" << index  << endl;
        set_address(index, address_data);
        // cerr << "adress set" << endl;
        cerr << hex << "address set at 0x" << index << ": " << (int)memory[index] << endl;
    }
}

uint32_t Memory::get_n_bytes(int n, int start_address) //maximum of 4 bytes
{
    uint32_t result = 0;
    for (int i = 0; i < n; i++)
    {
        result += get_address(start_address + (n - 1 - i)) << (i * 8);
    }
    return result;
}

bool Memory::is_all_consecutive_n_bytes_in_range(int n, int start_address, int start_of_range, int length_of_range)
{
    int end_of_range = start_of_range + length_of_range - 1;
    //better to use loop to make sure
    // cerr << hex<< "start of range: " << start_of_range << "  length of range: " << length_of_range << " start address: " << start_address << " n bytes: " << n << endl;
    for (int ith_bit = start_address; ith_bit < start_address + n; ith_bit++)
    {
        if (ith_bit < start_of_range || ith_bit > end_of_range)
        {
            return false;
        }
    }
    return true;
}

bool Memory::is_any_consecutive_n_bytes_in_range(int n, int start_address, int start_of_range, int length_of_range)
{
    int end_of_range = start_of_range + length_of_range - 1;
    //better to use loop to make sure
    for (int ith_bit = start_address; ith_bit < start_address + n; ith_bit++)
    {
        if (ith_bit >= start_of_range && ith_bit <= end_of_range)
        {
            return true;
        }
    }
    return false;
}

//==============================================public functions==============================================

void Memory::set_instructions(uint32_t *instructions, int number_of_instructions)
{
    for (int i = 0; i < number_of_instructions; i++)
    {
        set_n_bytes(4, Memory::ADDR_INSTR + i * 4, instructions[i]);
    }
}

uint32_t Memory::get_instruction(int address)
{
    if (!is_addr_in_instr_range(4, address))
    {
        throw Memory_exception();
    }
    return get_n_bytes(4, address);
}

void Memory::set_n_bytes_of_data(int n, int start_address, uint32_t value)
{
    if (is_trying_to_set_stdout(n, start_address))
    {
        if (!is_addr_in_mapped_io_range(n, start_address))
        {
            throw Memory_exception();
        }
        set_n_bytes(n, start_address, value);
        int putchar_value = Bitwise_helper::extract_char(0, get_n_bytes(Memory::ADDR_PUTC_LENGTH, Memory::ADDR_PUTC));
        set_n_bytes(n, start_address, 0); //make sure it gets set back to 0 because this isn't actually memory
        if ((int)Bitwise_helper::sign_extend_to_32(n * 8, value) == EOF)
        {
            putchar_value = EOF;
        }
        cerr << dec << "putchar should be: " << putchar_value << endl;
        putchar(putchar_value);
        if (ferror(stdout))
        {
            throw IO_error();
        }
        cerr << endl;
        return;
    } //must be before range check or will throw as its out of range

    if (!is_addr_in_data_write_range(n, start_address))
    {
        throw Memory_exception();
    }

    set_n_bytes(n, start_address, value);
}

uint32_t Memory::get_n_bytes_of_data(int n, int start_address)
{
    // cerr << "start address: " << start_address << endl;
    if (is_trying_to_read_stdin(n, start_address)) //should be in get data function because its 'part' of it... so is addr null set
    {
        if (!is_addr_in_mapped_io_range(n, start_address)) //stuff like this should only really happen on things like lwl lwr or whatevs
        {
            throw Memory_exception();
        }
        //cerr << "is trying to read stdin" << endl;
        char input = getchar();
        set_n_bytes(n, start_address, input);
        int gotchar_value = Bitwise_helper::extract_char(0, get_n_bytes(Memory::ADDR_GETC_LENGTH, Memory::ADDR_GETC));
        set_n_bytes(n, start_address, 0); //make sure it gets set back to 0 because this isn't actually memory
        if (input == EOF)
        {
            gotchar_value = EOF;
        }
        cerr << dec << "stdin from gotchar: " << gotchar_value << endl;
        if (ferror(stdin))
        {
            throw IO_error();
        }

        return gotchar_value; //will be in lsb of return result
    }                         //must be before range check

    if (!is_addr_in_data_read_range(n, start_address))
    {
        throw Memory_exception();
    }

    return get_n_bytes(n, start_address);
}

bool Memory::is_addr_in_data_write_range(int number_of_bytes, int start_address) //applies to both read and write
{
    bool result = is_all_consecutive_n_bytes_in_range(number_of_bytes, start_address, Memory::ADDR_DATA, Memory::ADDR_DATA_LENGTH);
    if (!result)
        cerr << "address is not in data range: 0x" << start_address << endl;
    return result;
}

bool Memory::is_addr_in_data_read_range(int number_of_bytes, int start_address) //applies to both read and write
{
    bool condition1 = is_all_consecutive_n_bytes_in_range(number_of_bytes, start_address, Memory::ADDR_DATA, Memory::ADDR_DATA_LENGTH);
    bool condition2 = is_all_consecutive_n_bytes_in_range(number_of_bytes, start_address, Memory::ADDR_INSTR, Memory::ADDR_INSTR_LENGTH); //can read instruction memory too
    if (condition1 || condition2)
    {
        return true;
    }
    return false;
    cerr << "address is not in data range: 0x" << start_address << endl;
}

bool Memory::is_addr_in_instr_range(int number_of_bytes, int start_address)
{
    bool result = is_all_consecutive_n_bytes_in_range(number_of_bytes, start_address, Memory::ADDR_INSTR, Memory::ADDR_INSTR_LENGTH);
    if (!result)
        cerr << "address is not in instruction range: " << start_address << endl;
    return result;
}

bool Memory::is_addr_in_mapped_io_range(int number_of_bytes, int start_address)
{
    //encapsulates both input and output
    bool result = is_all_consecutive_n_bytes_in_range(number_of_bytes, start_address, Memory::ADDR_GETC, Memory::ADDR_GETC_LENGTH + Memory::ADDR_PUTC_LENGTH);
    if (!result)
        cerr << "address is not in mapped io range: " << start_address << endl;
    return result;
}

bool Memory::is_trying_to_read_stdin(int number_of_bytes_being_got, int start_address) //checks if any bytes being gotten are in the getc range
{
    bool result = is_any_consecutive_n_bytes_in_range(number_of_bytes_being_got, start_address, Memory::ADDR_GETC, Memory::ADDR_GETC_LENGTH);
    if (result)
        cerr << "address will trigger stdin: 0x" << start_address << endl;
    return result;
}

bool Memory::is_trying_to_set_stdout(int number_of_bytes_being_set, int start_address) //checks if any bytes being set are in the putc range
{
    bool result = is_any_consecutive_n_bytes_in_range(number_of_bytes_being_set, start_address, Memory::ADDR_PUTC, Memory::ADDR_PUTC_LENGTH);
    if (result)
        cerr << "address will trigger stdout: 0x" << start_address << endl;
    return result;
}
