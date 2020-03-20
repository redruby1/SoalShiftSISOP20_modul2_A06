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
	if(inp[0] == '*') return -1;
	else {
		int i;
		for(i=0; i<strlen(inp); i++) {
			if(inp[i] < '0' || inp[i] > '9') {
				return 0;
			}
		}
		return 1;
	}
}

int main(int argc,char *argv[]) {
	int arg[4], i;
	
	if(argc == 5) {		
		for(i=1; i<4; i++) {
			if(input(argv[i]) == 1) {
				arg[i] = atoi(argv[i]);
			}
			else if(input(argv[i]) == -1) {
				arg[i] = -1;
			}
			else if(input(argv[i]) == 0){
				printf("Argumen %d tidak valid\n", i);
        		exit(EXIT_FAILURE);
			}
		}
		
		if(arg[1] > 59 || arg[2] > 59 || arg[3] > 23) {
			printf("Argumen tidak valid\n");
			exit(EXIT_FAILURE);
		}
		
		time_t times;
		struct tm *local; 
		
		int hour, min, sec;
			
		pid_t pid, sid, anak;
	
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
			time(&times);
			local = localtime(&times);
			
			hour = local->tm_hour;
			min = local->tm_min;
			sec = local->tm_sec;
			
			if((sec == arg[1] || arg[1] == -1) && (min == arg[2] || arg[2] == -1) && (hour == arg[3] || arg[3] == -1)) {
				anak = fork();
			}
	    	
	    	if(anak == 0) {
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
