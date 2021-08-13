#include<stdio.h>
#include"operation.h"

int Gcd(int a, int b){
    int tmp, n;

    if(a < b){
        tmp = a;
        a = b;
        b = tmp;
    }

    while(b!=0){
        n = a % b;
        a = b;
        b = n;
    }
    return a;
}