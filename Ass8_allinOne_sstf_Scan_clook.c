#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n)
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

void SSTF(int requests[], int n, int head)
{
    int total_movement = 0, completed[n], count = 0;
    for (int i = 0; i < n; i++)
        completed[i] = 0;

    printf("\nSSTF Disk Scheduling:\nHead Movement: %d", head);
    while (count < n)
    {
        int closest = -1, min_distance = 1e9;
        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && abs(head - requests[i]) < min_distance)
            {
                min_distance = abs(head - requests[i]);
                closest = i;
            }
        }
        if (closest != -1)
        {
            total_movement += min_distance;
            head = requests[closest];
            completed[closest] = 1;
            count++;
            printf(" -> %d", head);
        }
    }
    printf("\nTotal Head Movements = %d\n", total_movement);
}

void SCAN(int requests[], int n, int head, int disk_size, int direction)
{
    sort(requests, n);
    int total_movement = 0, i = 0;
    printf("\nSCAN Disk Scheduling:\nHead Movement: %d", head);

    if (direction == 1)
    {
        while (i < n && requests[i] < head)
            i++;
        for (int j = i; j < n; j++)
        {
            printf(" -> %d", requests[j]);
            total_movement += abs(head - requests[j]);
            head = requests[j];
        }
        total_movement += abs(head - (disk_size - 1));
        head = disk_size - 1;
        printf(" -> %d", head);
        for (int j = i - 1; j >= 0; j--)
        {
            printf(" -> %d", requests[j]);
            total_movement += abs(head - requests[j]);
            head = requests[j];
        }
    }
    else
    {
        while (i < n && requests[i] < head)
            i++;
        for (int j = i - 1; j >= 0; j--)
        {
            printf(" -> %d", requests[j]);
            total_movement += abs(head - requests[j]);
            head = requests[j];
        }
        total_movement += abs(head);
        head = 0;
        printf(" -> %d", head);
        for (int j = i; j < n; j++)
        {
            printf(" -> %d", requests[j]);
            total_movement += abs(head - requests[j]);
            head = requests[j];
        }
    }
    printf("\nTotal Head Movements = %d\n", total_movement);
}

void C_LOOK(int requests[], int n, int head, int disk_size, int direction)
{
    sort(requests, n);
    int total_movement = 0, i = 0;
    printf("\nC-LOOK Disk Scheduling:\nHead Movement: %d", head);

    while (i < n && requests[i] < head)
        i++;

    if (direction == 1)
    {
        for (int j = i; j < n; j++)
        {
            printf(" -> %d", requests[j]);
            total_movement += abs(head - requests[j]);
            head = requests[j];
        }
        total_movement += abs(head - requests[0]);
        head = requests[0];
        printf(" -> %d", head);
        for (int j = 1; j < i; j++)
        {
            printf(" -> %d", requests[j]);
            total_movement += abs(head - requests[j]);
            head = requests[j];
        }
    }
    else
    {
        for (int j = i - 1; j >= 0; j--)
        {
            printf(" -> %d", requests[j]);
            total_movement += abs(head - requests[j]);
            head = requests[j];
        }
        total_movement += abs(head - requests[n - 1]);
        head = requests[n - 1];
        printf(" -> %d", head);
        for (int j = n - 2; j >= i; j--)
        {
            printf(" -> %d", requests[j]);
            total_movement += abs(head - requests[j]);
            head = requests[j];
        }
    }
    printf("\nTotal Head Movements = %d\n", total_movement);
}

int main()
{
    int n, head, disk_size, direction, choice;

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    printf("Enter the direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    do
    {
        printf("\nDisk Scheduling Algorithms Menu:\n");
        printf("1. SSTF\n");
        printf("2. SCAN\n");
        printf("3. C-LOOK\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            SSTF(requests, n, head);
            break;
        case 2:
            SCAN(requests, n, head, disk_size, direction);
            break;
        case 3:
            C_LOOK(requests, n, head, disk_size, direction);
            break;
        case 4:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}