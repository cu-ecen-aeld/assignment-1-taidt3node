#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void run_zombie() {
    pid_t pid = fork();
    if (pid > 0) {
        printf("Parent (Zombie demo), PID=%d\n", getpid());
        sleep(20); // parent doesn't wait
    } else if (pid == 0) {
        printf("Child (Zombie demo) exiting, PID=%d\n", getpid());
        exit(0);
    }
}

int main() {
    run_zombie();
    return 0;
}