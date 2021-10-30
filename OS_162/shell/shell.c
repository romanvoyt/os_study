#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

#include "tokenizer.h"

#define unused __attribute__((unused))

bool shell_is_interactive;
int shell_terminal;

struct termios shell_tmodes;

pid_t shell_pgid;
int cmd_exit(struct tokens *tokens);
int cmd_help(struct tokens *tokens);

typedef int cmd_fun_t(struct tokens *tokens);

typedef struct fun_desc {
    cmd_fun_t *fun;
    char *cmd;
    char *doc;
} fun_desc_t;

fun_desc_t cmd_table[] = {
    {cmd_help, "?", "show this help menu"},
    {cmd_exit, "exit", "exit the shell"},
    {cmd_cwd, "pwd", "Prints current working directory"},
};

int cmd_help(unused struct tokens *tokens){
	for (u_int32_t i = 0; i < sizeof(cmd_table)/sizeof(fun_desc_t); i++)
    {
        printf("%s - %s\n", cmd_table[i].cmd, cmd_table[i].doc);
    }
    return 1;
}

int cmd_exit(unused struct tokens *tokens){
    exit(0);
}

int cmd_cwd(unused struct tokens *tokens){
    long size;
    char *ptr;
    char *buf;
    size = pathconf(".", _PC_PATH_MAX);


    if ((buf = (char *)malloc((size_t)size)) != NULL)
        ptr = getcwd(buf, (size_t)size);

    printf("%s ", ptr);

    free(buf);

    return 1;
}

int lookup(char cmd[]){
    for(u_int32_t i = 0; i < sizeof(cmd_table)/sizeof(fun_desc_t); i++){
        if(cmd && (strcmp(cmd_table[i].cmd, cmd) == 0)){
            return i;
        }
    }
    return -1;
}

void init_shell(){
    shell_terminal = STDIN_FILENO;

    shell_is_interactive = isatty(shell_terminal);

    if(shell_is_interactive){
        while(tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp())){
            kill(-shell_pgid, SIGTTIN);
        }

        shell_pgid = getpid();

        tcsetpgrp(shell_terminal, shell_pgid);

        tcgetattr(shell_terminal, &shell_tmodes);
    }

}

int main(unused int argc, unused char *argv[]){
    init_shell();

    static char line[4096];
    int line_num = 0;

    if(shell_is_interactive){
        fprintf(stdout, "%d: ", line_num);
    }

    while(fgets(line, 4096, stdin)){
        struct tokens *tokens = tokenize(line);

        int fundex = lookup(tokens_get_token(tokens, 0));

        if(fundex >= 0){
            cmd_table[fundex].fun(tokens);
        } else{
            fprintf(stdout, "Not running \n");
        }

        if(shell_is_interactive){
            fprintf(stdout, "%d: ", ++line_num);
        }

        tokens_destroy(tokens);
    }
    return 0;
}
