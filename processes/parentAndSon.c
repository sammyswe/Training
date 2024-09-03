#include <stdio.h>
#include <unistd.h>

int main(void){


    pid_t pid = fork();
    
    
    if(pid ==0){
        printf("I am process number %d the son of process %d\n", getpid(), getppid());
    }else{
        printf("I am the father, my son is 0.\n");
    }

}