// main_program.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void sortArray(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    
    // Accept array size and elements from user
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    
    int arr[n]; // int * arr = (int *)malloc(n * sizeof(int));
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Sort the array
    sortArray(arr, n);
    
    // Prepare arguments for execve
    char *args[n + 2]; // char **args = (char **)malloc((n + 2) * sizeof(char*));  
    args[0] = "./reverse";  // child program to be executed
    for (int i = 0; i < n; i++) {
        args[i + 1] = malloc(10);
        sprintf(args[i + 1], "%d", arr[i]);
    }
    args[n + 1] = NULL;

    // Fork process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // In child process, execute child_program with sorted array as arguments
        execve(args[0], args, NULL);
        perror("execve failed");  // execve only returns on failure
        exit(1);
    }
    else {
        // Parent process waits for child to complete
        wait(NULL);
        printf("Parent: Child process completed.\n");
    }

    // Free allocated memory
    for (int i = 1; i <= n; i++) {
        free(args[i]);
    }

    return 0;
}
