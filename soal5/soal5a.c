#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

int main(){
    pid_t pid, sid;
    pid = fork();
    if (pid < 0){
        exit(EXIT_FAILURE);
    }
    if (pid > 0){
        exit(EXIT_SUCCESS);
    }
    umask(0);
    sid = setsid();
    if (sid < 0){
        exit(EXIT_FAILURE);
    }
    if ((chdir("/")) < 0){
        exit(EXIT_FAILURE);
    }
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    while(1){
        struct tm *currtime;
        time_t timenow;
        time(&timenow);
        currtime = localtime(&timenow);

        char folder[50];
        char path[100];
        strcpy(path, "/home/hayu/log/");

        sprintf(folder, "%02d:%02d:%02d-%02d:%02d", currtime->tm_mday, currtime->tm_mon + 1, currtime->tm_year + 1900, currtime->tm_hour, currtime->tm_min);
        strcat(path, folder);
        mkdir(path, S_IRWXU | S_IRWXO | S_IRWXG);

        for(int i=0; i<30; i++){
            char file[100];
            char c;
	    char syslog[100] = "/var/log/syslog";
            FILE *read = fopen(syslog, "r");
            sprintf(file, "%s/log%d.log", path, i+1);
            FILE *write = fopen(file, "w+");

            if(read != NULL && write != NULL){
                while((c = fgetc(read))  != EOF){
                        fputc(c, write);
                }
            fclose(write);
            fclose(read);
            }
            sleep(1);
        }
    }
    exit(EXIT_SUCCESS);
}
