#include <stdio.h>
#include <stdint.h>

#define MEMORY_MAX (1 << 16)
uint16_t memory[MEMORY_MAX];

typedef enum
{
    R_R0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC,
    R_COND,
    R_COUNT
} reg_name_t;

uint16_t reg[R_COUNT];

typedef enum
{
    FL_POS = (1 << 0),
    FL_ZRO = (1 << 1),
    FL_NEG = (1 << 2),
} cond_flag_t;

enum
{
    PC_START = 0x3000
};

typedef enum
{
    OP_BR,
    OP_ADD,
    OP_LD,
    OP_ST,
    OP_JSR,
    OP_AND,
    OP_LDR,
    OP_STR,
    OP_RTI,
    OP_NOT,
    OP_LDI,
    OP_STI,
    OP_JMP,
    OP_RES,
    OP_LEA,
    OP_TRAP
} opcode_t;

uint16_t sign_extend(uint16_t x, int bit_count)
{
    uint16_t msb_bit = (x >> (bit_count - 1)) & 0x1;
    if (msb_bit == 0)
        return x;
    else
    {
        return (0xffff << bit_count) | x;
    }
}

void update_flags(uint16_t r)
{
    if (reg[r] == 0x0)
    {
        reg[R_COND] = FL_ZRO;
    }
    else if ((reg[r] >> 15) == 1)
    {
        reg[R_COND] = FL_NEG;
    }
    else
        reg[R_COND] = FL_POS;
}
int main()

{

    reg[R_COND] = FL_ZRO;
    reg[R_PC] = PC_START;
    int running = 1;
    while (running)
    {
        uint16_t instr = memory[reg[R_PC]];
        reg[R_PC]++;
        uint16_t op = instr >> 12;
        switch (op)
        {
        case OP_BR:
        {
            uint16_t cond_flag = (instr >> 9) & 0x7;
            uint16_t pc_offset = sign_extend((instr & 0x1ff), 9);
            if ((reg[R_COND] & cond_flag) != 0)
            {
                reg[R_PC] += pc_offset;
            }
        }

        break;
        case OP_ADD:
        {
            uint16_t r0 = (instr >> 9) & 0x7;
            uint16_t r1 = (instr >> 6) & 0x7;
            uint16_t imm_flag = (instr >> 5) & 0x1;
            if (imm_flag == 1)
            {
                uint16_t imm5 = instr & 0x1f;
                uint16_t value = sign_extend(imm5, 5);
                reg[r0] = reg[r1] + value;
            }
            else
            {
                uint16_t r2 = instr & 0x7;
                reg[r0] = reg[r1] + reg[r2];
            }
            update_flags(r0);
        }
        break;
        case OP_LD:
            break;
        case OP_ST:
            break;
        case OP_JSR:
        {
            reg[R_R7] = reg[R_PC];
            uint16_t long_flag = (instr >> 11) & 0x1;
            if (long_flag)
            {
                uint16_t PCoffset11 = sign_extend((instr) & 0x7ff, 11);
                reg[R_PC] += PCoffset11;
            }
            else
            {
                uint16_t BaseR = (instr >> 6) & 0x7;
                reg[R_PC] = reg[BaseR];
            }
        }
        break;
        case OP_AND:
        {
            uint16_t r0 = (instr >> 9) & 0x7;
            uint16_t r1 = (instr >> 6) & 0x7;
            uint16_t imm_flag = (instr >> 5) & 0x1;
            if (imm_flag == 1)
            {
                uint16_t imm5 = instr & 0x1f;
                uint16_t value = sign_extend(imm5, 5);
                reg[r0] = reg[r1] & value;
            }
            else
            {
                uint16_t r2 = instr & 0x7;
                reg[r0] = reg[r1] & reg[r2];
            }
            update_flags(r0);
        }
        break;
        case OP_LDR:
            break;
        case OP_STR:
            break;
        case OP_NOT:
        {
            uint16_t r0 = (instr >> 9) & 0x7;
            uint16_t r1 = (instr >> 6) & 0x7;
            reg[r0] = ~(reg[r1]);
            update_flags(r0);
        }
        break;
        case OP_LDI:
            break;
        case OP_JMP:
        {
            uint16_t baseR = (instr >> 6) & 0x7;
            reg[R_PC] = reg[baseR];
        }
        break;
        case OP_LEA:
            break;
        case OP_STI:
            break;
        case OP_TRAP:
            break;
        case OP_RTI:
        case OP_RES:
        default:
            running = 0;
            break;
        }
    }

    return 0;
}
