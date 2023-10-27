#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


void CfsDefault(){
	printf("This is CFS_DEFAULT\n");
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
