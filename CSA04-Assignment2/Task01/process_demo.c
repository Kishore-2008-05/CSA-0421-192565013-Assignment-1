#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    if (pid == 0) {
        printf("child: pid=%ld ppid=%ld\n", (long)getpid(), (long)getppid());
        printf("child: inspect /proc/%ld/status while this process is alive\n", (long)getpid());
        sleep(3);
        _exit(0);
    }
    printf("parent: pid=%ld child=%ld\n", (long)getpid(), (long)pid);
    char cmd[128];
    snprintf(cmd, sizeof cmd, "ps -o pid,ppid,stat,comm -p %ld,%ld", (long)getpid(), (long)pid);
    (void)system(cmd);
    int status = 0;
    waitpid(pid, &status, 0);
    printf("parent: child exit=%d\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);
    return 0;
}
