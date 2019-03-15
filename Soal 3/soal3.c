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

#define share 1
#define get 0

int main(){
	pid_t pid1,pid2,pid3;
	int fd1[2];
	int fd2[2];	
	char fileTxt[10000];
	int delay;
	pid1 = fork();
	if(pid1 > 0){
	
		printf("first");		
		while(wait(&delay) > 0);
		printf("adsasdas");
		
		pipe(fd1);
		pipe(fd2);

		pid2=fork();

		if(pid2 == 0){
			
			dup2(fd1[share],1);
			close(fd1[share]);
			close(fd1[get]);
			close(fd2[share]);
			close(fd2[get]);

			//nge ls file campur2
			execlp("ls","ls","campur2",NULL);


		}else{
//			int delay2;
			//while(wait(&delay2)>0);
			wait(NULL);

			pid3=fork();		

			if(pid3 == 0){
				
				dup2(fd1[get],0);
				close(fd1[get]);
				close(fd1[share]);

				dup2(fd2[share],1);
				close(fd2[share]);
				close(fd2[get]);
				
				//nge grep .txt	
			
				execlp("grep","grep",".txt$",NULL);
			}else{
				//Membuat file
				
				read(fd2[get],fileTxt,sizeof(fileTxt));

				FILE *data;
				data = fopen("data.txt","w+");
				fputs(fileTxt,data);
				fclose(data);
				

				close(fd1[share]);
				close(fd1[get]);
				close(fd2[share]);
				close(fd2[get]);


			}


		}


	}else{

		//nzippingnya	
		execlp("unzip","unzip","campur2.zip", NULL);
	//		exit(1);
	}

	return 0;
}
