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

int main()
{
    return 0;
}
