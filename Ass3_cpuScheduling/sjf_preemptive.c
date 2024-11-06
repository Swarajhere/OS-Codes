// ----------------------------------------------------------------
// with inclusion of completion time column
#include <stdio.h>
#include <stdlib.h>

int arrival_time[10], burst_time[10], waiting_time[10], TAT[10];
int completion_time[10], finish[10], process_name[10], remaining_burst_time[10];
int n, curr_time = 0, pending;

void input()
{
	printf("\nEnter the number of processes: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		process_name[i] = i + 1; // process names will be P1, P2, etc.
		printf("\nEnter arrival time of process %d: ", process_name[i]);
		scanf("%d", &arrival_time[i]);
		printf("Enter burst time of process %d: ", process_name[i]);
		scanf("%d", &burst_time[i]);
		remaining_burst_time[i] = burst_time[i];
		finish[i] = 0;
	}
}

int find_next_process()
{
	int shortest = -1;
	for (int i = 0; i < n; i++)
	{
		if (!finish[i] && arrival_time[i] <= curr_time) // arrival_time[i] <= curr_time && finish[i] == 0
		{
			if (shortest == -1 || remaining_burst_time[i] < remaining_burst_time[shortest])
			{
				shortest = i;
			}
		}
	}
	return shortest;
}

void SJF_preemptive()
{
	input();
	pending = n;
	printf("\n\nGantt Chart:\n");

	while (pending > 0)
	{
		int p = find_next_process();
		if (p == -1)
		{
			curr_time++;
			continue;
		}

		printf("P%d || ", process_name[p]);
		remaining_burst_time[p]--;
		curr_time++;

		if (remaining_burst_time[p] == 0)
		{
			finish[p] = 1;
			pending--;
			completion_time[p] = curr_time; // record completion time
			TAT[p] = completion_time[p] - arrival_time[p];
			waiting_time[p] = TAT[p] - burst_time[p];
		}
	}

	int total_waiting_time = 0, total_TAT = 0;
	printf("\n\nProcess\tBurst Time\tArrival Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
	for (int i = 0; i < n; i++)
	{
		total_waiting_time += waiting_time[i];
		total_TAT += TAT[i];
		printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process_name[i], burst_time[i], arrival_time[i], completion_time[i], waiting_time[i], TAT[i]);
	}

	printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
	printf("\nAverage Turnaround Time: %.2f\n", (float)total_TAT / n);
}

int main()
{
	SJF_preemptive();
	return 0;
}
