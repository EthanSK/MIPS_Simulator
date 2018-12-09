#include "instructions.hpp"
#include "helpers.hpp"
#include "registers.hpp"
#include "memory.hpp"
#include "exceptions.hpp"
#include <iostream>

using namespace std;

Instruction_helper::Instruction_helper(Registers *registers, Memory *memory)
{
	this->registers = registers;
	this->memory = memory;
	this->branch_delay_helper = Branch_delay();
}

R_type::R_type(uint32_t instruction, Registers *registers, Memory *memory, Instruction_helper *instruction_helper)
{
	opcode = Bitwise_helper::extract_bits(26, 6, instruction);
	// cerr << "extracted op code " << dec << opcode << endl;
	source1 = Bitwise_helper::extract_bits(21, 5, instruction);
	source2 = Bitwise_helper::extract_bits(16, 5, instruction);
	destination = Bitwise_helper::extract_bits(11, 5, instruction);
	shift = Bitwise_helper::extract_bits(6, 5, instruction);
	function = Bitwise_helper::extract_bits(0, 6, instruction);
	this->registers = registers;
	this->memory = memory;
	this->instruction_helper = instruction_helper;
}

I_type::I_type(uint32_t instruction, Registers *registers, Memory *memory, Instruction_helper *instruction_helper)
{
	opcode = Bitwise_helper::extract_bits(26, 6, instruction);
	// cerr << "extracted op code " << dec << opcode << endl;
	source1 = Bitwise_helper::extract_bits(21, 5, instruction);
	source2_or_destination = Bitwise_helper::extract_bits(16, 5, instruction);
	immediate = Bitwise_helper::extract_bits(0, 16, instruction);
	this->registers = registers;
	this->memory = memory;
	this->instruction_helper = instruction_helper;
}

J_type::J_type(uint32_t instruction, Registers *registers, Memory *memory, Instruction_helper *instruction_helper)
{
	opcode = Bitwise_helper::extract_bits(26, 6, instruction);
	address = Bitwise_helper::extract_bits(0, 26, instruction);
	this->registers = registers;
	this->memory = memory;
	this->instruction_helper = instruction_helper;
}

Instruction_helper::Type Instruction_helper::get_type(uint32_t instruction)
{
	uint32_t opcode = Bitwise_helper::extract_bits(26, 6, instruction);
	if (opcode == 0)
	{
		return r_type;
	}
	if (opcode == 2 || opcode == 3)
	{
		return j_type;
	}

	return i_type; //if not r_type or j_type, must be i_type
}

void R_type::deSYTHER()
{
	switch (function)
	{
	case 0:
		SLL();
		break;
	case 2:
		SRL();
		break;
	case 3:
		SRA();
		break;
	case 4:
		SLLV();
		break;
	case 6:
		SRLV();
		break;
	case 7:
		SRAV();
		break;
	case 8:
		JR();
		break;
	case 9:
		JALR();
		break;
	case 16:
		MFHI();
		break;
	case 17:
		MTHI();
		break;
	case 18:
		MFLO();
		break;
	case 19:
		MTLO();
		break;
	case 24:
		MULT();
		break;
	case 25:
		MULTU();
		break;
	case 26:
		DIV();
		break;
	case 27:
		DIVU();
		break;
	case 32:
		ADD();
		break;
	case 33:
		ADDU();
		break;
	case 34:
		SUB();
		break;
	case 35:
		SUBU();
		break;
	case 36:
		AND();
		break;
	case 37:
		OR();
		break;
	case 38:
		XOR();
		break;
	case 42:
		SLT();
		break;
	case 43:
		SLTU();
		break;
	default:
		throw Invalid_instruction_exception();
		break;
	}
}

void I_type::deSYTHER()
{
	switch (opcode)
	{
	case 1:
		switch (source2_or_destination)
		{
		case 0:
			BLTZ();
			break;
		case 1:
			BGEZ();
			break;
		case 16:
			BLTZAL();
			break;
		case 17:
			BGEZAL();
			break;
		default:
			break;
		}
		break;
	case 4:
		BEQ();
		break;
	case 5:
		BNE();
		break;
	case 6:
		BLEZ();
		break;
	case 7:
		BGTZ();
		break;
	case 8:
		ADDI();
		break;
	case 9:
		ADDIU();
		break;
	case 10:
		SLTI();
		break;
	case 11:
		SLTIU();
		break;
	case 12:
		ANDI();
		break;
	case 13:
		ORI();
		break;
	case 14:
		XORI();
		break;
	case 15:
		LUI();
		break;
	case 32:
		LB();
		break;
	case 33:
		LH();
		break;
	case 34:
		LWL();
		break;
	case 35:
		LW();
		break;
	case 36:
		LBU();
		break;
	case 37:
		LHU();
		break;
	case 38:
		LWR();
		break;
	case 40:
		SB();
		break;
	case 41:
		SH();
		break;
	case 43:
		SW();
		break;
	default:
		throw Invalid_instruction_exception();
		break;
	}
}

