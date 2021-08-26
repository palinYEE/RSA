#include<stdio.h>
#include"utils.h"

// 빅 엔디안 버전 프린트 함수
void printArray(unsigned char *a, int arrayNum){
    int i;
    for(i=arrayNum-1; i>=0; i--){
        printf("%02x | ", a[i]);
    }
    printf("\n");
}