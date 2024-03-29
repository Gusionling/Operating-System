#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/wait.h>

#define PIDS 21


void print_time(uint32_t pid, struct timeval start_time, struct timeval end_time){
	
    struct timeval elapsed_time;

    timersub(&end_time, &start_time, &elapsed_time);
    printf("PID: %d | Start time: %ld.%06ld seconds | End time: %ld.%06ld seconds | Elapsed time: %ld.%06ld \n", pid, start_time.tv_sec, start_time.tv_usec, end_time.tv_sec, end_time.tv_usec, elapsed_time.tv_sec, elapsed_time.tv_usec);
}

void print_avg_elapsed_time(struct timeval begin_t[], struct timeval end_t[]) {
    // 모든 자식 프로세스의 실행 시간을 합산
    struct timeval total_elapsed_time = {0, 0};
    for (int i = 0; i < PIDS; i++) {
        struct timeval elapsed_time;
        timersub(&end_t[i], &begin_t[i], &elapsed_time);
        timeradd(&total_elapsed_time, &elapsed_time, &total_elapsed_time);
    }

    // 실행 시간의 평균 계산
    struct timeval avg_elapsed_time = {0, 0};
    avg_elapsed_time.tv_sec = total_elapsed_time.tv_sec / PIDS;
    avg_elapsed_time.tv_usec = total_elapsed_time.tv_usec / PIDS;

    printf("Average Elapsed Time: %ld.%06ld seconds\n", avg_elapsed_time.tv_sec, avg_elapsed_time.tv_usec);
}

void product(){
	int k, i, j;
	int count = 0; 

	int result[100][100];
	int A[100][100];
	int B[100][100];

	memset(result, 1, sizeof(result));
	memset(A, 1, sizeof(A));
	memset(B, 1, sizeof(B));

	while(count < 100){
        for(k = 0; k < 100; k++){
            for(i = 0; i < 100; i++){
                for(j = 0; j < 100; j++){
                    result[k][j] += A[k][i] * B[i][j];
                }
            }
        }
        count++;
 	}

}


void CfsDefault(){
	
	uint8_t i,j;
	uint32_t pid, pid_list[PIDS] = {0}; 
	struct timeval begin_t[PIDS], end_t[PIDS], elapsed_time;


	for(i=0; i<PIDS; i++){

		gettimeofday(&begin_t[i], NULL); //생성 시간 측정
		
		if((pid = fork()) == (uint32_t)-1){
			perror("Failed to fork");
			exit(EXIT_FAILURE);
		}
		
		if(pid == 0)
		{
			//자식 프로세스 작업 수행
			product();

			// 자식 프로세스 종료 시간 측정
			


			//자식 프로세스 종료
			exit(EXIT_SUCCESS);
		}

		else{
			pid_list[i] = pid;
		}
		
	}

	for(i=0; i<PIDS; i++){
		int status;
		if((pid = wait(&status))>1){
			for(j=0; j<PIDS; j++){
				if(pid_list[j]== pid){
                    gettimeofday(&end_t[j], NULL);
					
					print_time(pid, begin_t[j], end_t[j]);
				}
			}
		}
	}

    
    printf("Scheduling Policy: CFS_DEFAULT | ");
	print_avg_elapsed_time(begin_t, end_t);
	
}

void CfsNice(){
	printf("This is CFS_NICE\n");
}

void RtFifo(){
	printf("This is RT_FIFO\n");
}

void RtRr(){
	printf("This is RT_RR\n");
}




int main(int argc, char **argv)
{
	
	int core_id =0;
	cpu_set_t mask;

	CPU_ZERO(&mask); 	// mask를 초기화한다. 
	CPU_SET(core_id, &mask);		// 원하는 코어 ID를 설정한다. 
 	
	if(sched_setaffinity(0, sizeof(mask), &mask) == -1){
		perror("sched_setaffinity");
	}

	int select; 

	while(1){
		
		printf("Input the Scheduling Policy to apply:\n");
		printf("1. CFS_DEFAULT\n2. CFS_NICE\n3. RT_FIFO\n4. RT_RR\n0. Exit\n");
		printf(">> ");
		scanf("%d", &select);

		if(select == 1){
			CfsDefault();
		}

		else if (select == 2){
			CfsNice();
		}

		else if (select == 3){
			RtFifo();
		}
		else if (select == 4){
			RtRr();
		}
		else if (select == 0){
			exit(1);
		}
		else{
			printf("Wrong Input!\n");
		}
	}

	return 0;
}