void J_type::deSYTHER()
{
	switch (opcode)
	{
	case 2:
		J();
		break;
	case 3:
		JAL();
		break;

	default:
		throw Invalid_instruction_exception(); //instruction not found
		break;
	}
}

void Instruction_helper::decode_and_execute(uint32_t instruction)
{
	// cerr << hex <<"pc value: " << registers->get_program_counter() << endl;
	// cerr << "cond : " << Memory::ADDR_INSTR + (uint32_t)number_of_instructions * 4 << endl;
	uint32_t current_instruction_program_counter = registers->get_program_counter();

	cerr << "executing instruction: " << hex << instruction << " at address: 0x" << current_instruction_program_counter << endl;

	//bool should_perform_delayed_load_after_execution = Load_delay::should_delayed_load; //determine before, execute after. commented out because it is apparently undefined behaviour and is up to me how to implement it

	if (branch_delay_helper.set_needs_branch)
	{
		registers->set_program_counter(branch_delay_helper.address);
		branch_delay_helper.set_needs_branch = false;
	}
	else
	{
		registers->advance_program_counter(); //technically happens after decode (deSYTHER), but same thing in this case, just much more clean in code. its he same thing because the decode no longer requries the programme counter from this point on as we have the next instruction.
	}
	// cerr << hex <<"pc of currently executing instruction: " << current_instruction_program_counter << " no instrr: "  << dec<< number_of_instructions <<  endl;

	//this is meant to be down here, because jr to 0 will only acc happen in the branch delay slot, and the instruction in the delay slot doesn't exist as the jr was the last one, so it would otherwise throw an error before having the chnace to set the correct next address and detect end of program
	if (current_instruction_program_counter >= Memory::ADDR_INSTR + ((uint32_t)number_of_instructions + 1) * 4 || current_instruction_program_counter < Memory::ADDR_INSTR) //if the CURRENT instruction address is out of range
	//we want it to allow one extra instruction after the last one to simulate the delay instruction. very important to let jr work for the termination. if the last instr is jr 0, it still needs to execute the delay slot, so it essentially inserts a nop (in this sim) and then terminates, so we gotta assume there is +1 instruction
	{
		throw Memory_exception(); //this is the exception that would happen if it went through all the 0s (nops) and hit the end and threw memeory exception out of range
	}

	switch (get_type(instruction))
	{
	case r_type:
	{
		// cerr << "is r type " << endl;
		R_type r_instruction = R_type(instruction, registers, memory, this);
		r_instruction.deSYTHER();
		break;
	}
	case i_type:
	{
		//cerr << "is i type" << endl;
		I_type i_instruction = I_type(instruction, registers, memory, this);
		i_instruction.deSYTHER();
		break;
	}
	case j_type:
	{
		J_type j_instruction = J_type(instruction, registers, memory, this);
		j_instruction.deSYTHER();
		break;
	}
	}

	if (registers->get_program_counter() == Memory::ADDR_NULL) //if the NEXT instruction address is 0x000...
	{
		throw End_of_program();
	}
}

void R_type::ADD() //check to see if this is correct - what if we used negative 2s complement? will that even make a difference
{
	//we need to check for overflow
	//cerr << hex << "source1: " << registers->get_register(source1) << " source2: " << registers->get_register(source2) << endl;
	int result = registers->get_register(source1) + registers->get_register(source2); // trunc to 32 bits

	bool overflow_condition_1 = (registers->get_register(source1) < 0 && registers->get_register(source2) < 0 && result >= 0);
	bool overflow_condition_2 = (registers->get_register(source1) > 0 && registers->get_register(source2) > 0 && result <= 0);
	//overflow can't physically happen if both sources have different signs to each other
	// cerr << "result: " << result << endl;

	if (overflow_condition_1 || overflow_condition_2)
	{
		throw Arithmetic_exception();
	}
	registers->set_register(destination, result);
}

