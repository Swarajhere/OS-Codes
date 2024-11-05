#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define BUFFER_SIZE 1024

int main() {
    char input[BUFFER_SIZE];
    char output[BUFFER_SIZE];
    int fd1, fd2;

    // Create FIFOs if they don't exist
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("Process 1: Enter sentences (type 'exit' to quit):\n");

    while (1) {
        // Get user input
        fgets(input, BUFFER_SIZE, stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline
        if (strcmp(input, "exit") == 0)
            break;

        // Write input to FIFO1
        fd1 = open(FIFO1, O_WRONLY);
        write(fd1, input, strlen(input) + 1);
        close(fd1);

        // Read processed output from FIFO2
        fd2 = open(FIFO2, O_RDONLY);
        read(fd2, output, BUFFER_SIZE);
        close(fd2);

        // Display result
        printf("Received from Process 2: %s\n", output);
    }

    // Cleanup
    unlink(FIFO1);
    unlink(FIFO2);
    return 0;
}
