#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

int main(void) {
    int numsons = 0; 
    int parentid = getpid();
    printf("How many sons do you want to have: "); 
    scanf("%d", &numsons);
    
    for (int i = 1; i < numsons; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            printf("I am the son process with ID: %d\n", getpid());
            exit(i); // Exit with the index as the status
        } else if (pid < 0) {
            // Fork failed
            perror("Fork failed");
            exit(1);
        }
    }

    if (getpid() == parentid) {
        // Parent process
        for (int i = 1; i <= numsons; i++) {
            int status = 0;
            pid_t pid = wait(&status);
            if (pid > 0) {
                if (WIFEXITED(status)) {
                    printf("Son with PID %d exited with status: %d\n", pid, WEXITSTATUS(status));
                }
            }else{
                return 0;
            }
        }
        printf("All sons finished.\n");
    }

    return 0;
}
