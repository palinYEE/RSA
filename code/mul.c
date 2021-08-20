#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"rsa.h"
#include"mul.h"
#include"add.h"

/*
input : n-bit A (a_n | ... | a_0), B (b_n | ... | b_0)
output : 2n-bit C (c_n | c_{n-1} ... | c_1 | c_0)
    1. for i = 0 to n-1 do
    2.      for j = 0 to 8 do
    3.          if b_j == 1 then
    4.              C = (A << j) + C
    5.          endif
    6.      endfor
    7. end for
    8. return c_2n | c_{2n-1} ... | c_1 | c_0
*/
void textBookMul(unsigned char *a, unsigned char *b, unsigned char *dst, int loopNum){
    int i, j;
    int k, h;
    unsigned char tmp;
    unsigned char *arrayTmp;
    unsigned char *addTmp;

    arrayTmp = calloc(2*loopNum, sizeof(unsigned char));
    addTmp = calloc(2*loopNum + 1, sizeof(unsigned char));

    for(i=loopNum-1; i>=0; i--){
        for(j=0; j<8; j++){
            if( ((b[i] >> j) & 0x01) == 0x01 ){
                
                // arrayTmp clear
                memset(arrayTmp, 0, 2*loopNum*sizeof(arrayTmp[0]));
                memset(addTmp, 0, (2*loopNum + 1)*sizeof(arrayTmp[0]));

                // arrayTmp setting
                for(k = loopNum-1; k >=0; k--){
                    tmp = ((a[k] & 0xff) >> (8-j));
                    arrayTmp[i + k + 1] ^= ((a[k] & 0xff) << (j));
                    arrayTmp[i + k] ^= tmp;
                }

                naiveAdd(arrayTmp, dst, addTmp, 2*loopNum);
                memcpy(dst, addTmp+1, 2*loopNum);
            }
        }
    }
}

/*  
    16-bit 로 예시
    ex. 1101 0010 1111 0101     x    0101 1001 0001 0111
        |-------| |-------|          |-------| |-------|
            a0        a1                 b0        b1
        (a02^8 + a1)x(b02^8 + b1)
                = (a0xb0)2^16 + (a0xb1 + a1b0)2^8 + (a1b1)
        여기서 (a0xb1 + a1b0)을 다음과 같이 변경 가능
            (a0xb1 + a1b0) = (a0 + a1)(b0 + b1) - a0b0 - a1b1
*/
void karatubaMul(unsigned char *a, unsigned char *b, unsigned char *dst, int loopNum){
    int i, j, l;
    unsigned char bitTmp;

}