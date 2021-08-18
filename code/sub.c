#include<stdio.h>
#include"rsa.h"
#include"sub.h"

/*
input : n-bit A (a_n | ... | a_0), B (b_n | ... | b_0)
output : n-bit C (c_n | c_{n-1} ... | c_1 | c_0)
    1. borrow <- 0
    2. for j=0 to n-1 do
    3.      c_j <- a_j xor b_j xor borrow
    4.      borrow <- (borrow and ~(a_j xor b_j)) | (~(a_j) and b_j)
    5. endfor
    6. return c_{n-1} | ... | c_0
*/
void naiveSub(unsigned char *a, unsigned char *b, unsigned char *dst, int loopNum);