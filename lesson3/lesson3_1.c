#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    pid_t child_pid;

    // Tạo tiến trình con
    pid = fork();

    if (pid == 0) {
        // --- Child ---
        printf("Child process: PID = %d\n", getpid());
        exit(10);
    } 
    else {
        // Parent and child
        pid_t child_pid = wait(&status);
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), child_pid);

        if (WIFEXITED(status)) {
            printf("Child exited normally with exit code = %d\n", WEXITSTATUS(status));
        } else {
            printf("Child did not exit normally\n");
        }
    }

    return 0;
}