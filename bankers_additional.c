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
int calculateSafeSequence(int n) {
    for (int i = 0; i < n; i++)
        done[i] = 0;

    int processSeq[MAX_PROCESSES];
    int count = 0;
    int safe = 1;

    int work[MAX_RESOURCES];
    for (int i = 0; i < m; i++) {
        work[i] = available[i]; // Copy available resources
    }

    while (count < n) {
        safe = 0;
        for (int i = 0; i < n; i++) {
            if (done[i])
                continue;

            int canProceed = 1;
            for (int j = 0; j < m; j++) {
                if (need[i][j] > work[j]) {
                    canProceed = 0;
                    break;
                }
            }

            if (canProceed) {
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

    if (safe) {
        printf("The safe sequence is:\n");
        for (int i = 0; i < count; i++)
            printf("P%d ", processSeq[i]);
        printf("\n");
    } else {
        printf("The system is not in a safe state.\n");
    }
    return safe;
}

int main() {
    printf("Enter the initial number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Resources allocated:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Max resources required:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate the need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    // Calculate the initial safe sequence
    calculateSafeSequence(n);

    // Loop for adding new processes
    // char addProcess;
    // do {
    //     printf("Do you want to add a new process? (y/n): ");
    //     scanf(" %c", &addProcess);

    //     if (addProcess == 'y') {
    //         n++; // Increase process count for the new process

    //         printf("Enter allocated resources for the new process P%d:\n", n - 1);
    //         for (int j = 0; j < m; j++)
    //             scanf("%d", &alloc[n - 1][j]);

    //         printf("Enter maximum resources required for the new process P%d:\n", n - 1);
    //         for (int j = 0; j < m; j++)
    //             scanf("%d", &max[n - 1][j]);

    //         // Update the need matrix for the new process
    //         for (int j = 0; j < m; j++)
    //             need[n - 1][j] = max[n - 1][j] - alloc[n - 1][j];

    //         printf("Available resources after adding new process:\n");
    //         for (int i = 0; i < m; i++)
    //             printf("%d ", available[i]);
    //         printf("\n");

    //         // Calculate the new safe sequence
    //         calculateSafeSequence(n);
    //     }
    // } while (addProcess == 'y');

    return 0;
}
