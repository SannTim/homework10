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
#define MAXLEN 50
int f;
int N;
pid_t son;
char str[MAXLEN];


void readstr(){
    char c;
    int i = 0, g;
    while ((g = read(f,&c,1) > 0) && c == ' ' && c == '\n');
    if ((c != ' ') && (c != '\n') && g > 0)
        str[i++] = c;
    while((g = read(f,&c,1) > 0) && c != ' '&& c != EOF && c != '\n')
        str[i++] = c;
    printf(" ");
    if (g <= 0) {
        close(f);
        N = 0;    
    } 
    for (int j = 0; j < i; j++)
        printf("%c", str[j]);
    printf("\n");
}

void handleral(int k){
    N = 0;
}

void handler1(int k){
    printf("Father");
    readstr();
    if (N) kill(son,SIGUSR1);
    signal(SIGUSR1,handler1);
}

void handler2(int k){
    printf("Son");
    readstr();
    if (N) kill(getppid(),SIGUSR1);
    signal(SIGUSR1,handler2);
}

int main(int argc, char **argv){
    if (argc <= 1) return -1;
    f = open(argv[1],O_RDONLY);
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
    alarm(1);
    printf("Father");
    readstr();
    signal(SIGUSR1, handler1);
    kill(son,SIGUSR1);  
    pause();  
    while (N)pause();
    exit(0);
}