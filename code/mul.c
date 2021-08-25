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

    memset(dst, 0, 2*loopNum);

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
    free(arrayTmp);
    free(addTmp);
}

/*  
    16-bit 로 예시
    ex. 1101 0010 1111 0101     x    0101 1001 0001 0111
        |-------| |-------|          |-------| |-------|
            a0        a1                 b0        b1
        (a02^8 + a1)x(b02^8 + b1)
                = (a0b0)2^16 + (a0xb1 + a1b0)2^8 + (a1b1)
        여기서 (a0xb1 + a1b0)을 다음과 같이 변경 가능
            (a0b1 + a1b0) = (a0 + a1)(b0 + b1) - a0b0 - a1b1
        정리하면 다음과 같은 행태로 되어있다. 
            (a0b0)2^16 + {(a0 + a1)(b0 + b1) - a0b0 - a1b1}2^8 + (a1b1)
        우리는 비트 단위의 계산을 원하기에 a0b0와 a1b1를 카라츄바 곱셈으로 구해야 한다. 
        a0b0           1101 0010   x   0101 1001
                       |--| |--|       |--| |--|
                        a'0  a'1       b'0   b'1
        (a'02^4 + a'1) x (b'02^4 + b'1)
        -> (a'0b'0)2^8 + {(a'0 + a'1)(b'0 + b'1) - a'0b'0 - a'1b'1}2^4 + (a'1b'1)
    위와 같은 과정을 재귀적으로 코딩을 하면 될 것 같다. 
    주의. loopNum은 len(a*b) 이다. 
*/
void karatsubaMul(unsigned char *a, unsigned char *b, unsigned char *dst, int loopNum){
    int i, j, k;
    
    unsigned char *a0b0;
    unsigned char *a1b1;
    unsigned char *a0a1;
    unsigned char *b0b1;

    a0b0 = calloc(loopNum/2, sizeof(unsigned char));
    a1b1 = calloc(loopNum/2, sizeof(unsigned char));
    a0a1 = calloc(loopNum/4 + 1, sizeof(unsigned char));
    b0b1 = calloc(loopNum/4 + 1, sizeof(unsigned char));

    if (){
        
    }
    else{
        unsigned char *tmpA;
        unsigned char *tmpB;

        tmpA = calloc(loopNum/4, sizeof(unsigned char));
        tmpB = calloc(loopNum/4, sizeof(unsigned char));

        memcpy(tmpA, a + loopNum/4, loopNum/4);
        memcpy(tmpB, b + loopNum/4, loopNum/4);

        karatsubaMul(tmpA, tmpB, a0b0, loopNum/2);

        memset(tmpA, 0, (loopNum/4)*sizeof(tmpA[0]));
        memset(tmpB, 0, (loopNum/4)*sizeof(tmpB[0]));
        memcpy(tmpA, a, loopNum/4);
        memcpy(tmpB, b, loopNum/4);

        karatsubaMul(tmpA, tmpB, a1b1, loopNum/2);

        free(tmpA);
        free(tmpB);
    }
}