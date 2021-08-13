#include<stdio.h>
#include"rsa.h"


int main(){
    int choice;
    printf("=================\n");
    printf("[*] RSA Algorithm\n");
    printf("=================\n");
    printf("1. Basic RSA Code\n");

    printf("\n");
    printf("choice number : ");
    scanf("%d", &choice);
    
    switch (choice)
    {
    case 1:
        Basic_RSA();
        break;
    
    default:
        break;
    }
}