void R_type::ADDU()
{
	int result = registers->get_register(source1) + registers->get_register(source2);
	registers->set_register(destination, result);
}
void R_type::AND()
{
	int result = registers->get_register(source1) & registers->get_register(source2);
	registers->set_register(destination, result);
}
void R_type::DIV()
{
	int dividend = registers->get_register(source1);
	int divisor = registers->get_register(source2);
	int quotient_result = 0;
	int remainder_result = 0;
	if (divisor != 0)
	{
		quotient_result = dividend / divisor;
		remainder_result = dividend % divisor;
	}
	int lo = quotient_result;
	int hi = remainder_result;
	registers->set_lo(lo);
	registers->set_hi(hi);
	cerr << hex << "divu lo: 0x" << lo << endl;
	cerr << hex << "divu hi: 0x" << hi << endl;
}
void R_type::DIVU()
{
	uint32_t dividend = registers->get_register(source1);
	uint32_t divisor = registers->get_register(source2);
	uint32_t quotient_result = 0;
	uint32_t remainder_result = 0;
	if (divisor != 0)
	{
		quotient_result = dividend / divisor;
		remainder_result = dividend % divisor;
	}
	uint32_t lo = quotient_result;
	uint32_t hi = remainder_result;
	registers->set_lo(lo);
	registers->set_hi(hi);
	cerr << hex << "div lo: 0x" << lo << endl;
	cerr << hex << "div hi: 0x" << hi << endl;
}
void R_type::JALR() //has delay slot
{
	int jump_address = registers->get_register(source1);
	cerr << "jump address: 0x" << jump_address << endl;
	if (Bitwise_helper::extract_bits(0, 2, jump_address) != 0)
	{
		throw Address_exception();
	}
	instruction_helper->branch_delay_helper.set_needs_branch = true;
	instruction_helper->branch_delay_helper.address = jump_address;

	uint32_t link_address = registers->get_program_counter() + 4;
	registers->set_register(destination, link_address);
}

