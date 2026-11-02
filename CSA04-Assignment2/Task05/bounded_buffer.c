#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define SIZE 5
#define ITEMS 20
#define MAXT 16
static int buffer[SIZE], in=0, out=0;
static sem_t empty_slots, full_slots;
static pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
static long consumed_sum=0;
static int producers=1, consumers=1, next_item=1;
static void *producer(void *arg){
    (void)arg;
    for(;;){
        pthread_mutex_lock(&lock);
        int item=next_item++;
        pthread_mutex_unlock(&lock);
        if(item>ITEMS)break;
        sem_wait(&empty_slots);
        pthread_mutex_lock(&lock);
        buffer[in]=item;in=(in+1)%SIZE;
        pthread_mutex_unlock(&lock);
        sem_post(&full_slots);
    }
    return NULL;
}
static void enqueue(int item){
    sem_wait(&empty_slots);
    pthread_mutex_lock(&lock);
    buffer[in]=item;in=(in+1)%SIZE;
    pthread_mutex_unlock(&lock);
    sem_post(&full_slots);
}
static void *consumer(void *arg){
    (void)arg;
    for(;;){
        sem_wait(&full_slots);
        pthread_mutex_lock(&lock);
        int item=buffer[out];out=(out+1)%SIZE;
        pthread_mutex_unlock(&lock);
        sem_post(&empty_slots);
        if(item==-1)break;
        pthread_mutex_lock(&lock);
        consumed_sum+=item;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
int main(int argc,char **argv){
    if(argc>1)producers=atoi(argv[1]);
    if(argc>2)consumers=atoi(argv[2]);
    if(producers<1||producers>MAXT||consumers<1||consumers>MAXT){fprintf(stderr,"use 1..16 producers and consumers\n");return 2;}
    pthread_t p[MAXT],c[MAXT];
    sem_init(&empty_slots,0,SIZE);sem_init(&full_slots,0,0);
    for(int i=0;i<consumers;i++)pthread_create(&c[i],NULL,consumer,NULL);
    for(int i=0;i<producers;i++)pthread_create(&p[i],NULL,producer,NULL);
    for(int i=0;i<producers;i++)pthread_join(p[i],NULL);
    for(int i=0;i<consumers;i++)enqueue(-1);
    for(int i=0;i<consumers;i++)pthread_join(c[i],NULL);
    printf("items consumed: %d, sum = %ld (expected %d)\n",ITEMS,consumed_sum,ITEMS*(ITEMS+1)/2);
    sem_destroy(&empty_slots);sem_destroy(&full_slots);
    return consumed_sum==210?0:1;
}
