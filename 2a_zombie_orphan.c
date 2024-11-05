#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Zombie Process Demonstration
void demonstrateZombie()
{
  pid_t pid = fork();

  if (pid < 0)
  {
    fprintf(stderr, "Fork failed\n");
    exit(1);
  }
  else if (pid == 0)
  {
    // Child process
    printf("Child process (PID: %d) exiting to create zombie process.\n", getpid());
    exit(0);
  }
  else
  {
    // Parent process
    printf("Parent process (PID: %d) sleeping to create zombie process.\n", getpid());
    sleep(10);  // Sleep for 10 seconds to give time to observe the zombie process
    wait(NULL); // Clean up the zombie process
    printf("Parent process (PID: %d) cleaned up zombie process.\n", getpid());
  }
}

/*void demonstrateZombie()
{
  pid_t pid = fork();

  if (pid < 0)
  {
    fprintf(stderr, "Fork failed\n");
    exit(1);
  }
  else if (pid == 0)
  {
    // Child process
    printf("Child process (PID: %d) is running\n", getpid());
    printf("Child process is exiting\n");
    exit(0); // Child exits, creating a zombie
  }
  else
  {
    // Parent process
    printf("Parent process (PID: %d) is running\n", getpid());
    printf("Child process (PID: %d) will become a zombie\n", pid);

    // Parent process enters infinite loop, keeping child as zombie
    while (1)
    {
      sleep(1); // Sleep to reduce CPU usage
    }
  }
} */

// Orphan Process Demonstration
void demonstrateOrphan()
{
  pid_t pid = fork();

  if (pid < 0)
  {
    fprintf(stderr, "Fork failed\n");
    exit(1);
  }
  else if (pid == 0)
  {
    // Child process
    printf("Child process (PID: %d) is running\n", getpid());
    printf("Parent process (PID: %d) will exit soon\n", getppid());
    sleep(2); // Ensure parent exits first
    printf("Child's parent PID after parent exits: %d\n", getppid());
    printf("Child process (now orphan) is exiting\n");
    exit(0);
  }
  else
  {
    // Parent process
    printf("Parent process (PID: %d) is running\n", getpid());
    printf("Parent process is exiting without waiting\n");
    exit(0); // Parent exits without waiting, child becomes orphan
  }
}

int main()
{
  int choice;

  while (1)
  {
    printf("\nProcess State Demonstration\n");
    printf("1. Demonstrate Zombie Process\n");
    printf("2. Demonstrate Orphan Process\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      printf("\n--- Zombie Process Demonstration ---\n");
      demonstrateZombie();
      break;

    case 2:
      printf("\n--- Orphan Process Demonstration ---\n");
      demonstrateOrphan();
      break;

    case 3:
      printf("Exiting program\n");
      exit(0);

    default:
      printf("Invalid choice\n");
    }
  }

  return 0;
}