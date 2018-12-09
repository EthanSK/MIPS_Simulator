#include <vector>
#include "helpers.hpp"
#include <unordered_map>

#pragma once

class Memory
{
  std::unordered_map<int, unsigned char> memory;

private:
  void set_address(int address, unsigned char data); //these should be implemented using set n bytes and get n bytes so it correctly does the putchar and getchar once
  unsigned char get_address(int address);
  uint32_t get_n_bytes(int n, int start_address);
  void set_n_bytes(int n, int start_address, uint32_t value);
  bool is_all_consecutive_n_bytes_in_range(int n, int start_address, int start_of_range, int length_of_range); 
  bool is_any_consecutive_n_bytes_in_range(int n, int start_address, int start_of_range, int length_of_range); 


public:
  static const int ADDR_NULL = 0x00000000;
  static const int ADDR_NULL_LENGTH = 0x4;
  static const int ADDR_INSTR = 0x10000000;
  static const int ADDR_INSTR_LENGTH = 0x1000000;
  static const int ADDR_DATA = 0x20000000;
  static const int ADDR_DATA_LENGTH = 0x4000000;
  static const int ADDR_GETC = 0x30000000;
  static const int ADDR_GETC_LENGTH = 0x4;
  static const int ADDR_PUTC = 0x30000004;
  static const int ADDR_PUTC_LENGTH = 0x4;

public:
  Memory();
  //no get word function because lw is a command, so is lh and lb etc
  void set_instructions(uint32_t *instructions, int number_of_instructions);
  uint32_t get_instruction(int address); //separate func so we can throw exceptions properly

  //specifically for addr_data range
  void set_n_bytes_of_data(int n, int start_address, uint32_t value);
  uint32_t get_n_bytes_of_data(int n, int start_address);

  bool is_addr_in_data_write_range(int number_of_bytes, int start_address);
  bool is_addr_in_data_read_range(int number_of_bytes, int start_address);
  bool is_addr_in_instr_range(int number_of_bytes, int start_address);
  bool is_addr_in_mapped_io_range(int number_of_bytes, int start_address);


  bool is_trying_to_read_stdin(int number_of_bytes_being_got, int start_address);  //tryna read user input
  bool is_trying_to_set_stdout(int number_of_bytes_being_set, int start_address); //tryna read user output
};