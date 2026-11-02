#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <string.h>
typedef struct { sem_t ready; int values[6]; int count; } Shared;
int main(void) {
    const char *name="/os_a2_weather_shm";
    int fd=shm_open(name,O_CREAT|O_RDWR,0600); if(fd<0){perror("shm_open");return 1;}
    if(ftruncate(fd,sizeof(Shared))<0){perror("ftruncate");return 1;}
    Shared *s=mmap(NULL,sizeof(Shared),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(s==MAP_FAILED){perror("mmap");return 1;}
    memset(s,0,sizeof(*s)); sem_init(&s->ready,1,0);
    pid_t p=fork();
    if(p==0){
        sem_wait(&s->ready); int sum=0,max=0;
        for(int i=0;i<s->count;i++){sum+=s->values[i];if(i==0||s->values[i]>max)max=s->values[i];}
        printf("shared-memory analyser: %d readings, average %.1f, max %d\n",s->count,s->count?(double)sum/s->count:0.0,max);
        fflush(stdout);_exit(0);
    }
    int vals[]={31,33,36,34,41,38};s->count=6;
    memcpy(s->values,vals,sizeof vals);sem_post(&s->ready);waitpid(p,NULL,0);
    puts("shared-memory reader: done");
    sem_destroy(&s->ready);munmap(s,sizeof(*s));close(fd);shm_unlink(name);return 0;
}
