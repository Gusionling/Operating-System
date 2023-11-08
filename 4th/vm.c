#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>





int main()
{
    while(1){
        int select1;
        printf("A. Simulation에 사용할 가상주소 길이를 선택하시오 (1. 18bits  2. 19bits 3. 20bits) : ");
        scanf("%d", &select1);
        if(select1 == 1 || select1 == 2 || select1 == 3) {
            break;
        }
        else{
            printf("올바른 입력이 아닙니다. 다시 입력하세요 \n");
        }

    }

    while(1){
        int select2;
        printf("B. Simulation에 사용할 페이지(프레임)의 크기를 선택하시오 (1. 1KB  2. 2KB 3. 4KB) : ");
        scanf("%d", &select2);
        if(select2 == 1 || select2 == 2 || select2 == 3) {
            break;
        }
        else{
            printf("올바른 입력이 아닙니다. 다시 입력하세요 \n");
        }

    }

    while(1){
        int select3;
        printf("C. Simulation에 사용할 물리메모리의 크기를 선택하시오 (1. 32KB  2. 64KB ) : ");
        scanf("%d", &select3);
        if(select3 == 1 || select3 == 2 ) {
            break;
        }
        else{
            printf("올바른 입력이 아닙니다. 다시 입력하세요 \n");
        }

    }

    while(1){
        int select4;
        printf("D. Simulation에 적용할 Page Replacement 알고리즘을 선택하시오\n (1. Optimal  2. FIFO 3. LRU 4. Second-Chance) : ");
        scanf("%d", &select4);
        if(select4 == 1 || select4 == 2 || select4 == 3 || select4 == 4) {
            break;
        }
        else{
            printf("올바른 입력이 아닙니다. 다시 입력하세요 \n");
        }

    }

    while(1){
        int select5;
        printf("E. 가상주소 스트링 입력방식을 선택하시오\n (1. input.in 자동 생성  2. 기존 파일 사용) : ");
        scanf("%d", &select5);
        if(select5 == 1 || select5 == 2) {
            break;
        }
        else{
            printf("올바른 입력이 아닙니다. 다시 입력하세요 \n");
        }

    }
            
            
}