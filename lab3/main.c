#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define INPUTSIZE 100
#define TOKENDELIM "\0"

char *shellreadline(void);
char **shellgettoken(char *buffer);

int main(int argc, char** argv){
    char *buffer;
    char **key;
    int flag;
    do{
        printf("Your Command\n");
        buffer = shellreadline();
        key = shellgettoken(buffer);
        flag = shellcheck(key);
        shellfork(key, flag);
        
        free(buffer);
        free(key);
    }while(key != NULL);
    return(EXIT_SUCCESS);
}

char *shellreadline(void){
    int inputsize = INPUTSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * inputsize);
    int ch;

    while(1){
        ch = getchar();
        if(ch == '\n'){
            buffer[position] = '\0';
            return buffer;
        }else if(ch == ' '){
            buffer[position] = '\0';
            position++;
        }else{
            buffer[position] = ch;
            position++;
        }
        
        if(position >= INPUTSIZE){
            position += INPUTSIZE;
            buffer = realloc(buffer, position);
            if (!buffer){
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **shellgettoken(char *buffer){
    int inputsize = INPUTSIZE;
    int position = 0;
    char **tokens = malloc(sizeof(char) * inputsize);
    char *token;

    token = strtok(buffer, TOKENDELIM);
    while(token != NULL){
        tokens[position] = token;
        position++;
        token = strtok(NULL, TOKENDELIM);
        
        if(position >= INPUTSIZE){
            position += INPUTSIZE;
            tokens = realloc(tokens, position * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    tokens[position] = '\0';
    return tokens;
}

int shellcheck(char **keys){
    int i = 0;
    char **args[] = {
        'ls', 'ps', 'pwd'
    };
    
    while(i <= 2){
        if(strcmp(keys[0], args[i]) != 0){
            i++;
        }else{
            if(args[1] == NULL){
                perror("shell");
            }else{
                if(chdir(args[1] != 0)){
                    perror("shell");
                }
            }
            return 1;
        }
    }
    return 0;
}

int shellfork(char **keys, int flag){
    pid_t pid = fork();
    
    if(pid == 0){
        //Child Process
        if(execvp(keys[0], keys) == -1){
            printf("ERROR FORKING CHILD PROCESS\n");
        }else{
            printf("CHILD\n");
        }
    }else if(pid > 0){
        //Parent Process
        if(flag == 1){
            printf("WAITING\n");
            pid = wait(NULL);
        }
        printf("PARENT\n");
    }else{
        //Error Forking
        printf("ERROR FORKING\n");
    }
}
