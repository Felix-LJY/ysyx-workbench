#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t PC = 0;
uint8_t R[4];
uint8_t M[16]={0x8a,0x90,0xa0,0xb1,0x17,0x29,0xd1,0x60,0xe3,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

inline void inst_cycle();

void inst_cycle()
{
    uint8_t inst = M[PC++];
    switch ((inst>>6)&0b11)
    {
    case 0b00:
        R[(inst>>4)&0b11] = R[(inst>>2)&0b11]+R[(inst>>0)&0b11];
        break;
    case 0b01:
        printf("R[%d] = %d\n", (inst>>4)&0b11, R[(inst>>4)&0b11]);
        break;
    case 0b10:
        R[(inst>>4)&0b11] = inst&0b1111;
        break;
    case 0b11:
        if(R[0]!=R[(inst>>0)&0b11]) PC = (inst>>2)&0b1111;
        break;
    default:
        printf("Unknown instruction: 0x%02x\n", inst);
        break;
    }
}

int main(int argc, char *argv[])
{
    uint8_t last_PC = 0xFF;

    if(argc!=2)
    {
        printf("Usage: %s <input>\n", argv[0]);
        return 1;
    }

    M[0] = 0x80|((uint8_t)atoi(argv[1])&0b1111);

    while (PC!=last_PC)
    {
        last_PC = PC;
        inst_cycle();
    }

    return 0;
}
