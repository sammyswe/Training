#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main (void){

    int fd [2],nbytes;
    pid_t childpid;
    char string[] = "Hello World \n";
    char readbuffer[80];

    pipe(fd);

    if((childpid = fork()) == -1){
        perror("fork");
        exit(1);
    }
    if (childpid ==0){ //child process closes read end of pipe
        close(fd[0]); //fd[0] is the read end
        write(fd[1], string, (strlen(string)+1));
        exit(0);
        
    }else{
        close(fd[1]);
        nbytes = read(fd[0], readbuffer,sizeof(readbuffer));
        printf("Received string: %s", readbuffer);
    }

    return 0;
}