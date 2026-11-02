#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
int main(void) {
    int fd[2]; if(pipe(fd)==-1){perror("pipe");return 1;}
    pid_t pid=fork(); if(pid<0){perror("fork");return 1;}
    if(pid==0){
        close(fd[1]); int r,count=0,sum=0,max=0;
        while(1){
            ssize_t n=read(fd[0],&r,sizeof r);
            if(n==0)break;
            if(n<0){if(errno==EINTR)continue;perror("read");_exit(2);}
            if(n!=(ssize_t)sizeof r){fprintf(stderr,"partial integer read\n");_exit(3);}
            if(count==0||r>max)max=r;sum+=r;count++;
        }
        printf("analyser: %d readings, average %.1f, max %d\n",count,count?(double)sum/count:0.0,max);
        close(fd[0]);fflush(stdout);_exit(0);
    }
    close(fd[0]); int readings[]={31,33,36,34,41,38};
    for(int i=0;i<6;i++)if(write(fd[1],&readings[i],sizeof readings[i])!=(ssize_t)sizeof readings[i])perror("write");
    close(fd[1]); waitpid(pid,NULL,0); puts("reader: done");return 0;
}
