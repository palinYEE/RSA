#include<stdio.h>
#include"add.h"

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
void naiveAdd(unsigned int *a, unsigned int *b, unsigned int *dst);