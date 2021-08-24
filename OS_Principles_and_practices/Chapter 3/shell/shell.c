#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define shell_rl_buffersize 1024
#define shell_tok_BUFSIZE 64
#define shell_tok_DELIM " \t\r\n\a"

/* Lifetime of a shell  
    1. Initialize
    2. Interpret
    3. Terminate
*/

/* Basic loop of a shell */

void shell_loop(void){
    char *line;
    char **args;
    int status;

    do{
        printf("> ");
        line = shell_read_line();
        args = shell_split_line();
        status = shell_execute(args);

        free(line);
        free(args);
    } while(status);
}

/* read line function  */

char *shell_read_line(void){
    int bufsize = shell_rl_buffersize;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "shell: allocation error");
        exit(EXIT_FAILURE);
    }

    while(1) {
        c = getchar();
        if(c == EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        //realllocation of the buffer if we exceeded its size
        if(position>=bufsize){
            bufsize += shell_rl_buffersize;
            buffer = realloc(buffer, bufsize);

            if(!buffer){
                fprintf(stderr, "shell: allocation error");
                exit(EXIT_FAILURE);
            }
        }
    }
}

/* split line function */

char **shell_split_line(char *line){
    int bufsize = shell_tok_BUFSIZE, postion = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if(!tokens){
        fprintf(stderr, "shell: allocation error \n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, shell_tok_DELIM);
    while(token!=NULL){
        tokens[postion] = token;
        postion++;

        if(postion>=bufsize){
            bufsize += shell_tok_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if(!tokens){
                fprintf(stderr, "shell: allocation error \n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, shell_tok_DELIM);
    }

    tokens[postion] = NULL;
    return tokens;
}

/* shell execution */

int shell_launch(char **args){
    pid_t pid, wpid;
    int status;

    pid = fork();
    if(pid == 0){
        if(execvp(args[0], args) == -1){
            perror("shell");
        }
    }else if (pid < 0){
        perror("shell");
    }else if(){
        //parent process is
        do{
            wpid = wait(pid, &status, WUNTRACED);
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/*shell builtins*/

int shell_cd(char **args);
int shell_help(char **args);
int shell_exid(char **args);

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit
};

int shell_num_builtins(){
    return sizeof(builtin_str) / sizeof(char *);
}

/* builtin functions implementation */
int shell_cd(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "shell: expected arguments to \"cd\" \n");
    }else{
        if(chdir(args[1]) != 0){
            perror("shell");
        }
    }

    return 1;
}

int shell_help(char **args){
    int i;
    printf("Stephen Brennan's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for(i = 0; i < shell_num_builtins(); i++){
        printf(" %s \n", builtin_str[i]);
    }

    printf("Use the man command for info on other programs");
    
    return 1;
}

int shell_exit(char **args){
    return 0;
}

int shell_execute(char **args){
    int i;
    if(args[0] == NULL){
        return 1;
    }

    for ( i = 0; i < shell_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i])==0)
        {
            return (*builtin_func[i])(args);
        }
        
    }

    return shell_launch(args);
}


int main(int argc, char *argv[]){
    
    shell_loop();
    return EXIT_SUCCESS;
}