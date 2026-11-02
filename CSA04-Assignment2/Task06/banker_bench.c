#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
static double now(void){struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return t.tv_sec+t.tv_nsec/1e9;}
static int safe(int n,int m,int *avail,int *maxm,int *alloc){
    int *work=malloc((size_t)m*sizeof(int));int *finish=calloc((size_t)n,sizeof(int));
    if(!work||!finish){free(work);free(finish);return 0;}
    for(int r=0;r<m;r++)work[r]=avail[r];
    int done=0;
    while(done<n){int found=0;
        for(int p=0;p<n;p++)if(!finish[p]){
            int ok=1;for(int r=0;r<m;r++)if(maxm[p*m+r]-alloc[p*m+r]>work[r])ok=0;
            if(ok){for(int r=0;r<m;r++)work[r]+=alloc[p*m+r];finish[p]=1;done++;found=1;}
        }
        if(!found){free(work);free(finish);return 0;}
    }
    free(work);free(finish);return 1;
}
int main(void){
    const int sizes[]={10,100,1000};const int m=3;
    for(int z=0;z<3;z++){
        int n=sizes[z];int *a=calloc(m,sizeof(int));int *mx=calloc((size_t)n*m,sizeof(int));int *al=calloc((size_t)n*m,sizeof(int));
        for(int p=0;p<n;p++)for(int r=0;r<m;r++){mx[p*m+r]=1;al[p*m+r]=0;}
        a[0]=n;a[1]=n;a[2]=n;
        double t=now();int result=safe(n,m,a,mx,al);double elapsed=now()-t;
        printf("n=%d m=%d safe=%d elapsed=%.9f s\n",n,m,result,elapsed);
        free(a);free(mx);free(al);
    }
}
