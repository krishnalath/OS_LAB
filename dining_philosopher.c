#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define n 5
pthread_t philosophers[n];
pthread_mutex_t forks[n];

void* philosopher(void *num){
    int id = *(int*)num;
    int left = id;
    int right = (id+1)%n;
    while(1){
        printf("Philosopher %d is thinking\n",id);
        sleep(1);
        if(id%2==0){
            pthread_mutex_lock(&forks[left]);
            printf("philosopher %d picked up left fork %d\n",id,left);
            pthread_mutex_lock(&forks[right]);
            printf("philosopher %d picked up right fork %d\n",id,right);
        }
        else{
            pthread_mutex_lock(&forks[right]);
            printf("philosopher %d picked up right fork %d\n",id,right);
            pthread_mutex_lock(&forks[left]);
            printf("philosopher %d picked up left fork %d\n",id,left);
        }
        printf("Philosopher %d is eating\n",id);
        sleep(2);
        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
        printf("Philosopher %d put down forks %d and %d\n",id,left,right);
    }
    return NULL;
}

int main() {
    int i,ids[n];
    for(i=0;i<n;i++){
        pthread_mutex_init(&forks[i],NULL);
        ids[i]=i;
    }
    for(i=0;i<n;i++)
        pthread_create(&philosophers[i],NULL,philosopher,&ids[i]);
        
    for(i=0;i<n;i++)
        pthread_join(philosophers[i],NULL);
        
    for(i=0;i<n;i++)
        pthread_mutex_destroy(&forks[i]);

    return 0;
}
