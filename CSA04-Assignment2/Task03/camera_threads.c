#define _POSIX_C_SOURCE 200809L
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CAMERAS 64
#define FRAMES 40000
static volatile unsigned long long sink;
typedef struct { int start, end; } Job;
static void work(int camera) {
    unsigned long long x=(unsigned long long)camera+1;
    for (int i=0;i<FRAMES;i++) x=(x*1664525ULL+1013904223ULL) ^ (unsigned long long)i;
    __atomic_fetch_add(&sink,x,__ATOMIC_RELAXED);
}
static void *one_camera(void *v) { int c=*(int*)v; work(c); return NULL; }
static int next_camera;
static pthread_mutex_t next_lock=PTHREAD_MUTEX_INITIALIZER;
static void *worker(void *unused) {
    (void)unused;
    for (;;) {
        pthread_mutex_lock(&next_lock);
        int c=next_camera++;
        pthread_mutex_unlock(&next_lock);
        if(c>=CAMERAS) break;
        work(c);
    }
    return NULL;
}
static double now(void){struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return t.tv_sec+t.tv_nsec/1e9;}
int main(void) {
    double t=now(); for(int c=0;c<CAMERAS;c++) work(c);
    double serial=now()-t; printf("serial: %.6f s\n",serial);
    for(int n=4;n<=16;n*=2) {
        pthread_t th[CAMERAS]; int ids[CAMERAS];
        t=now();
        for(int c=0;c<CAMERAS;c++){ids[c]=c;pthread_create(&th[c],NULL,one_camera,&ids[c]);}
        for(int c=0;c<CAMERAS;c++)pthread_join(th[c],NULL);
        double elapsed=now()-t;
        printf("one-thread-per-camera (64): %.6f s, speedup %.2fx\n",elapsed,serial/elapsed);
        break;
    }
    for(int n=4;n<=16;n*=2) {
        pthread_t th[16]; next_camera=0; t=now();
        for(int i=0;i<n;i++)pthread_create(&th[i],NULL,worker,NULL);
        for(int i=0;i<n;i++)pthread_join(th[i],NULL);
        double elapsed=now()-t;
        printf("pool %2d: %.6f s, speedup %.2fx\n",n,elapsed,serial/elapsed);
    }
    printf("checksum=%llu\n",sink);
    return 0;
}
