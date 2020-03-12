#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <dirent.h>
#include <time.h>

int main() {
	pid_t anak1, anak2, anak3, anak4, anak5;
	int status;
	
	int j=0, k=0;
	char filename[256][256], filename2[256][256];
	
	anak1 = fork();
	
	if(anak1 == 0) {
		char *argv[] = {"mkdir", "-p", "modul2/indomie", NULL};
    	execv("/bin/mkdir", argv);
    	
    	sleep(5);
	}
	else {
		while ((wait(&status)) > 0);
		anak2 = fork();
		
		if(anak2 == 0) {
			char *argv[] = {"mkdir", "-p", "modul2/sedaap", NULL};
    		execv("/bin/mkdir", argv);
		}
		else {
			while ((wait(&status)) > 0);
			anak3 = fork();
			
			if(anak3 == 0) {
				char *argv[] = {"unzip", "jpg.zip", "-d", "modul2/", NULL};
    			execv("/usr/bin/unzip", argv);
			}
			else {
				while ((wait(&status)) > 0);
				anak4 = fork();
				
				if(anak4 == 0) {
					
					pid_t baru1, baru2;
					int status1;
					
					DIR *d;
					struct dirent *dir;
					int i;
					
					if((d = opendir("modul2/jpg")) != NULL) {
					    while((dir = readdir(d)) != NULL) {
					        if(dir->d_type == DT_REG){
					        	strcpy(filename[j], dir->d_name); //file
					        	j++;
					        }
					        else {
					        	strcpy(filename2[k], dir->d_name); //dir
					        	k++;
							}
					    }
					    closedir(d);
					}
					
					for(i=0; i<j; i++) {
						baru1 = fork();
						
						char name[30];
						sprintf(name, "modul2/jpg/%s", filename[i]);
						
						if(baru1 == 0) {
							char *argv[] = {"mv", name, "modul2/sedaap", NULL};
	    					execv("/bin/mv", argv);
						}
					}
					
					for(i=2; i<k; i++) {
						baru1 = fork();
						
						char name[30];
						sprintf(name, "modul2/jpg/%s", filename2[i]);
						
						if(baru1 == 0) {
							char *argv[] = {"mv", name, "modul2/indomie", NULL};
	    					execv("/bin/mv", argv);
						}
						else {
							while ((wait(&status1)) > 0);
							baru2 = fork();
							
							char name2[30];
							sprintf(name2, "modul2/indomie/%s/coba1.txt", filename2[i]);
							
							if(baru2 == 0) {
								char *argv[] = {"touch", name2, NULL};
    							execv("/usr/bin/touch", argv);
    							
    							sleep(3);
							}
							else {
								while ((wait(&status1)) > 0);
								baru2 = fork();
								
								char name3[30];
								sprintf(name3, "modul2/indomie/%s/coba2.txt", filename2[i]);
								
								if(baru2 == 0) {
									char *argv[] = {"touch", name3, NULL};
	    							execv("/usr/bin/touch", argv);
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
