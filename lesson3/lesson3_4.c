#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

void run_orphan() {
    pid_t pid = fork();
    if (pid > 0) {
        printf("Parent (Orphan demo) exiting, PID=%d\n", getpid());
        exit(0);
    } else if (pid == 0) {
        printf("Child (Orphan demo), PID=%d\n", getpid());
        for (int i = 0; i < 5; i++) {
            printf("Child: my PPID=%d\n", getppid());
            sleep(2);
        }
    }
}

int main() {
    run_orphan();
    return 0;
}