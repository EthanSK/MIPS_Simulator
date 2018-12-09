#include "helpers.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <cstdint>
#include "exceptions.hpp"

using namespace std;

void File_io::get_binary_file(string file_path)
{
    cerr << "getting binary file \n";
    streampos size;
    char *memblock; //dont deconstruct
    uint32_t *instructions;

    ifstream file(file_path, ios::in | ios::binary | ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        cerr << "file size: " << size << endl;
        memblock = new char[size];
        file.seekg(0, ios::beg);
        file.read(memblock, size);
        file.close();

        instructions = reinterpret_cast<uint32_t *>(memblock);
        this->number_of_instructions = size / sizeof(instructions[0]);
        cerr << "instructions: ";
        for (int i = 0; i < this->number_of_instructions; i++)
        {
            instructions[i] = Bitwise_helper::swap_bytes(instructions[i], 0, 3);
            instructions[i] = Bitwise_helper::swap_bytes(instructions[i], 1, 2);
            cerr << hex << uppercase << instructions[i] << " ";
        }
        cerr << endl;
        this->instructions = instructions;
    }
    else
    {
        cerr << "Unable to open file";
        throw Environment_error();
        //throw error
    }
}

// template <class T>
// inline T Bitwise_helper::rotate_left(T v, std::int32_t shift)
// {
//     std::size_t m = sizeof(v) * std::numeric_limits<T>::digits;
//     T s = shift >= 0 ? shift % m : -((-shift) % m);
//     return (v << s) | (v >> (m - s));
// }

// template <class T>
// inline T Bitwise_helper::rotate_right(T v, std::int32_t shift)
// {
//     std::size_t m = sizeof(v) * std::numeric_limits<T>::digits;
//     T s = shift >= 0 ? shift % m : -((-shift) % m);
//     return (v >> s) | (v << (m - s));
// }

unsigned int Bitwise_helper::swap_bits(unsigned int n, unsigned int p1, unsigned int p2)
{
    unsigned int bit1 = (n >> p1) & 1;
    unsigned int bit2 = (n >> p2) & 1;
    unsigned int x = (bit1 ^ bit2);
    x = (x << p1) | (x << p2);
    unsigned int result = n ^ x;
    return result;
}

unsigned int Bitwise_helper::swap_bytes(unsigned int n, unsigned int p1, unsigned int p2)
{
    unsigned int result = n;
    for (size_t i = 0; i < 8; i++)
    {
        result = Bitwise_helper::swap_bits(result, p1 * 8 + i, p2 * 8 + i);
    }
    return result;
}

uint32_t Bitwise_helper::extract_bits(int start_position, int size_in_bits, uint32_t value) 
{  
    uint32_t mask;
    mask = ((1 << size_in_bits) - 1) << start_position;
    uint32_t masked = value & mask; 
    return masked >> start_position;
}

uint64_t Bitwise_helper::extract_bits_64(int start_position, int size_in_bits, uint64_t value) 
{  
    uint64_t mask;
    mask = (((uint64_t)1 << (uint64_t)size_in_bits) - (uint64_t)1) << (uint64_t)start_position;
    uint64_t masked = value & mask; 
    // cerr << hex << "mask: " << mask << " value: " << value << endl;
    return masked >> start_position;
}

unsigned char Bitwise_helper::extract_char(int nth_char, uint32_t word)
{
    return extract_bits(nth_char * 8, 8, word);
}

uint32_t Bitwise_helper::set_nth_bit(int n, bool new_bit, uint32_t word)
{
    uint32_t result = (word & (~(1 << n))) | (new_bit << n);
    return result;
}

uint32_t Bitwise_helper::sign_extend_to_32(int size_in_bits, uint32_t value)
{
    uint32_t result = value;
    bool sign_bit = extract_bits(size_in_bits - 1, 1, value);
    for(size_t i = size_in_bits; i < 32; i++) 
    {
       result = set_nth_bit(i, sign_bit, result);
    }
    return result;
}

uint32_t Bitwise_helper::overwrite_bits(uint32_t original_value, uint32_t new_value, int start_position, int size_in_bits)
{
    uint32_t result = original_value;
    for(int i = 0; i < size_in_bits; i++)
    {
        bool new_bit = extract_bits(start_position + i, 1, new_value);
        result = set_nth_bit(start_position + i, new_bit, result);
    }
    return result;
}
