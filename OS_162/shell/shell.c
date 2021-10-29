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
    {cmd_exit, "exit", "exit the comand shell"},
};

int cmd_help(unused struct tokens *tokens){

}

int cmd_exit(unused struct tokens *tokens){
    exit(0);
}

int lookup(char cmd[]){

}

void init_shell(){


}

int main(unused int argc, unused char *argv[]){
    
}