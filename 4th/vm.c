#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define EBIT 262144 //18bit
#define NBIT 524288 //19bit
#define TBIT 1048576 //20bit
#define ONEKB 1024 //1KB
#define TWOKB 2048 // 2KB
#define FOUREKB 4096 //4KB
#define ADDRESSC 5000 //가상주소 개수 


int vlength;  //가상주소의 길이
int psize; //페이지 크기
int pnum; //페이지 개수
int fnum; //프레임 개수


int main()
{
    int select1, select2, select3, select4, select5;
    while(1){
        printf("A. Simulation에 사용할 가상주소 길이를 선택하시오 (1. 18bits  2. 19bits 3. 20bits) : ");
        scanf("%d", &select1);
        if(select1 == 1){
            vlength = EBIT;
            break;
        } else if(select1 == 2){
            vlength = NBIT;
            break;
        } else if(select1 == 3) {
            vlength = TBIT;
            break;
        }
        else{
            printf("올바른 입력이 아닙니다. 다시 입력하세요 \n");
        }

    }

    while(1){
        printf("B. Simulation에 사용할 페이지(프레임)의 크기를 선택하시오 (1. 1KB  2. 2KB 3. 4KB) : ");
        scanf("%d", &select2);
        if(select2 == 1){
            psize = ONEKB;
            break;
        }else if (select2 == 2){
            psize = TWOKB;
            break;
        } else if( select2 == 3) {
            psize = FOUREKB;
            break;
        }
        else{
            printf("올바른 입력이 아닙니다. 다시 입력하세요 \n");
        }

    }

    pnum = vlength / psize;

    while(1){
        
        printf("C. Simulation에 사용할 물리메모리의 크기를 선택하시오 (1. 32KB  2. 64KB ) : ");
        scanf("%d", &select3);
        if(select3 == 1 || select3 == 2 ) {
            if(select3 == 1){
                if(select2 == 3){
                    fnum = 32/4;
                }else
                    fnum = 32/select2;
            }
            else{
                 if(select2 == 3){
                    fnum = 64/4;
                }else
                    fnum = 64/select2;
            }
            printf("frame 의 개수 : %d개 \n", fnum);
            break;
        }
        else{
            printf("올바른 입력이 아닙니다. 다시 입력하세요 \n");
        }

    }

    while(1){
        
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
        
        printf("E. 가상주소 스트링 입력방식을 선택하시오\n (1. input.in 자동 생성  2. 기존 파일 사용) : ");
        scanf("%d", &select5);
        if(select5 == 1){
            

        } else if(select5 == 2)  {
            char filename[100];
            printf("입력 파일 이름을 입력하시오:");
            scanf("%s", filename);

            FILE *file = fopen(filename, "r");

            if(file == NULL){
                perror("기존 파일 열기 실패");
            }

            fclose(file);

        }
        else{
            printf("올바른 입력이 아닙니다. 다시 입력하세요 \n");
        }

    }
            
            
}