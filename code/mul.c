#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mul.h"
#include"add.h"

/*
 0001 1101 0101 1111 : a
 0010 1011 1111 1010 : b
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