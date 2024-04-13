#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define NUM_READERS 3
#define NUM_WRITERS 2
#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int num_items = 0;

int sem_id;
struct sembuf sops;

void reader(int id);
void writer(int id);

int main()
{
    int i, pid;

    // Create semaphore
    sem_id = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    if (sem_id == -1) {
        perror("Error creating semaphore");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphore value
    if (semctl(sem_id, 0, SETVAL, 1) == -1) {
        perror("Error initializing semaphore");
        exit(EXIT_FAILURE);
    }

    // Create readers
    for (i = 0; i < NUM_READERS; i++) {
        pid = fork();
        if (pid == -1) {
            perror("Error creating reader");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            reader(i);
            exit(EXIT_SUCCESS);
        }
    }

    // Create writers
    for (i = 0; i < NUM_WRITERS; i++) {
        pid = fork();
        if (pid == -1) {
            perror("Error creating writer");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            writer(i);
            exit(EXIT_SUCCESS);
        }
    }

    // Wait for all child processes to finish
    for (i = 0; i < NUM_READERS + NUM_WRITERS; i++) {
        wait(NULL);
    }

    // Remove semaphore
    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        perror("Error removing semaphore");
        exit(EXIT_FAILURE);
    }

    return 0;
}

void reader(int id)
{
    int i, item;

    for (i = 0; i < 5; i++) {
        // Acquire read lock
        sops.sem_num = 0;
        sops.sem_op = -1;
        sops.sem_flg = 0;
        if (semop(sem_id, &sops, 1) == -1) {
            perror("Error acquiring read lock");
            exit(EXIT_FAILURE);
        }

        // Read from buffer
        item = buffer[num_items - 1];
        printf("Reader %d read item %d from buffer\n", id, item);

        // Release read lock
        sops.sem_num = 0;
        sops.sem_op = 1;
        sops.sem_flg = 0;
        if (semop(sem_id, &sops, 1) == -1) {
            perror("Error releasing read lock");
            exit(EXIT_FAILURE);
        }

        // Sleep for random amount of time
        usleep(rand() % 1000000);
    }
}

void writer(int id)
{
    int i, item;

    for (i = 0; i < 5; i++) {
        // Acquire write lock
        sops.sem_num = 0;
        sops.sem_op = -1;
        sops.sem_flg = 0;
        if (semop(sem_id, &sops, 1) == -1) {
            perror("Error acquiring write lock");
            exit(EXIT_FAILURE);
        }

        // Write
        item = rand() % 100;
    buffer[num_items++] = item;
    printf("Writer %d wrote item %d to buffer\n", id, item);

    // Release write lock
    sops.sem_num = 0;
    sops.sem_op = 1;
    sops.sem_flg = 0;
    if (semop(sem_id, &sops, 1) == -1) {
        perror("Error releasing write lock");
        exit(EXIT_FAILURE);
    }

    // Sleep for random amount of time
    usleep(rand() % 1000000);
}
}