void R_type::JR() //has delay slot
{
	int jump_address = registers->get_register(source1); //ensure we store the correct address before executing delay slot (as it could change the value of address source1)
	// uint32_t next_instruction_address = registers->get_program_counter();

	if (Bitwise_helper::extract_bits(0, 2, jump_address) != 0)
	{
		throw Address_exception();
	}
	cerr << "jr address: 0x" << jump_address << endl;
	instruction_helper->branch_delay_helper.set_needs_branch = true;
	instruction_helper->branch_delay_helper.address = jump_address;
	//cerr << "jr needs branch: " << instruction_helper->branch_delay_helper.set_needs_branch << endl;
	// int32_t next_instruction = memory->get_instruction(next_instruction_address);
	// instruction_helper->decode_and_execute(next_instruction);

	// registers->set_program_counter(jump_address);
}
void R_type::MFHI()
{
	registers->set_register(destination, registers->get_hi());
	cerr << hex << "new register from hi at 0x" << destination << ": " << registers->get_hi() << endl;
}
void R_type::MFLO()
{
	registers->set_register(destination, registers->get_lo());
	cerr << hex << "new register from low at 0x" << destination << ": " << registers->get_lo() << endl;
}
void R_type::MTHI()
{
	registers->set_hi(registers->get_register(source1));
}
void R_type::MTLO()
{
	registers->set_lo(registers->get_register(source1));
}
void R_type::MULT()
{
	int64_t result_64 = (int64_t)registers->get_register(source1) * (int64_t)registers->get_register(source2);
	int lo = Bitwise_helper::extract_bits_64(0, 32, result_64);
	int hi = Bitwise_helper::extract_bits_64(32, 32, result_64);
	cerr << hex << "result 64: 0x" << result_64 << endl;
	registers->set_lo(lo);
	registers->set_hi(hi);
	cerr << hex << "mult lo: 0x" << lo << endl;
	cerr << hex << "mult hi: 0x" << hi << endl;
}
void R_type::MULTU()
{
	uint64_t result_64 = (uint64_t)(uint32_t)registers->get_register(source1) * (uint64_t)(uint32_t)registers->get_register(source2);
	cerr << "multu'ing these numbers: " << dec << (uint64_t)(uint32_t)registers->get_register(source1) << " and " << (uint64_t)(uint32_t)registers->get_register(source2) << endl;
	int lo = Bitwise_helper::extract_bits_64(0, 32, result_64);
	int hi = Bitwise_helper::extract_bits_64(32, 32, result_64);
	cerr << hex << "result 64: 0x" << result_64 << endl;
	registers->set_lo(lo);
	registers->set_hi(hi);
	cerr << hex << "mult lo: 0x" << lo << endl;
	cerr << hex << "mult hi: 0x" << hi << endl;
}
void R_type::OR()
{
	int result = registers->get_register(source1) | registers->get_register(source2);
	registers->set_register(destination, result);
}
void R_type::SLL()
{
	int result = (uint32_t)registers->get_register(source2) << shift;
	registers->set_register(destination, result);
}
void R_type::SLLV()
{
	int result = (uint32_t)registers->get_register(source2) << Bitwise_helper::extract_bits(0, 5, registers->get_register(source1));
	registers->set_register(destination, result);
}
void R_type::SLT()
{
	int result = (registers->get_register(source1) < registers->get_register(source2));
	registers->set_register(destination, result);
}
void R_type::SLTU()
{
	bool result = ((uint32_t)registers->get_register(source1) < (uint32_t)registers->get_register(source2));
	registers->set_register(destination, result);
}
void R_type::SRA()
{
	uint32_t unsigned_result = registers->get_register(source2) >> shift;
	int result = Bitwise_helper::sign_extend_to_32(32 - shift, unsigned_result); //max shift is 31 bits (2^5 -1)
	registers->set_register(destination, result);
}
void R_type::SRAV()
{
	uint32_t unsigned_result = registers->get_register(source2) >> Bitwise_helper::extract_bits(0, 5, registers->get_register(source1));
	int result = Bitwise_helper::sign_extend_to_32(32 - shift, unsigned_result); //max shift is 31 bits (2^5 -1)
	registers->set_register(destination, result);
}
void R_type::SRL()
{
	int result = (uint32_t)registers->get_register(source2) >> shift;
	registers->set_register(destination, result);
}
void R_type::SRLV()
{
	int result = (uint32_t)registers->get_register(source2) >> Bitwise_helper::extract_bits(0, 5, registers->get_register(source1));
	registers->set_register(destination, result);
}
void R_type::SUB()
{
	int result = registers->get_register(source1) - registers->get_register(source2);		   // trunc to 32 bits
	if ((result < registers->get_register(source1)) != (registers->get_register(source2) > 0)) //got this method of checking for overflow from some dude on stack overflow
	{
		throw Arithmetic_exception();
	}
	registers->set_register(destination, result);
}
void R_type::SUBU()
{
	int result = registers->get_register(source1) - registers->get_register(source2); // trunc to 32 bits
	registers->set_register(destination, result);
}
void R_type::XOR()
{
	int result = registers->get_register(source1) ^ registers->get_register(source2);
	registers->set_register(destination, result);
}

void I_type::ADDI()
{
	// cerr << hex << "source1: " << registers->get_register(source1) << " source2: " << Bitwise_helper::sign_extend_to_32(16, immediate) << endl;
	int signed_immediate = Bitwise_helper::sign_extend_to_32(16, immediate);
	int result = registers->get_register(source1) + signed_immediate; // trunc to 32 bits
	bool overflow_condition_1 = (registers->get_register(source1) < 0 && signed_immediate < 0 && result >= 0);
	bool overflow_condition_2 = (registers->get_register(source1) > 0 && signed_immediate > 0 && result <= 0);
	//overflow can't physically happen if both sources have different signs to each other
	cerr << hex<< "addi result: 0x" << result << " source1: " << registers->get_register(source1) << " signed immediate: 0x" << signed_immediate << endl;

	if (overflow_condition_1 || overflow_condition_2)
	{
		throw Arithmetic_exception();
	}
	registers->set_register(source2_or_destination, result);
}
void I_type::ADDIU()
{
	int result = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	registers->set_register(source2_or_destination, result);
}
void I_type::ANDI()
{
	int result = registers->get_register(source1) & immediate;
	cerr << "andi result: " << result << endl;
	registers->set_register(source2_or_destination, result);
}

