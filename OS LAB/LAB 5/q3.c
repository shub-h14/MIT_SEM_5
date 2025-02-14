#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<limits.h>

void main() {
    int status;
    pid_t pid;
    pid = fork();
    if(pid == -1)
        printf("\nERROR child not created");
    else if (pid == 0){
        printf("\nI'm the child!");
        printf("\npid is %d\nppid is %d\n", getpid(), getppid());
        exit(0);
    }
    else{
        wait(&status);
        printf("\nI'm the parent!");
        printf("\npid is %d\nppid is %d\n", getpid(), getppid());
    }
}