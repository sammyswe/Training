#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(void){
    pid_t pid = fork();

    if(pid == 0){
        int Y = getpid();
        printf("I am the son process %d\n", Y);
        exit(2); 
    }
    else{
        int status = 1;
        pid_t code = wait(&status);
        printf("Status: %d\n", WEXITSTATUS(status));

    }

}