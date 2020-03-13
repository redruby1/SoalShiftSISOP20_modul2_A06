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

int input(char inp[]) {
	int isi;
	if(strlen(inp) == 1) if(inp[0] == '*') return -1;
	else {
		int i;
		for(i=0; i<strlen(inp); i++){
			if(inp[i] < '0' || inp[i] > '9') {
				printf("Argumen tidak valid\n");
				exit(EXIT_FAILURE);
			}
			else 
				isi = atoi(inp[i]);
		}
		return isi;
	}
}

int main(int argc,char *argv[]) {
	int arg[4], i;
	if(argc == 5) {
		for(i=1; i<4; i++) {
			arg[i] = input(argv[i]);
		}
		
		if(arg[1] > 59 || arg[2] > 59 || arg[3] > 23) {
			printf("Argumen tidak valid\n");
			exit(EXIT_FAILURE);
		}
			
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
	
		if((chdir("/")) < 0) {
			exit(EXIT_FAILURE);
		}
	
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	
		while (1) {
	    	pid_t anak1;
	    	anak1 = fork();
	    	
	    	int status;
	    	
	    	//timer belum
	    	
	    	if(anak1 == 0) {
	    		char *arg[] = {"bash", argv[4], NULL};
	        	execv("/bin/bash", arg);
			}
	
		sleep(1);
		}
	}
	else {
		printf("Argumen tidak valid\n");
		exit(EXIT_FAILURE);
	}
}
