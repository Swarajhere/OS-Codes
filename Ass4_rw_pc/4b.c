#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_THREADS 10 // Maximum number of reader/writer threads

int readCount = 0;              // Number of active readers
int sharedVar = 0;              // Shared resource
sem_t writerSem;                // Semaphore to control write access
pthread_mutex_t readCountMutex; // Mutex for readCount variable

// Reader function
void *readerFunc(void *args)
{
    while (1)
    {
        pthread_mutex_lock(&readCountMutex); // Lock before updating readCount
        readCount++;
        if (readCount == 1)
        {
            // First reader locks the writer semaphore to prevent writing
            sem_wait(&writerSem);
        }
        pthread_mutex_unlock(&readCountMutex); // Unlock after updating readCount

        // Reading section
        printf("Reader reads sharedVar = %d\n", sharedVar);
        sleep(1); // Simulate read time

        pthread_mutex_lock(&readCountMutex); // Lock before updating readCount
        readCount--;
        if (readCount == 0)
        {
            // Last reader unlocks the writer semaphore
            sem_post(&writerSem);
        }
        pthread_mutex_unlock(&readCountMutex); // Unlock after updating readCount

        sleep(1); // Let other threads run
    }
}

// Writer function
void *writerFunc(void *args)
{
    while (1)
    {
        sem_wait(&writerSem); // Wait for writer semaphore to get write access

        // Writing section
        sharedVar++; // Update the shared resource
        printf("Writer updated sharedVar to %d\n", sharedVar);
        sleep(1); // Simulate write time

        sem_post(&writerSem); // Release writer semaphore after writing
        sleep(1);             // Let other threads run
    }
}

int main()
{
    int numReaders, numWriters;

    // Initialize semaphore and mutex
    sem_init(&writerSem, 0, 1);
    pthread_mutex_init(&readCountMutex, NULL);

    // Get the number of reader and writer threads from user
    printf("Enter the number of readers: ");
    scanf("%d", &numReaders);
    printf("Enter the number of writers: ");
    scanf("%d", &numWriters);

    pthread_t readers[MAX_THREADS], writers[MAX_THREADS];

    // Create writer threads
    for (int i = 0; i < numWriters; i++)
    {
        pthread_create(&writers[i], NULL, writerFunc, NULL);
        printf("Writer thread %d created.\n", i + 1);
    }

    // Create reader threads
    for (int i = 0; i < numReaders; i++)
    {
        pthread_create(&readers[i], NULL, readerFunc, NULL);
        printf("Reader thread %d created.\n", i + 1);
    }

    // Wait for all reader and writer threads to complete (optional in infinite loop)
    for (int i = 0; i < numReaders; i++)
    {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < numWriters; i++)
    {
        pthread_join(writers[i], NULL);
    }

    // Cleanup
    sem_destroy(&writerSem);
    pthread_mutex_destroy(&readCountMutex);

    return 0;
}

/*
            Expected output
Enter the number of readers: 3
Enter the number of writers: 2

Writer thread 1 created.
Writer thread 2 created.
Reader thread 1 created.
Reader thread 2 created.
Reader thread 3 created.

Reader reads sharedVar = 0
Reader reads sharedVar = 0
Reader reads sharedVar = 0

Writer updated sharedVar to 1

Reader reads sharedVar = 1
Reader reads sharedVar = 1
Reader reads sharedVar = 1

Writer updated sharedVar to 2

Reader reads sharedVar = 2
Reader reads sharedVar = 2
Reader reads sharedVar = 2

*/
