#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <dirent.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define PROC "/proc"  // /proc 절대 경로

#define TTY_LEN 32
#define PATH_LEN 1024

//typedef struct{
//    unsigned long pid;
//    unsigned long uid; 
//    char user[UNAME_LEN};
//    char tty[TTY_LEN];
//    char stat[STAT_LEN];
//    char start[TIME_LEN];
//    char time[TIME_LEN];
//    char cmd[CMD_LEN];
//}myProc;

pid_t current_pid;
uid_t current_uid;
char current[TTY_LEN];
char myPath[PATH_LEN];  //자신의 path
char myTTY[TTY_LEN];  //자신의 tty
   


void getTTY(char path[PATH_LEN], char tty[TTY_LEN])
{
    char fdZeroPath[PATH_LEN];			//0번 fd에 대한 절대 경로
	memset(tty, '\0', TTY_LEN);
	memset(fdZeroPath, '\0', TTY_LEN);
	strcpy(fdZeroPath, path);
	strcat(fdZeroPath, "/fd/0");

	if(access(fdZeroPath, F_OK) < 0){	//fd 0이 없을 경우

		char statPath[PATH_LEN];		// /proc/pid/stat에 대한 절대 경로
		memset(statPath, '\0', PATH_LEN);
		strcpy(statPath, path);
		strcat(statPath, "/stat");

		FILE *statFp;
		if((statFp = fopen(statPath, "r")) == NULL){	// /proc/pid/stat open
			fprintf(stderr, "fopen error %s %s\n", strerror(errno), statPath);
			sleep(1);
			return;
		}

		char buf[1024];
		for(int i = 0; i <= 6; i++){		// 7행까지 read해 TTY_NR 획득
			memset(buf, '\0', 1024);
			fscanf(statFp, "%s", buf);
		}
		fclose(statFp);

		int ttyNr = atoi(buf);		//ttyNr 정수 값으로 저장

		DIR *dp;
		struct dirent *dentry;
		if((dp = opendir("/dev")) == NULL){		// 터미널 찾기 위해 /dev 디렉터리 open
			fprintf(stderr, "opendir error for %s\n", "/dev");
			exit(1);
		}
		char nowPath[PATH_LEN];

		while((dentry = readdir(dp)) != NULL){	// /dev 디렉터리 탐색
			memset(nowPath, '\0', PATH_LEN);	// 현재 탐색 중인 파일 절대 경로
			strcpy(nowPath, "/dev");
			strcat(nowPath, "/");
			strcat(nowPath, dentry->d_name);

			struct stat statbuf;
			if(stat(nowPath, &statbuf) < 0){	// stat 획득
				fprintf(stderr, "stat error for %s\n", nowPath);
				exit(1);
			}
			if(!S_ISCHR(statbuf.st_mode))		//문자 디바이스 파일이 아닌 경우 skip
				continue;
			else if(statbuf.st_rdev == ttyNr){	//문자 디바이스 파일의 디바이스 ID가 ttyNr과 같은 경우
				strcpy(tty, dentry->d_name);	//tty에 현재 파일명 복사
				break;
			}
		}
		closedir(dp);

		if(!strlen(tty))					// /dev에서도 찾지 못한 경우
			strcpy(tty, "?");				//nonTerminal
	}
	else{
		char symLinkName[128];
		memset(symLinkName, '\0', 128);
		if(readlink(fdZeroPath, symLinkName, 128) < 0){
			fprintf(stderr, "readlink error for %s\n", fdZeroPath);
			exit(1);
		}
		if(!strcmp(symLinkName, "/dev/null"))		//symbolic link로 가리키는 파일이 /dev/null일 경우
			strcpy(tty, "?");					//nonTerminal
		else
			sscanf(symLinkName, "/dev/%s", tty);	//그 외의 경우 tty 획득

	}
	return;
}

int main(int argc, char *argv){
	
    //현재 pid
    current_pid = getpid();

    char pidPath[128];
    memset(pidPath, '\0', 128);
    sprintf(pidPath, "/%d", current_pid);

    strcpy(myPath, PROC);
    strcat(myPath, pidPath);
    
    printf("myPath : %s\n", myPath);
    
    getTTY(myPath, myTTY);

    printf("TTY:%s\n", myTTY);
    
    current_uid = getuid();

    printf("UID:%d\n", current_uid);
    
    return 0;

}


