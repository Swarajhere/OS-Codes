#include <stdio.h>
#include <limits.h>

void printFrames(int frames[], int frame_size)
{
    for (int i = 0; i < frame_size; i++)
    {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

// FCFS Page Replacement Algorithm
void fcfs(int pages[], int n, int frame_size)
{
    int frames[frame_size], index = 0, page_faults = 0;
    for (int i = 0; i < frame_size; i++)
        frames[i] = -1;

    printf("\nFCFS Page Replacement\n");
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < frame_size; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            frames[index] = pages[i];
            index = (index + 1) % frame_size;
            page_faults++;
            printFrames(frames, frame_size);
        }
    }
    printf("Total Page Faults (FCFS): %d\n", page_faults);
}

// LRU Page Replacement Algorithm
void lru(int pages[], int n, int frame_size)
{
    int frames[frame_size], recent[frame_size], page_faults = 0;
    for (int i = 0; i < frame_size; i++)
    {
        frames[i] = -1;
        recent[i] = 0;
    }

    printf("\nLRU Page Replacement\n");
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < frame_size; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                recent[j] = i;
                break;
            }
        }

        if (!found)
        {
            int lru_index = 0;
            for (int j = 1; j < frame_size; j++)
            {
                if (recent[j] < recent[lru_index])
                    lru_index = j;
            }
            frames[lru_index] = pages[i];
            recent[lru_index] = i;
            page_faults++;
            printFrames(frames, frame_size);
        }
    }
    printf("Total Page Faults (LRU): %d\n", page_faults);
}

// Optimal Page Replacement Algorithm
void optimal(int pages[], int n, int frame_size)
{
    int frames[frame_size], page_faults = 0;
    for (int i = 0; i < frame_size; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement\n");
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < frame_size; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            int opt_index = -1, farthest = i + 1;
            for (int j = 0; j < frame_size; j++)
            {
                int k;
                for (k = i + 1; k < n; k++)
                {
                    if (frames[j] == pages[k])
                        break;
                }
                if (k > farthest)
                {
                    farthest = k;
                    opt_index = j;
                }
                if (opt_index == -1 || k > farthest)
                {
                    opt_index = j;
                }
            }
            frames[opt_index] = pages[i];
            page_faults++;
            printFrames(frames, frame_size);
        }
    }
    printf("Total Page Faults (Optimal): %d\n", page_faults);
}

int main()
{
    int n, frame_size; // Minimum frame size set to 3
    // Setting minimum frame size
    do
    {
        printf("Enter frame size (minimum 3): ");
        scanf("%d", &frame_size);
    } while (frame_size < 3 || frame_size > n); // Ensure valid frame size

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter page reference sequence:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    // Calling each page replacement algorithm
    fcfs(pages, n, frame_size);
    lru(pages, n, frame_size);
    optimal(pages, n, frame_size);

    return 0;
}
