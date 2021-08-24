#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
	/*if(argc != 4){
		printf("Wrong use of a program! \n");
		return 0;
	}*/
	char *arg1[] = {"./hello_world", NULL};
	char *arg2[] = {"./hello_world", "parent"};
	int pid = fork();
	
	if(pid == 0){
		execvp(arg1[0], arg1);
	}else{
		printf("hello from parent \n");
	}
	return 0;
}
