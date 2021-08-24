#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int func1() {
	int val = 5;
	int pid;
	if (pid = fork())
		wait(&pid);
	val++;
	printf("%d\n", val);
	return val;
}

int func2() {
	int val = 5;
	int pid;
	if (pid = fork())
		wait(&pid);
	else
		exit(val);
	val++;
	printf("%d\n", val);
	return val;
}

int main(int argc, char *argv[]){
	/*int child = fork();
	int x = 5;
	
	if(child == 0){
		x += 5;
		printf("If x = %d \n", x);
	}else {
		child = fork();
		x += 10;
		printf("Else x = %d \n ", x);
		if(child){
			x += 5;
			printf("Nested if x = %d \n", x);
		}
	}*/
	func1();
	func2();
	return 0;
}
