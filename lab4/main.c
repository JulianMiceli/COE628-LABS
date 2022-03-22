#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

char input[100];
char parent_cmd[50];
char child_cmd[50];

int main(int argc, char** argv) {
    int fd[2], pid;
    int i;
    int pipeflag = 0;
    int parentc = 0;
    int childc = 0;

    printf("Your command> ");
    fgets(input, 100, stdin);
    for(i = 0; i < strlen(input)-1; i++){
	if(input[i] != '|' && pipeflag == 0){
            parent_cmd[parentc] = input[i];
            parentc++;
	}else if(input[i] != '|' && pipeflag == 1){
            child_cmd[childc] = input[i];
            childc++;
        }else if(input[i] == '|'){
            pipeflag = 1;
            i++;
	}
    }
    
    printf("Parent Command: %s\n", parent_cmd);
    printf("Child Command: %s\n", child_cmd);
	
    pipe(fd);
    pid = fork();

    if(pid == 0){
	dup2(fd[1], 1);
	close(fd[0]);
	system(child_cmd);
	exit(0);
    }else{
	dup2(fd[0], 0);
	close(fd[1]);
	system(parent_cmd);
    }
    return(EXIT_SUCCESS);
}