#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

while(1)
{
   char totalfile[100]; //nama file lengkap .png
   char hasil[100];
   char totalfile2[100]; //copy an dari totalfile
   char file2[100]= "_grey.png";
   char *file; //yang dipake buat ambil titik dalam file.png

   DIR *dir = opendir("/home/hayu/modul2/soal1"); //ngambil dari direktori
   struct dirent *d; //read file
   
   if(dir == NULL)
        return 0;

   while((d = readdir(dir)) != NULL) {
                strcpy(totalfile, d->d_name);
                file = strrchr(totalfile, '.');
                strcpy(totalfile2, totalfile);

                if(file && (strcmp(file, ".png")==0)){
                        *file = '\0'; //buat ngebuat null/ gantiin posisi titik
                        strcpy(hasil, totalfile);
                        strcat(hasil, file2);

                        char awal[500]={"/home/hayu/modul2/soal1/"};
                        char tujuan[500]={"/home/hayu/modul2/soal1/gambar/"};

                        strcat(awal, totalfile2);
                        strcat(tujuan, hasil);
                        rename(awal, tujuan);
                }
        }

   closedir(dir);
   sleep(10);
}
   exit(EXIT_SUCCESS);
}
