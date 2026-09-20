#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t room;

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < 3; i++)
    {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        // Allow maximum N-1 philosophers to compete for forks
        sem_wait(&room);

        // Pick up left fork
        sem_wait(&forks[id]);
        printf("Philosopher %d picked up left fork.\n", id);

        // Pick up right fork
        sem_wait(&forks[(id + 1) % N]);
        printf("Philosopher %d picked up right fork.\n", id);

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(2);

        // Put down right fork
        sem_post(&forks[(id + 1) % N]);

        // Put down left fork
        sem_post(&forks[id]);

        // Leave room
        sem_post(&room);

        printf("Philosopher %d finished eating.\n\n", id);
    }

    return NULL;
}

int main()
{
    pthread_t philosophers[N];
    int id[N];

    // Initialize fork semaphores
    for (int i = 0; i < N; i++)
    {
        sem_init(&forks[i], 0, 1);
    }

    // Only 4 philosophers can compete for forks
    sem_init(&room, 0, N - 1);

    // Create philosopher threads
    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &id[i]);
    }

    // Wait for all philosophers
    for (int i = 0; i < N; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < N; i++)
    {
        sem_destroy(&forks[i]);
    }

    sem_destroy(&room);

    printf("All philosophers have finished eating.\n");

    return 0;
}

