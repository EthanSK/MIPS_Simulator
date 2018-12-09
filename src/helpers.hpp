#include <string>
#include <cstdint>
#include <unordered_map>

#pragma once

struct File_io
{
  int number_of_instructions;
  uint32_t *instructions;

  void get_binary_file(std::string file_path);
};

struct Bitwise_helper
{
  // template <class T>
  // static inline T rotate_left(T v, std::int32_t shift);
  // template <class T>
  // static inline T rotate_right(T v, std::int32_t shift);
  static unsigned int swap_bits(unsigned int n, unsigned int p1, unsigned int p2);
  static unsigned int swap_bytes(unsigned int n, unsigned int p1, unsigned int p2);
  static uint32_t extract_bits(int start_position, int size_in_bits, uint32_t value);
  static uint64_t extract_bits_64(int start_position, int size_in_bits, uint64_t value); 
  static unsigned char extract_char(int nth_char, uint32_t word); //nth char can only be 0 8 16 or 24
  static uint32_t set_nth_bit(int n, bool new_bit, uint32_t word);
  static uint32_t sign_extend_to_32(int size_in_bits, uint32_t value);
  static uint32_t overwrite_bits(uint32_t original_value, uint32_t new_value, int start_position, int size_in_bits);
};
