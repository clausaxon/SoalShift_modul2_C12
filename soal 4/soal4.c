#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#include<fcntl.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/claus/Documents/makanan")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
int i=1;
while(1) {
 struct stat sb;

 stat("/home/claus/Documents/makanan/makan_enak.txt", &sb);
 struct tm waktu1; 
 waktu1 = *localtime(&sb.st_atime);

 //printf("%d\n", waktu.tm_min);

 time_t t = time(NULL);
 struct tm waktu2 = *localtime(&t);
 // printf("now: %d-%d-%d %d:%d:%d\n", waktu2.tm_year + 1900, waktu2.tm_mon + 1, waktu2.tm_mday, waktu2.tm_hour, waktu2.tm_min, waktu2.tm_sec);

 double a =  difftime (mktime(&waktu2),mktime(&waktu1));

 if(a <=30  ){
 int fd;
 mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
// char *filename = "/home/claus/Documents/makanan/makanan_sehat.txt";
 char filename[100];
 sprintf(filename, "makan_sehat%d.txt", i); 
fd = creat(filename, mode);
 i++;
 }
sleep (5);
}
exit(EXIT_SUCCESS);

}
