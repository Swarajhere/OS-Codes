#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 12345
#define SHM_SIZE 1024

int main()
{
	int shmid;
	char *shm_ptr;
	char input[SHM_SIZE];

	// Create shared memory segment
	shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
	if (shmid < 0)
	{
		perror("shmget");
		exit(1);
	}

	// Attach to shared memory segment
	shm_ptr = (char *)shmat(shmid, NULL, 0);
	if (shm_ptr == (char *)-1)
	{
		perror("shmat");
		exit(1);
	}

	// Get user input
	printf("Server: Enter a message to write to shared memory: ");
	fgets(input, SHM_SIZE, stdin);
	input[strcspn(input, "\n")] = '\0'; // Remove the trailing newline

	// Write user input to shared memory
	strcpy(shm_ptr, input);
	printf("Server: Message written to shared memory.\n");

	// Wait for the client to read the message
	while (*shm_ptr != '*')
		sleep(1);

	printf("Server: Client has read the message.\n");

	// Detach and remove shared memory segment
	shmdt(shm_ptr);
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
