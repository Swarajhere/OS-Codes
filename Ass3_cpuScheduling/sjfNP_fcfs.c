#include <stdio.h>

#define MAX_PROCESSES 50

// Global Variables
int n;                             // Number of processes
int arrivalTime[MAX_PROCESSES];    // Arrival times of processes
int burstTime[MAX_PROCESSES];      // Burst times of processes
int waitingTime[MAX_PROCESSES];    // Waiting times of processes
int turnaroundTime[MAX_PROCESSES]; // Turnaround times of processes

// Function to calculate waiting and turnaround times for FCFS scheduling
void fcfs()
{
  int completionTime[MAX_PROCESSES];
  completionTime[0] = arrivalTime[0] + burstTime[0];
  turnaroundTime[0] = completionTime[0] - arrivalTime[0];
  waitingTime[0] = turnaroundTime[0] - burstTime[0];

  for (int i = 1; i < n; i++)
  {
    if (arrivalTime[i] > completionTime[i - 1])
    {
      completionTime[i] = arrivalTime[i] + burstTime[i];
    }
    else
    {
      completionTime[i] = completionTime[i - 1] + burstTime[i];
    }
    turnaroundTime[i] = completionTime[i] - arrivalTime[i];
    waitingTime[i] = turnaroundTime[i] - burstTime[i];
  }

  printf("\nFCFS Scheduling:\n");
  printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
  for (int i = 0; i < n; i++)
  {
    printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrivalTime[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
  }
}

// Function to calculate waiting and turnaround times for SJF Non-Preemptive scheduling
void sjf()
{
  int completed[MAX_PROCESSES] = {0};
  int time = 0, completedCount = 0;

  while (completedCount < n)
  {
    int shortestJob = -1;
    for (int i = 0; i < n; i++)
    {
      if (!completed[i] && arrivalTime[i] <= time)
      {
        if (shortestJob == -1 || burstTime[i] < burstTime[shortestJob])
        {
          shortestJob = i;
        }
      }
    }

    if (shortestJob == -1)
    {
      time++;
      continue;
    }

    time += burstTime[shortestJob];
    waitingTime[shortestJob] = time - arrivalTime[shortestJob] - burstTime[shortestJob];
    turnaroundTime[shortestJob] = time - arrivalTime[shortestJob];
    completed[shortestJob] = 1;
    completedCount++;
  }

  printf("\nSJF Non-Preemptive Scheduling:\n");
  printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
  for (int i = 0; i < n; i++)
  {
    printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrivalTime[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
  }
}

// Function to get process details from the user
void inputProcesses()
{
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  printf("Enter the Arrival Time and Burst Time for each process:\n");
  for (int i = 0; i < n; i++)
  {
    printf("Process %d:\n", i + 1);
    printf("Arrival Time: ");
    scanf("%d", &arrivalTime[i]);
    printf("Burst Time: ");
    scanf("%d", &burstTime[i]);
  }
}

// Main function
int main()
{
  inputProcesses();

  fcfs();
  sjf();

  return 0;
}
