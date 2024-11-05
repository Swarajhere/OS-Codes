// Client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHM_KEY 12345
#define SHM_SIZE 1024

int main()
{
    int shmid;
    char *shm_ptr;

    // Attach to the shared memory segment created by the server
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // Read and display the message from shared memory
    printf("Client: Message from shared memory: %s\n", shm_ptr);

    // Signal the server that the message has been read
    *shm_ptr = '*';

    // Detach from shared memory
    shmdt(shm_ptr);
    return 0;
}