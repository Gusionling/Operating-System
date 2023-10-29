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
#include <time.h>

#define PIDS 21

#define NICE_HIGH -19
#define NICE_MID 1
#define NICE_LOW 19
#define NNICE 99

//if_nice는 CFS_NICE일 떄 출력 값을 다르게 하기 위해서 적는 변수이며 nice 범위 밖인 99가 default이다. 
void print_time(uint32_t pid, struct timeval start_time, struct timeval end_time, int if_nice){
    
    struct timeval elapsed_time;
    timersub(&end_time, &start_time, &elapsed_time);

	time_t start_seconds = start_time.tv_sec;
    time_t end_seconds = end_time.tv_sec;

    struct tm start_timeinfo;
    struct tm end_timeinfo;

	localtime_r(&start_seconds, &start_timeinfo);
    localtime_r(&end_seconds, &end_timeinfo);

    int start_hour = start_timeinfo.tm_hour;
    int start_minute = start_timeinfo.tm_min;
    int start_second = start_timeinfo.tm_sec;

    int end_hour = end_timeinfo.tm_hour;
    int end_minute = end_timeinfo.tm_min;
    int end_second = end_timeinfo.tm_sec;


    printf("PID: %d | ", pid);
	if(if_nice != NNICE){
		printf("NICE: %3d | ", if_nice);
	}
	printf("Start time: %02d:%02d:%02d.%06ld | ",start_hour, start_minute, start_second, start_time.tv_usec);
	printf("End time: %02d:%02d:%02d.%06ld | ",end_hour, end_minute, end_second, end_time.tv_usec);
	printf("Elapsed time: %ld.%06ld\n", elapsed_time.tv_sec, elapsed_time.tv_usec);

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
					
					print_time(pid, begin_t[j], end_t[j], NNICE);
				}
			}
		}
	}

    
    printf("Scheduling Policy: CFS_DEFAULT | ");
	print_avg_elapsed_time(begin_t, end_t);
	
}

void CfsNice(){
	
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

			//생성 순서에 따른 nice값 적용
			if(i<7){
				nice(NICE_HIGH);
				product();
			}
			else if (i<14){
				nice(NICE_MID);
				product();
			}
			else
			{
				nice(NICE_LOW);
				product();
			}

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
					if(j<7){
						print_time(pid, begin_t[j], end_t[j], NICE_HIGH);
					}
					else if(j <14){
						print_time(pid, begin_t[j], end_t[j], NICE_MID);
					}
					else{
						print_time(pid, begin_t[j], end_t[j], NICE_LOW);
					}
				
				}
			}
		}
	}

    
    printf("Scheduling Policy: CFS_NICE | ");
	print_avg_elapsed_time(begin_t, end_t);
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