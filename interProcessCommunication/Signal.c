#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void handle_signal(int sig) {
    printf("Received signal %d, from my parent %d\n", sig, getppid());
    exit(1); //graceful exit.
}

void first_child() {
    printf("First child: printing message and exiting with code 0\n");
    exit(0);
}

void infinite_loop() {
    signal(SIGUSR1, handle_signal); //receive SIGUSR1 -> run the handle signal code.
    while (1) {
        printf("Child %d in infinite loop...\n", getpid());
        sleep(2); // Avoid overcrowding terminal
    }
}

int main() {
    pid_t pid1, pid2, pid3;

    // Create first child process
    pid1 = fork();
    if (pid1 == 0) {
        first_child();
    }

    // Create second child process
    pid2 = fork();
    if (pid2 == 0) {
        infinite_loop();
    }

    // Create third child process
    pid3 = fork();
    if (pid3 == 0) {
        infinite_loop();
    }

    // Parent process waits for 6 seconds
    sleep(6);

    // Send SIGUSR1 to both children in infinite loop
    kill(pid2, SIGUSR1);
    kill(pid3, SIGUSR1);

    wait(NULL);  //NULL - the parent does not care about the child process exit status.
    wait(NULL);  
    wait(NULL);  

    printf("Parent: All children have exited.\n");

    return 0;
}
