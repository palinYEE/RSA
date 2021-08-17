#include<stdio.h>
#include<stdlib.h>
#include"add.h"
#include"rsa.h"

/*
input : n-bit A (a_n | ... | a_0), B (b_n | ... | b_0)
output : n+1-bit C (c_n | c_{n-1} ... | c_1 | c_0)
    1. carry <- 0
    2. for j = 0 to n-1 do
    3.      c_j <- a_j xor b_j xor carry
    4.      carry <- (carry and (a_j xor b_j)) or (a_j and b_j)
    5. end for
    6. c_n <- carry
    7. return c_n | c_{n-1} ... | c_1 | c_0
*/
void naiveAdd(unsigned char *a, unsigned char *b, unsigned char *dst, int loopNum){
    int i, j;
    int carry = 0;
    unsigned char tmp;
    unsigned char Ctmp;

    for(i=loopNum-1; i >=0; i--){
        Ctmp = 0;
        for(j=0; j<8; j++){
            tmp = ((a[i] >> j) & 0x01) ^ ((b[i] >> j) & 0x01);                      // 0 or 1
            Ctmp ^= (tmp ^ carry) << j;
            carry = (carry & tmp) | (((a[i] >> j) & 0x01) & ((b[i] >> j) & 0x01));
        }
        dst[i + 1] = Ctmp;
    }
    dst[0] = carry;  
}
