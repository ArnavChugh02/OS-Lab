#include <stdio.h>
#include <unistd.h>  // For fork(), getpid(), getppid()
#include <sys/types.h>  // For pid_t

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Child Process:\n");
        printf("PID (Process ID): %d\n", getpid());
        printf("PPID (Parent Process ID): %d\n", getppid());
    } 
    else {
        printf("Parent Process:\n");
        printf("PID (Process ID): %d\n", getpid());
        printf("PPID (Parent Process ID): %d\n", getppid());
    }

    return 0;
}

