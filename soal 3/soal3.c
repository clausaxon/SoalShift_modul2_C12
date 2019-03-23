#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int main()
{
    pid_t child1;
    pid_t child2;
    pid_t child3;
    int status, pip[4];
    char isi[300000];

    child1 = fork();

    if(child1 == 0){
      execl("/usr/bin/unzip","unzip", "campur2.zip", NULL);
    }else{
        int p2;
        while(wait(&status)>0);
        pipe(pip);
        pipe(pip+2);
        child2 = fork();
        if(child2==0){
          close(pip[0]);
          close(pip[2]);
          close(pip[3]);
          dup2(pip[1], STDOUT_FILENO);
          close(pip[1]);
          execl("/bin/ls", "ls" ,"campur2", NULL);
        }else{
            child3 = fork();
            if(child3==0){
              close(pip[1]);
              dup2(pip[0],STDIN_FILENO);
              close(pip[0]);

              close(pip[2]);
              dup2(pip[3],STDOUT_FILENO);
              close(pip[3]);
              execl("/bin/grep", "grep" ,".txt$", NULL);
            }else{
              close(pip[1]);
              close(pip[0]);
              close(pip[3]);
              int x = read(pip[2],isi,sizeof(isi));
              close(pip[2]);
              FILE* output;
              output = fopen("daftar.txt","w+");
              fputs(isi,output);
              fclose(output);
            }
            
        }
    }
}
