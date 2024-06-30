#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 2
#define MaxCycles 2
int eating_cycles[NUM_PHILOSOPHERS];
sem_t forks[NUM_PHILOSOPHERS], mutex;
pthread_t philosophers[NUM_PHILOSOPHERS];
void * philosopher(void * arg) {
    int id = * ((int * ) arg);
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;
    int eatcount = 0;
    while (eatcount < MaxCycles) {
        printf("Philosopher %d has started thinking and is not
        eating\n", id); // Thinking
        sleep(rand() % 3 + 1);
        sem_wait( & mutex);
        // Pick up forks
        sem_wait( & forks[left_fork]);
        sem_wait( & forks[right_fork]);
        sem_post( & mutex);
        printf("Philosopher %d has stopped thinking and is eating\n",id); // Eating
        sleep(rand() % 3 + 1);
        eating_cycles[id]++;
        eatcount++;
        // Release forks
        sem_post( & forks[left_fork]);
        sem_post( & forks[right_fork]);
    }
    return NULL;
}
int main() {
    int i;
    srand(time(NULL));
    sem_init( & mutex, 0, 1);
    // Initialize forks
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init( & forks[i], 0, 1);
    }
    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        int * id = (int * ) malloc(sizeof(int));
        * id = i;
        pthread_create( & philosophers[i], NULL, philosopher, id);
    }
    // Join philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    sem_destroy( & mutex);
    // Destroy forks
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
        sem_destroy( & forks[i]);
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
        printf("Philosopher %d ate %d times\n", i, eating_cycles[i]);
    return 0;
}
