#include <string> //makes vscode recognize uint32_t
#include "registers.hpp"
#include "memory.hpp"

struct Instruction_helper
{
    enum Type
    {
        r_type,
        i_type,
        j_type
    };

    struct Branch_delay
    {
        bool set_needs_branch = false;
        uint32_t address;
    };

  private:
    Registers *registers;
    Memory *memory;

  public:
    Instruction_helper(Registers *registers, Memory *memory);
    int number_of_instructions;
    Branch_delay branch_delay_helper;
    Type get_type(uint32_t instruction);
    void decode_and_execute(uint32_t instruction); //convenient to have it in the same function
};

// struct Load_delay{//don't need to do this if i don't want to
//     static bool should_delayed_load; //if true, immediately set to false once the new register was set
//     static int register_index;
//     static uint32_t register_value;
// };

struct R_type

{
    uint32_t opcode;      //6 bits
    uint32_t source1;     //5 bits
    uint32_t source2;     //5 bits
    uint32_t destination; //5 bits
    uint32_t shift;       //5 bits
    uint32_t function;    //6 bits

    R_type(uint32_t instruction, Registers *registers, Memory *memory, Instruction_helper *instruction_helper); //loads in opcode, source1, source2, etc...
    Registers *registers;
    Memory *memory;
    Instruction_helper *instruction_helper;
    void deSYTHER();

    void ADD();
    void ADDU();
    void AND();
    void DIV();
    void DIVU();
    void JALR();
    void JR();
    void MFHI();
    void MFLO();
    void MTHI();
    void MTLO();
    void MULT();
    void MULTU();
    void OR();
    void SLL();
    void SLLV();
    void SLT();
    void SLTU();
    void SRA();
    void SRAV();
    void SRL();
    void SRLV();
    void SUB();
    void SUBU();
    void XOR();
};

struct I_type

{
    uint32_t opcode;                 //6 bits
    uint32_t source1;                //5 bits
    uint32_t source2_or_destination; //5 bits
    uint32_t immediate;              //16 bits

    I_type(uint32_t instruction, Registers *registers, Memory *memory, Instruction_helper *instruction_helper);
    Registers *registers;
    Memory *memory;
    Instruction_helper *instruction_helper;
    void deSYTHER();

    void ADDI();
    void ADDIU();
    void ANDI();
    void BEQ();
    void BGEZ();
    void BGEZAL();
    void BGTZ();
    void BLEZ();
    void BLTZ();
    void BLTZAL();
    void BNE();
    void LB();
    void LBU();
    void LH();
    void LHU();
    void LUI();
    void LW();
    void LWL();
    void LWR();
    void ORI();
    void SB();
    void SH();
    void SLTI();
    void SLTIU();
    void SW();
    void XORI();

  private:
    void BRANCH(); //since all branches are the same contents
};

struct J_type

{
    uint32_t opcode;  // 6 bits
    uint32_t address; //26 bits

    J_type(uint32_t instruction, Registers *registers, Memory *memory, Instruction_helper *instruction_helper);
    Registers *registers;
    Memory *memory;
    Instruction_helper *instruction_helper;
    void deSYTHER();

    void J();
    void JAL();
};
