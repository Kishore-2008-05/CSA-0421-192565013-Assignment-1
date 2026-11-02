#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>

#define COUNT 1000

static double seconds_between(struct timespec a, struct timespec b) {
    return (double)(b.tv_sec-a.tv_sec) + (double)(b.tv_nsec-a.tv_nsec)/1e9;
}
static void *thread_fn(void *arg) { (void)arg; return NULL; }

int main(void) {
    struct timespec a,b;
    clock_gettime(CLOCK_MONOTONIC, &a);
    for (int i=0; i<COUNT; i++) {
        pid_t p=fork();
        if (p<0) { perror("fork"); return 1; }
        if (p==0) _exit(0);
        int st;
        if (waitpid(p,&st,0)<0) { perror("waitpid"); return 1; }
    }
    clock_gettime(CLOCK_MONOTONIC, &b);
    printf("Created and reaped %d processes: %.6f seconds\n", COUNT, seconds_between(a,b));

    pthread_t t[COUNT];
    clock_gettime(CLOCK_MONOTONIC, &a);
    for (int i=0; i<COUNT; i++) {
        int e=pthread_create(&t[i],NULL,thread_fn,NULL);
        if (e) { errno=e; perror("pthread_create"); return 1; }
    }
    for (int i=0; i<COUNT; i++) {
        int e=pthread_join(t[i],NULL);
        if (e) { errno=e; perror("pthread_join"); return 1; }
    }
    clock_gettime(CLOCK_MONOTONIC, &b);
    printf("Created and joined %d threads:  %.6f seconds\n", COUNT, seconds_between(a,b));
    return 0;
}
