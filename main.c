//For AES algorithm, irreducible polynomial is: x^8 + x^4 + x^3 + x +1

#include<stdio.h>
#define Nb 4 // Number of columns (32-bit words) comprising the State
#define Nr 10 // Number of rounds, for 128-bit key it's 10
#define Nk 4  // Number of 32-bit keywords 

typedef unsigned char byte;

//defining datatype for 32-bit (= 4bytes) word
typedef struct{
    byte bytes[4];
    }word;
    
#include"KEX.h"


int main() {
    byte key[4 * Nk] = {0x2b, 0x7e, 0x15, 0x16,
        		0x28, 0xae, 0xd2, 0xa6,
        		0xab, 0xf7, 0x15, 0x88,
        		0x09, 0xcf, 0x4f, 0x3c};

    word w[Nb * (Nr + 1)];
    KeyExpansion(key, w);

    // Print expanded keys for testing
    for (int i = 0; i < Nb * (Nr + 1); i++) {
        printf("w[%d] = %02hhx%02hhx%02hhx%02hhx\n", i, w[i].bytes[0], w[i].bytes[1], w[i].bytes[2], w[i].bytes[3]);
    }

    return 0;
}
