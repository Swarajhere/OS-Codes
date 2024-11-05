#include <stdio.h>

// Global variables
int arrival_time[10], burst_time[10], waiting_time[10], TAT[10], completion_time[10];
int remaining_burst_time[10], finish[10], process_name[10];
int n, curr_time = 0;

void input() {
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        process_name[i] = i + 1;
        printf("\nEnter arrival time of process %d: ", process_name[i]);
        scanf("%d", &arrival_time[i]);
        printf("Enter burst time of process %d: ", process_name[i]);
        scanf("%d", &burst_time[i]);
        remaining_burst_time[i] = burst_time[i];
        finish[i] = 0;
        waiting_time[i] = 0;
        TAT[i] = 0;
        completion_time[i] = 0;
    }
}

// Helper function to check if all processes are complete
int allProcessesComplete() {
    for (int i = 0; i < n; i++) {
        if (!finish[i]) return 0;
    }
    return 1;
}

void round_robin() {
    int time_quantum, queue[100], front = 0, rear = -1;
    input();
    
    printf("\nEnter time quantum: ");
    scanf("%d", &time_quantum);
    
    printf("\nGantt Chart:\n");
    
    // Add first process that arrives at 0 to queue
    for (int i = 0; i < n; i++) {
        if (arrival_time[i] == 0) {
            rear = (rear + 1) % 100;
            queue[rear] = i;
        }
    }
    
    while (front <= rear) {
        int i = queue[front];
        front = (front + 1) % 100;
        
        if (remaining_burst_time[i] > 0) {
            printf("P%d || ", process_name[i]);
            
            if (remaining_burst_time[i] <= time_quantum) {
                curr_time += remaining_burst_time[i];
                completion_time[i] = curr_time;
                remaining_burst_time[i] = 0;
                finish[i] = 1;
                
                // Calculate times
                TAT[i] = completion_time[i] - arrival_time[i];
                waiting_time[i] = TAT[i] - burst_time[i];
            } else {
                curr_time += time_quantum;
                remaining_burst_time[i] -= time_quantum;
            }
            
            // Add newly arrived processes to queue
            for (int j = 0; j < n; j++) {
                if (!finish[j] && arrival_time[j] <= curr_time && j != i) {
                    // Check if process is not already in queue
                    int in_queue = 0;
                    for (int k = front; k <= rear; k++) {
                        if (queue[k] == j) {
                            in_queue = 1;
                            break;
                        }
                    }
                    
                    if (!in_queue) {
                        rear = (rear + 1) % 100;
                        queue[rear] = j;
                    }
                }
            }
            
            // If process still has remaining time, add it back to queue
            if (remaining_burst_time[i] > 0) {
                rear = (rear + 1) % 100;
                queue[rear] = i;
            }
        }
        
        // If queue is empty but processes remain, find next arriving process
        if (front > rear && !allProcessesComplete()) {
            int next_arrival_time = 999999;
            int next_process = -1;
            
            for (int j = 0; j < n; j++) {
                if (!finish[j] && arrival_time[j] > curr_time && arrival_time[j] < next_arrival_time) {
                    next_arrival_time = arrival_time[j];
                    next_process = j;
                }
            }
            
            if (next_process != -1) {
                curr_time = next_arrival_time;
                rear = (rear + 1) % 100;
                queue[rear] = next_process;
            }
        }
    }
    
    // Print results
    printf("\n\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    float total_waiting_time = 0, total_turnaround_time = 0;
    
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += TAT[i];
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               process_name[i], burst_time[i], arrival_time[i], waiting_time[i], TAT[i], completion_time[i]);
    }
    
    printf("\nAverage Waiting Time = %.2f", total_waiting_time / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_turnaround_time / n);
}

int main() {
    round_robin();
    return 0;
}