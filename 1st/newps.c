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
    
int main(int argc, char *argv){
	
    //현재 pid
    current_pid = getpid();

    char pidPath[128];
    memset(pidPath, '\0', 128);
    sprintf(pidPath, "/%d", current_pid);

    strcpy(myPath, PROC);
    strcat(myPath, pidPath);
    
    printf("myPath : %s\n", myPath);

    return 0;

}


