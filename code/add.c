#include<stdio.h>
#include<stdlib.h>
#include"add.h"
#include"rsa.h"
// 
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
// 128bit -> unsigned char 배열 기준 16개의 원소가 필요 
// n bit -> unsigned char 배열 기준 n/8 개의 원소가 필요
// 주의점 : n % 16 == 0 --> n/8개의 배열 필요 
//        n % 16 != 0 --> n/8 + 1 개의 배열 필요  
void naiveAdd(unsigned char *a, unsigned char *b, unsigned char *dst){
    int i, j;
    int loopNum;
    int carry = 0;
    unsigned char tmp;
    unsigned char Ctmp;

    if(BIT_SIZE%8 == 0){
        loopNum = BIT_SIZE/8;
    }
    else{
        loopNum =  BIT_SIZE/8 + 1;
    }

    dst = calloc(loopNum + 1, sizeof(unsigned char));

    for(i=0; i<loopNum; i++){
        Ctmp = 0;
        for(j=0; j<8; j++){
            tmp = ((a[i] >> i) & 0x01) ^ ((b[i] >> i) & 0x01);
            Ctmp ^= (tmp ^ carry) << i;
            carry = (carry & tmp) | (((a[i] >> i) & 0x01) & ((b[i] >> i) & 0x01));
        }
        dst[i] = Ctmp;
    }
    dst[loopNum] = carry; 
}
