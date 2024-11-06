#include <stdio.h>
#include <stdlib.h>

// Define maximum sizes
#define MAX_PROCESSES 50
#define MAX_RESOURCES 50

// Declare global variables
int alloc[MAX_PROCESSES][MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES], need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES], done[MAX_PROCESSES];
int n, m;

// Function to calculate the safe sequence
int calculateSafeSequence(int n)
{
  for (int i = 0; i < n; i++)
    done[i] = 0;

  int processSeq[MAX_PROCESSES];
  int count = 0;
  int safe = 1;

  int work[MAX_RESOURCES];
  for (int i = 0; i < m; i++)
  {
    work[i] = available[i]; // Copy available resources
  }

  while (count < n)
  {
    safe = 0;
    for (int i = 0; i < n; i++)
    {
      if (done[i])
        continue;

      int canProceed = 1;
      for (int j = 0; j < m; j++)
      {
        if (need[i][j] > work[j])
        {
          canProceed = 0;
          break;
        }
      }

      if (canProceed)
      {
        processSeq[count++] = i;
        done[i] = 1;
        safe = 1;
        for (int k = 0; k < m; k++)
          work[k] += alloc[i][k];
      }
    }
    if (!safe)
      break;
  }

  if (safe)
  {
    printf("The safe sequence is:\n");
    for (int i = 0; i < count; i++)
      printf("P%d ", processSeq[i]);
    printf("\n");
  }
  else
  {
    printf("The system is not in a safe state.\n");
  }
  return safe;
}

int main()
{
  printf("Enter the initial number of processes: ");
  scanf("%d", &n);
  printf("Enter the number of resources: ");
  scanf("%d", &m);

  printf("Resources allocated:\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      scanf("%d", &alloc[i][j]);
    }
  }

  printf("Max resources required:\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      scanf("%d", &max[i][j]);
    }
  }

  printf("Available resources:\n");
  for (int i = 0; i < m; i++)
  {
    scanf("%d", &available[i]);
  }

  // Calculate the need matrix
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
      need[i][j] = max[i][j] - alloc[i][j];
  }

  // Calculate the initial safe sequence
  calculateSafeSequence(n);

  // Loop for adding new processes
  char addProcess;
  do
  {
    printf("Do you want to add a new process? (y/n): ");
    scanf(" %c", &addProcess);

    if (addProcess == 'y')
    {
      n++; // Increase process count for the new process

      printf("Enter allocated resources for the new process P%d:\n", n - 1);
      for (int j = 0; j < m; j++)
        scanf("%d", &alloc[n - 1][j]);

      printf("Enter maximum resources required for the new process P%d:\n", n - 1);
      for (int j = 0; j < m; j++)
        scanf("%d", &max[n - 1][j]);

      // Update the need matrix for the new process
      for (int j = 0; j < m; j++)
        need[n - 1][j] = max[n - 1][j] - alloc[n - 1][j];

      printf("Available resources after adding new process:\n");
      for (int i = 0; i < m; i++)
        printf("%d ", available[i]);
      printf("\n");

      // Calculate the new safe sequence
      calculateSafeSequence(n);
    }
  } while (addProcess == 'y');

  return 0;
}

/*
Enter the initial number of processes: 5
Enter the number of resources: 3
Resources allocated:
0 1 0
2 0 0
3 0 3
2 1 1
0 0 2
Max resources required:
6 4 3
4 2 2
7 1 5
3 2 2
4 3 3
Available resources:
3 2 1
The safe sequence is:
P3 P4 P1 P2 P0
Do you want to add a new process? (y/n): y
Enter allocated resources for the new process P5:
1 1 2
Enter maximum resources required for the new process P5:
3 4 3
Available resources after adding new process:
3 2 1
The safe sequence is:
P3 P4 P5 P0 P1 P2

*/


// ------------------------------------------------------------------------------------------------------------------------------------
// normal bankers ->>
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m;
    printf("Enter no of processes: ");
    scanf("%d", &n);
    printf("Enter no of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int available[m];

    printf("resources alloted\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("max resources required\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("available resources\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    int done[n];
    for (int i = 0; i < n; i++)
        done[i] = 0;
    int processSeq[n];
    int count = 0;
    int check[n];
    for (int i = 0; i < n; i++)
        check[i] = -1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (count == check[j])
            {
                printf("The following system is not safe\n");
                return 0;
            }
            check[j] = count;
            if (done[j])
                continue;
            int flag = 1;
            for (int k = 0; k < m; k++)
            {
                if (need[j][k] > available[k])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                processSeq[count] = j;
                count++;
                done[j] = 1;
                for (int k = 0; k < m; k++)
                {
                    available[k] += alloc[j][k];
                }
            }
        }
        if (count == n)
        {
            printf("The safe sequence is:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", processSeq[i]);
            }
            printf("\n");
            return 0;
        }
    }
}
*/