void I_type::BRANCH()
{
	int offset = Bitwise_helper::sign_extend_to_32(18, immediate << 2);
	uint32_t branch_address = registers->get_program_counter() + offset; //ensure we store the correct address before executing delay slot
	cerr << "branch address: " << branch_address << ", program counter: " << registers->get_program_counter() << ", immediate: " << immediate << " offset: " << offset << hex << " source1 reg: " << registers->get_register(source1) << " source2 reg: " << registers->get_register(source2_or_destination) << endl;

	instruction_helper->branch_delay_helper.set_needs_branch = true;
	instruction_helper->branch_delay_helper.address = branch_address;
}

void I_type::BEQ() //has delay slot
{
	if (registers->get_register(source1) == registers->get_register(source2_or_destination))
	{
		BRANCH();
	}
}
void I_type::BGEZ() //has delay slot
{
	if (registers->get_register(source1) >= 0)
	{
		BRANCH();
	}
}
void I_type::BGEZAL() //has delay slot
{
	if (registers->get_register(source1) >= 0)
	{
		BRANCH();
	}
	uint32_t link_address = registers->get_program_counter() + 4;
	cerr << hex << "branch and link set link reg to: 0x" << link_address << endl;
	registers->set_register(31, link_address); //apparently this is done regardless of if the condition was met
}
void I_type::BGTZ() //has delay slot
{
	if (registers->get_register(source1) > 0)
	{
		BRANCH();
	}
}
void I_type::BLEZ() //has delay slot
{
	if (registers->get_register(source1) <= 0)
	{
		BRANCH();
	}
}
void I_type::BLTZ() //has delay slot
{
	if (registers->get_register(source1) < 0)
	{
		BRANCH();
	}
}
void I_type::BLTZAL() //has delay slot
{
	if (registers->get_register(source1) < 0)
	{
		BRANCH();
	}
	registers->set_register(31, registers->get_program_counter() + 4); //apparently this is done regardless of if the condition was met
}
void I_type::BNE() //has delay slot
{
	if (registers->get_register(source1) != registers->get_register(source2_or_destination))
	{
		BRANCH();
	}
}
void I_type::LB()
{
	int address = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	int result = Bitwise_helper::sign_extend_to_32(8, memory->get_n_bytes_of_data(1, address));
	cerr << hex << "loaded byte at 0x" << address << ": " << result << endl;
	registers->set_register(source2_or_destination, result);
}
void I_type::LBU()
{
	int address = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	int result = Bitwise_helper::extract_bits(0, 8, memory->get_n_bytes_of_data(1, address));
	cerr << hex << "loaded byte unsigned at 0x" << address << ": " << result << endl;
	registers->set_register(source2_or_destination, result);
}
void I_type::LH()
{
	int address = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	if (Bitwise_helper::extract_bits(0, 1, address) != 0)
	{
		throw Address_exception();
	}
	int result = Bitwise_helper::sign_extend_to_32(16, memory->get_n_bytes_of_data(2, address));
	cerr << hex << "loading halfword at 0x" << address << ": " << result << endl;
	registers->set_register(source2_or_destination, result);
}

