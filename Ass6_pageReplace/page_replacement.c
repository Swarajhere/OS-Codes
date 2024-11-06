#include <stdio.h>
#include <stdlib.h>

void printFrame(int frame[], int capacity)
{
    printf("Frame: ");
    for (int j = 0; j < capacity; j++)
    {
        if (frame[j] == -1)
        {
            printf("- "); // Print - for empty frames
        }
        else
        {
            printf("%d ", frame[j]);
        }
    }
    printf("\n");
}

// replace the page which is loaded first
// if all pages are used in future, replace the page which is used first
void fifo(int pages[], int n, int capacity)
{
    int frame[capacity], index = 0, faults = 0, hits = 0;
    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < capacity; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                hits++;
                break;
            }
        }
        if (!found)
        {
            frame[index] = pages[i];
            index = (index + 1) % capacity;
            faults++;
        }
        printFrame(frame, capacity);
    }
    printf("Total Page Faults (FIFO): %d\n", faults);
    printf("Total Page Hits (FIFO): %d\n", hits);
}

// replace the page which is not used in longest dimension of time in past
// Go to the past and check which page is not used for longest time
void lru(int pages[], int n, int capacity)
{
    int frame[capacity], time[capacity], faults = 0, counter = 0, hits = 0;

    // Initialize the frame and time arrays
    for (int i = 0; i < capacity; i++)
    {
        frame[i] = -1; // -1 indicates an empty slot
        time[i] = 0;   // Time array is also initialized to 0
    }

    // Iterate over each page in the reference string
    for (int i = 0; i < n; i++)
    {
        int found = 0, least = 0;

        // Check if the page is already in the frame (Page Hit)
        for (int j = 0; j < capacity; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1; // Page found in the frame
                hits++;
                time[j] = ++counter; // Update the time for this page
                break;
            }
        }

        // If page not found (Page Fault)
        if (!found)
        {
            // Find the least recently used (LRU) page by checking the time array
            for (int j = 1; j < capacity; j++)
            {
                if (time[j] < time[least])
                {
                    least = j; // Least recently used page
                }
            }
            // Replace the LRU page with the new page
            frame[least] = pages[i];
            time[least] = ++counter; // Set the time for the new page
            faults++;                // Increment the page fault count
        }

        // Display the current state of the frames
        printFrame(frame, capacity);
    }

    // Print the total number of page faults
    printf("Total Page Faults (LRU): %d\n", faults);
    printf("Total Page Hits (LRU): %d\n", hits);
}

// replace the page which is not used in longest dimension of time in future
// if all pages are used in future, replace the page which is used in longest dimension of time in future
void optimal(int pages[], int n, int capacity)
{
    int frame[capacity], faults = 0;
    // Initialize the frame to -1 (empty slots)
    for (int i = 0; i < capacity; i++)
    {
        frame[i] = -1;
    }

    // Iterate through the pages
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        int farthest = -1, replace_index = -1;

        // Check if the page is already in the frame (Page Hit)
        for (int j = 0; j < capacity; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1; // Page found in frame
                break;
            }
        }

        // If page not found in the frame, it's a Page Fault
        if (!found)
        {
            // Check for an empty frame
            for (int j = 0; j < capacity; j++)
            {
                if (frame[j] == -1)
                {
                    frame[j] = pages[i]; // Fill the empty frame
                    faults++;            // Increment page faults
                    found = 1;
                    break;
                }
            }
        }

        // If there are no empty frames, replace the page using Optimal strategy
        if (!found)
        {
            // Find the page that is used farthest in the future or not at all
            for (int j = 0; j < capacity; j++)
            {
                int k;
                for (k = i + 1; k < n; k++)
                {
                    if (frame[j] == pages[k])
                    {
                        // Page will be used in future at index k
                        if (k > farthest)
                        {
                            farthest = k;
                            replace_index = j;
                        }
                        break;
                    }
                }
                if (k == n)
                {
                    // If page will not be used in the future, replace it
                    replace_index = j;
                    break;
                }
            }
            frame[replace_index] = pages[i]; // Replace the page
            faults++;                        // Increment page faults
        }

        // Display the current frame content
        printFrame(frame, capacity);
    }

    // Print the total number of page faults
    printf("Total Page Faults (Optimal): %d\n", faults);
}

int main()
{
    int choice, n, capacity;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter the frame capacity: ");
    scanf("%d", &capacity);

    do
    {
        printf("Choose Page Replacement Algorithm:\n1. FIFO\n2. LRU\n3. Optimal\n4. Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fifo(pages, n, capacity);
            break;
        case 2:
            lru(pages, n, capacity);
            break;
        case 3:
            optimal(pages, n, capacity);
            break;
        case 4:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
