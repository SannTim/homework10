#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

int N;
pid_t son;
void handleral(int k){
    N = 0;
}

void handler1(int k){
    printf("Father\n");
    if (N) kill(son,SIGUSR1);
    signal(SIGUSR1,handler1);
}

void handler2(int k){
    printf("Son\n");
    if (N) kill(getppid(),SIGUSR1);
    signal(SIGUSR1,handler2);
}
void empty(int k){}
void hanalpr(int k){
    printf("Father\n");
    signal(SIGALRM,hanalpr);
}
int main(){
    signal(SIGALRM, handleral);
    signal(SIGUSR1,handler2);
    N = 1;
    
    son = fork();
    if (son == 0){
        N = 1;
        alarm(2);
        pause();
        while (N) pause();

        exit(1);
    }
    alarm(2);
    printf("Father\n");
    signal(SIGUSR1, handler1);
    kill(son,SIGUSR1);  
    pause();  
    while (N)pause();
    signal(SIGALRM,hanalpr);
    alarm(1);
    while (pause()){
        alarm(1);
    }
}