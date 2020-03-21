#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {	
	if(argc == 2) {
		printf("%s\n",argv[1]);
		if(!strcmp(argv[1], "-a")) {
			// killall (nama progam)
		}
		else if(!strcmp(argv[1], "-b")) {
			// kill -9 (pid)
		}
		else {
			printf("Argumen tidak valid\n");
			exit(EXIT_FAILURE);
		}
		
		time_t times;
		struct tm *local, *local2; 
		
		unsigned int t, uk;
		char name[30], name2[30], name3[30], namafile[30];
		
		pid_t pid, sid;
	
		pid = fork();
	
		if(pid < 0) {
			exit(EXIT_FAILURE);
		}
	  
		if(pid > 0) {
			exit(EXIT_SUCCESS);
		}
	
		umask(0);
	
		sid = setsid();
		if(sid < 0) {
			exit(EXIT_FAILURE);
		}
	
		if((chdir("/mnt/c/Users/Anisa Aurafitri/Documents/Sisop/modul2.1")) < 0) {
			exit(EXIT_FAILURE);
		}
	
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	
		while (1) {
			pid_t anak1, anak2, anak3;
			int status, i;
			
			time(&times);
			local = localtime(&times);
			
			sprintf(name, "%d-%d-%d_%d:%d:%d", local->tm_year+1900, local->tm_mon+1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
			
			anak1 = fork();
			
			if(anak1 == 0) {
				char *arg[] = {"mkdir", "-p", name, NULL};
		        execv("/bin/mkdir", arg);
			}
			else {
				while ((wait(&status)) > 0);
				anak2 = fork();
				
				if(anak2 == 0) {
					for(i=0; i<20; i++) {
						pid_t unduh;
						unduh = fork();
						
						if(unduh == 0) {
							time(&times);
							local2 = localtime(&times);
							
							t = (unsigned)time(NULL);
							uk = (t%1000)+100;
							
							sprintf(name2, "https://picsum.photos/%un/%un", uk, uk);
							sprintf(name3, "%d-%d-%d_%d:%d:%d", local2->tm_year+1900, local2->tm_mon+1, local2->tm_mday, local2->tm_hour, local2->tm_min, local2->tm_sec);
							
							sprintf(namafile, "%s/%s.jpg", name, name3);
							
							char *arg[] = {"wget", "-O", namafile, name2, NULL};
			        		execv("/usr/bin/wget", arg);
						}
						sleep(5);
					}
	
					anak3 = fork();
					
					if(anak3 == 0) {
						char zip[30];
						sprintf(zip, "%s.zip", name);
						
						char *arg[] = {"zip", "-rm", zip, name, NULL};
		        		execv("/usr/bin/zip", arg);
					}
				}
			}
			sleep(30);
		}
	}
	else {
		printf("Argumen tidak valid\n");
		exit(EXIT_FAILURE);
	}
}