void I_type::LHU()
{
	int address = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	if (Bitwise_helper::extract_bits(0, 1, address) != 0)
	{
		throw Address_exception();
	}
	int result = Bitwise_helper::extract_bits(0, 16, memory->get_n_bytes_of_data(2, address));
	cerr << hex << "loading halfword unsigned at 0x" << address << ": " << result << endl;
	registers->set_register(source2_or_destination, result);
}
void I_type::LUI()
{
	int result = immediate << 16;
	cerr << hex << "lui result: 0x" << result << endl;
	registers->set_register(source2_or_destination, result);
}
void I_type::LW()
{
	int address = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	if (Bitwise_helper::extract_bits(0, 2, address) != 0)
	{
		throw Address_exception();
	}
	int result = memory->get_n_bytes_of_data(4, address);
	cerr << hex << "loading word at 0x" << address << ": " << result << endl;
	registers->set_register(source2_or_destination, result);
	// Load_delay::should_delayed_load = true;
	// Load_delay::register_index = source2_or_destination;
	// Load_delay::register_value = memory->get_n_bytes_of_data(4, address);
}
void I_type::LWL()
{
	int address = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	int next_aligned_address = address;
	next_aligned_address = address + (4 - (address % 4));

	int number_of_bytes_to_get = next_aligned_address - address;
	int existing_reg_value = registers->get_register(source2_or_destination);
	int shift_amount = (8 * (4 - number_of_bytes_to_get));
	int data = memory->get_n_bytes_of_data(number_of_bytes_to_get, address) << shift_amount;
	int result = Bitwise_helper::overwrite_bits(existing_reg_value, data, shift_amount, number_of_bytes_to_get * 8);
	cerr << "lwl result: 0x" << hex << result << " nearest aligned address: 0x" << next_aligned_address << endl;
	registers->set_register(source2_or_destination, result);
}
void I_type::LWR()
{
	int address = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	int nearest_aligned_address = address;
	if ((nearest_aligned_address % 4) != 0)
	{ //if not already a multiple of 4
		nearest_aligned_address = address - (address % 4);
	}
	int number_of_bytes_to_get = (address - nearest_aligned_address) + 1;
	int existing_reg_value = registers->get_register(source2_or_destination);
	int shift_amount = 0; //for consistency
	int data = memory->get_n_bytes_of_data(number_of_bytes_to_get, nearest_aligned_address) << shift_amount;
	int result = Bitwise_helper::overwrite_bits(existing_reg_value, data, shift_amount, number_of_bytes_to_get * 8);
	cerr << "lwr result: 0x" << hex << result << " nearest aligned address: 0x" << nearest_aligned_address << endl;
	registers->set_register(source2_or_destination, result);
}
void I_type::ORI()
{
	int result = registers->get_register(source1) | immediate;
	cerr << "ori result: " << result << endl;
	registers->set_register(source2_or_destination, result);
}
void I_type::SB()
{
	int address = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	cerr << hex << "store byte address: " << address << " immediate: " << immediate << " source 1: " << source1 << endl;
	memory->set_n_bytes_of_data(1, address, Bitwise_helper::extract_bits(0, 8, registers->get_register(source2_or_destination)));
}
void I_type::SH()
{
	int address = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	cerr << hex << "store halfword address: " << address << endl;
	if (Bitwise_helper::extract_bits(0, 1, address) != 0)
	{
		throw Address_exception();
	}
	memory->set_n_bytes_of_data(2, address, Bitwise_helper::extract_bits(0, 16, registers->get_register(source2_or_destination)));
}
void I_type::SLTI()
{
	bool result = (registers->get_register(source1) < (int)Bitwise_helper::sign_extend_to_32(16, immediate));
	registers->set_register(source2_or_destination, result);
}
void I_type::SLTIU()
{
	bool result = ((uint32_t)registers->get_register(source1) < (uint32_t)Bitwise_helper::sign_extend_to_32(16, immediate));
	registers->set_register(source2_or_destination, result);
}
void I_type::SW()
{
	int address = registers->get_register(source1) + Bitwise_helper::sign_extend_to_32(16, immediate);
	cerr << hex << "store word address: 0x" << address << endl;
	if (Bitwise_helper::extract_bits(0, 2, address) != 0)
	{
		throw Address_exception();
	}
	memory->set_n_bytes_of_data(4, address, registers->get_register(source2_or_destination));
}
void I_type::XORI()
{
	int result = registers->get_register(source1) ^ immediate;
	registers->set_register(source2_or_destination, result);
}

void J_type::J() //has delay slot
{
	int jump_address = address << 2;
	cerr << "instr_index: 0x" << address << endl;

	for (size_t i = 28; i < 32; i++)
	{
		jump_address = Bitwise_helper::set_nth_bit(i, Bitwise_helper::extract_bits(i, 1, registers->get_program_counter()), jump_address);
	}
	cerr << "jump address: 0x" << jump_address << endl;

	instruction_helper->branch_delay_helper.set_needs_branch = true;
	instruction_helper->branch_delay_helper.address = jump_address;
}
void J_type::JAL() //has delay slot
{
	int jump_address = address << 2;

	for (size_t i = 28; i < 32; i++)
	{
		jump_address = Bitwise_helper::set_nth_bit(i, Bitwise_helper::extract_bits(i, 1, registers->get_program_counter()), jump_address);
	}
	cerr << "jump address: 0x" << jump_address << endl;

	instruction_helper->branch_delay_helper.set_needs_branch = true;
	instruction_helper->branch_delay_helper.address = jump_address;
	uint32_t link_address = registers->get_program_counter() + 4;
	registers->set_register(31, link_address);
}
