// #include <stdio.h>
// #include <stdlib.h>
// #include <semaphore.h>
// #include <pthread.h>
// #include <unistd.h>

// #define BUFFER_SIZE 5 // Define buffer size

// // Shared buffer structure
// typedef struct
// {
//     int in, out, buffer[BUFFER_SIZE];
//     sem_t full, empty;    // Counting semaphores
//     pthread_mutex_t lock; // Mutex for mutual exclusion
// } BUFFER;

// BUFFER b1;    // Global buffer
// int item = 1; // Item counter

// // Function declarations
// void init();
// void *producer(void *num);
// void *consumer(void *num);

// int main()
// {
//     int np, nc;

//     printf("Enter the number of Producers: ");
//     scanf("%d", &np);
//     printf("Enter the number of Consumers: ");
//     scanf("%d", &nc);

//     init(); // Initialize semaphores and mutex

//     pthread_t producers[np], consumers[nc];

//     // Create producer threads
//     for (int i = 0; i < np; i++)
//     {
//         pthread_create(&producers[i], NULL, producer, (void *)&i);
//         printf("Producer thread %d created.\n", i);
//     }

//     // Create consumer threads
//     for (int i = 0; i < nc; i++)
//     {
//         pthread_create(&consumers[i], NULL, consumer, (void *)&i);
//         printf("Consumer thread %d created.\n", i);
//     }

//     // Wait for all threads to finish (optional in an infinite loop model)
//     for (int i = 0; i < np; i++)
//     {
//         pthread_join(producers[i], NULL);
//     }
//     for (int i = 0; i < nc; i++)
//     {
//         pthread_join(consumers[i], NULL);
//     }

//     return 0;
// }

// // Initialize buffer, semaphores, and mutex
// void init()
// {
//     b1.in = b1.out = 0;
//     sem_init(&b1.empty, 0, BUFFER_SIZE); // Buffer empty slots
//     sem_init(&b1.full, 0, 0);            // Buffer filled slots
//     pthread_mutex_init(&b1.lock, NULL);  // Initialize mutex
// }

// // Producer function
// void *producer(void *num)
// {
//     int id = *(int *)num;
//     while (1)
//     {
//         int sleep_time = rand() % 10 + 1;
//         sleep(sleep_time); // Simulate production time

//         sem_wait(&b1.empty);          // Wait for empty slot
//         pthread_mutex_lock(&b1.lock); // Enter critical section

//         // Produce an item
//         b1.buffer[b1.in] = item++;
//         printf("Producer %d produced item %d\n", id, b1.buffer[b1.in]);
//         b1.in = (b1.in + 1) % BUFFER_SIZE;

//         pthread_mutex_unlock(&b1.lock); // Leave critical section
//         sem_post(&b1.full);             // Signal that buffer has new item
//     }
// }

// // Consumer function
// void *consumer(void *num)
// {
//     int id = *(int *)num;
//     while (1)
//     {
//         int sleep_time = rand() % 10 + 1;
//         sleep(sleep_time); // Simulate consumption time

//         sem_wait(&b1.full);           // Wait for filled slot
//         pthread_mutex_lock(&b1.lock); // Enter critical section

//         // Consume an item
//         int consumed_item = b1.buffer[b1.out];
//         printf("Consumer %d consumed item %d\n", id, consumed_item);
//         b1.out = (b1.out + 1) % BUFFER_SIZE;

//         pthread_mutex_unlock(&b1.lock); // Leave critical section
//         sem_post(&b1.empty);            // Signal that buffer has an empty slot
//     }
// }
// /*
//             Expected Output
// Enter the number of Producers: 2
// Enter the number of Consumers: 2
// Producer thread 0 created.
// Producer thread 1 created.
// Consumer thread 0 created.
// Consumer thread 1 created.
// Producer 0 produced item 1
// Producer 1 produced item 2
// Consumer 0 consumed item 1
// Producer 0 produced item 3
// Consumer 1 consumed item 2
// Producer 1 produced item 4
// Consumer 0 consumed item 3

// */




// ------------------------------------------------------------------------------------------------------------------------------ //



#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Define buffer size

// Global buffer variables
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int item = 1; // Item counter

// Semaphores and mutex for synchronization
sem_t full, empty;
pthread_mutex_t lock;

// Function declarations
void init();
void *producer(void *num);
void *consumer(void *num);

int main() {
    int np, nc;

    printf("Enter the number of Producers: ");
    scanf("%d", &np);
    printf("Enter the number of Consumers: ");
    scanf("%d", &nc);

    init(); // Initialize semaphores and mutex

    pthread_t producers[np], consumers[nc];

    // Create producer threads
    for (int i = 0; i < np; i++) {
        pthread_create(&producers[i], NULL, producer, (void *)&i);
        printf("Producer thread %d created.\n", i);
    }

    // Create consumer threads
    for (int i = 0; i < nc; i++) {
        pthread_create(&consumers[i], NULL, consumer, (void *)&i);
        printf("Consumer thread %d created.\n", i);
    }

    // Wait for all threads to finish (optional in an infinite loop model)
    for (int i = 0; i < np; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < nc; i++) {
        pthread_join(consumers[i], NULL);
    }

    return 0;
}

// Initialize buffer, semaphores, and mutex
void init() {
    sem_init(&empty, 0, BUFFER_SIZE); // Buffer empty slots
    sem_init(&full, 0, 0);            // Buffer filled slots
    pthread_mutex_init(&lock, NULL);   // Initialize mutex
}

// Producer function
void *producer(void *num) {
    int id = *(int *)num;
    while (1) {
        int sleep_time = rand() % 10 + 1;
        sleep(sleep_time); // Simulate production time

        sem_wait(&empty);          // Wait for empty slot
        pthread_mutex_lock(&lock); // Enter critical section

        // Produce an item
        buffer[in] = item++;
        printf("Producer %d produced item %d\n", id, buffer[in]);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&lock); // Leave critical section
        sem_post(&full);             // Signal that buffer has new item
    }
}

// Consumer function
void *consumer(void *num) {
    int id = *(int *)num;
    while (1) {
        int sleep_time = rand() % 10 + 1;
        sleep(sleep_time); // Simulate consumption time

        sem_wait(&full);           // Wait for filled slot
        pthread_mutex_lock(&lock); // Enter critical section

        // Consume an item
        int consumed_item = buffer[out];
        printf("Consumer %d consumed item %d\n", id, consumed_item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&lock); // Leave critical section
        sem_post(&empty);            // Signal that buffer has an empty slot
    }
}
