#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<pwd.h>
#include<sys/stat.h>
#include<grp.h>
#include<unistd.h>

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

  if ((chdir("/home/claus")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

while(1){
    struct stat sb;

    stat("/home/claus/hatiku/elen.ku", &sb);

    struct passwd *pw = getpwuid(sb.st_uid);
    struct group  *gr = getgrgid(sb.st_gid);

   // printf("%s %s\n", pw->pw_name, gr->gr_name);
	char simpanpw[70];
	char simpangr[70];
	strcpy(simpanpw,pw->pw_name);
	strcpy(simpangr, gr->gr_name);

   printf("%s %s\n", simpanpw, simpangr);

	char ubahpw[70];
	char ubahgr[70];
	strcpy(ubahpw, "www-data");
	strcpy(ubahgr, "www-data");

	if(strcmp(simpanpw,ubahpw) == 0 &&
	strcmp(simpangr,ubahgr) == 0 ){

		int x;
		x=remove("/home/claus/hatiku/elen.ku");
	}

	char mode[] = "0777";
    	char buf[100] = "/home/claus/hatiku/elen.ku";
    	int i;
    	i = strtoul(mode, 0, 8);
	int y;
	y = chmod(buf,i);

	sleep(3);
}

exit (EXIT_SUCCESS);
}
