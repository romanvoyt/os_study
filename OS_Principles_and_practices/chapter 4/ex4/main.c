#include <stdio.h>
#include "thread.h"
#include <time.h>

#define NUM 10000000

/* */

static void waiter(int ch);
static void incrementer(int num);

static thread_t threads[2];

int main(int argc, char **argv){
    char ch = 'q';
    thread_create(&(threads[0]), incrementer, NUM);
    thread_create(&(threads[1]), &waiter, ch);
    thread_join(threads[0]);
    thread_join(threads[1]);
    
    printf("main thread done");
    
    return 0;
}

void incrementer(int num){
    for(int i=0; i<num*100; i++){
        if(i%num == 0) printf(". \n");
    }
}

void waiter(int ch){
    while((int)fgetc(stdin)!= ch){
        fgetc(stdin);
        printf("Thank for yout input \n");
    }
}