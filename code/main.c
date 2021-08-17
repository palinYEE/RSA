#include<stdio.h>
#include<stdlib.h>
#include<time.h> 

#include"rsa.h"
#include"add.h"

void printArrayHexa(const unsigned char *in, int n){
    int i;
    for(i=0; i<n; i++){
        printf("%02x", in[i]);
    }
    printf("\n");
}

void genRandomTestVector(unsigned char *in, int n){
    int random;
    int i;

    for(i=1; i<n; i++){
        in[i] = rand()%0x100;
    }
    if(BIT_SIZE%8 == 0){
        in[0] = rand()%0x100;
    }
    else{
        in[0] = rand()%(0x01<<BIT_SIZE%8);
    }    
}

void inputArray(unsigned char *a, unsigned char *b){
    int i;
    unsigned int tmp;

    printf("a 값을 입력하세요 (8비트 %d개): ", BIT_SIZE/8);
    for(i=0; i<BIT_SIZE/8; i++){
        scanf("%02x", &tmp);
        a[i] = tmp;
    }
    printf("b 값을 입력하세요 (8비트 %d개): ", BIT_SIZE/8);
    for(i=0; i<BIT_SIZE/8; i++){
        scanf("%02x", &tmp);
        b[i] = tmp;
    }
}



void OperationTest(){
    int i;
    int choice;
    int arrayElementNum;
    unsigned char *a;
    unsigned char *b;
    unsigned char *dst;

    srand(time(NULL));
    a = calloc(BIT_SIZE/8, sizeof(unsigned char));
    b = calloc(BIT_SIZE/8, sizeof(unsigned char));

    if(BIT_SIZE%8 == 0){
        arrayElementNum = BIT_SIZE/8;
        dst = calloc(arrayElementNum + 1, sizeof(unsigned char));
    }
    else{
        arrayElementNum =  BIT_SIZE/8 + 1;
        dst = calloc(arrayElementNum, sizeof(unsigned char));
    }

    system("clear");
    printf("=================\n");
    printf("[*] Operation Test\n");
    printf("=================\n");
    printf("1. Naive ADD\n");
    printf("choice number : ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        if(BIT_SIZE <= 16){
            inputArray(a,b);
        }
        else{
            genRandomTestVector(a, arrayElementNum);
            genRandomTestVector(b, arrayElementNum);
        }
        
        printf("Array a : 0x");
        printArrayHexa(a, arrayElementNum);
        printf("Array b : 0x");
        printArrayHexa(b, arrayElementNum);
        naiveAdd(a, b, dst, arrayElementNum);
        printf("Array a+b : 0x");
        printArrayHexa(dst, arrayElementNum + 1);
        break;
    
    default:
        break;
    }

    free(a);
    free(b);
    free(dst);
}

int main(){
    system("clear");
    int choice;
    printf("=================\n");
    printf("[*] RSA Algorithm\n");
    printf("=================\n");
    printf("[*] Global Setting value\n");
    printf(" - BIT_SIZE %d\n", BIT_SIZE);
    printf("=================\n");
    printf("1. Basic RSA Code\n");
    printf("2. Operation Test");
    printf("\n");
    printf("choice number : ");
    scanf("%d", &choice);
    
    switch (choice)
    {
    case 1:
        Basic_RSA();
        break;
    case 2:
        OperationTest();
        break;
    default:
        break;
    }
}