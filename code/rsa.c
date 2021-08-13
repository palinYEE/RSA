#include<stdio.h>
#include<stdlib.h>
#include"rsa.h"
#include"operation.h"

void Basic_RSA(){
    // 키생성을 위한 파라미터
    int p, q;       // 소수
    int N, phi_N;   // N, 오일러 피 N
    int e, d;       // 나머지 파라미터

    // 암복호화를 위한 파라미터
    int m;      // 메세지
    int i;      // 반복문 변수
    int tmp;    // 연산을 위한 임시 변수

    // 입력 값으로 두개의 소수를 입력. (1 ~ 100 사이의 값만 입력)
    printf("[1-1] 두 소수를 입력하세요. (1 ~ 100 사이)\n");
    printf("       p = ");
    scanf("%d", &p);

    printf("       q = ");
    scanf("%d", &q);

    // 파라미터 N, 오일러 피 N 값을 계산.
    N = p * q;
    phi_N = (p-1) * (q-1);

    printf("[1-2] 계산한 N 값은 %d, 오일러 피 N 값은 %d 입니다. \n", N, phi_N);

    do{
        e = rand()%phi_N;
    }while(Gcd(e, phi_N) != 1);

    // e 값 선택
    printf("[1-3] 선택한 e 값은 %d 입니다.\n", e);

    for(d = 1; d<phi_N; d++){
        if((e * d)%phi_N == 1)
            break;
    }

    // d 값 계산
    printf("[1-4] 계산한 d 값은 %d 입니다.\n", d);

    printf("[1. KeyGenerate summary]\n");
    printf("    공개키 : (%d, %d)\n", N, e);
    printf("    개인키 : (%d, %d, %d, %d)\n", N, p, q, d);

    printf("[1-5] 메세지를 입력하세요 (%d 보다 작아야 합니다.): ", N);
    scanf("%d", &m);
    // 암호화
    tmp = m;
    for(i=0; i<e-1; i++){
        m = tmp * m;
        m = m % N;
    }
    
    printf("[1-6] 암호문은 %d 입니다. \n", m);

    // 복호화
    tmp = m;
    for(i=0; i<d-1; i++){
        m = tmp * m;
        m = m % N;
    }
    printf("[1-7] 평문은 %d 입니다. \n ", m);
}