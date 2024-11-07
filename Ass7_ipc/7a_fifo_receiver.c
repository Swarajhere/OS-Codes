#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define BUFFER_SIZE 1024
#define OUTPUT_FILE "output.txt"

// Function to analyze the text and count characters, words, and lines
void analyzeText(const char *text, char *result) {
    int characters = 0, words = 0, lines = 0; // Start with lines = 1
    const char *ptr = text;
    int in_word = 0;

    while (*ptr) {
        characters++;
        if (*ptr == ' '  || *ptr == '\t') {
            if (in_word) {
                words++;
                in_word = 0;
            }
        } else if (*ptr == '.') {  // Consider each period as a line terminator
            lines++;
            in_word = 0;
        } else {
            in_word = 1;
        }
        ptr++;
    }
    if (in_word) words++; // Count the last word if no trailing space or dot

    sprintf(result, "Characters: %d, Words: %d, Lines: %d", characters, words, lines);
}

/*
void analyzeText(const char *text, char *result) {
    int characters = 0, words = 0, lines = 0;
    const char *ptr = text;
    int in_word = 0;

    while (*ptr) {
        characters++;
        if (*ptr == ' ' || *ptr == '\n' || *ptr == '\t') {
            if (in_word) {
                words++;
                in_word = 0;
            }
            if (*ptr == '\n') lines++;
        } else {
            in_word = 1;
        }
        ptr++;
    }
    if (in_word) words++; // Count the last word if no trailing space

    sprintf(result, "Characters: %d, Words: %d, Lines: %d", characters, words, lines);
}


*/

int main() {
    char input[BUFFER_SIZE];
    char analysis[BUFFER_SIZE];
    int fd1, fd2;
    FILE *file;

    while (1) {
        // Clear input and analysis buffers
        memset(input, 0, BUFFER_SIZE);
        memset(analysis, 0, BUFFER_SIZE);

        // Read input from FIFO1
        fd1 = open(FIFO1, O_RDONLY);
        read(fd1, input, BUFFER_SIZE);
        close(fd1);

        printf("Received input: %s\n", input);

        // Check for exit condition
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Analyze the text
        analyzeText(input, analysis);

        // Write the analysis to the output file
        file = fopen(OUTPUT_FILE, "w");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
        fprintf(file, "%s\n", analysis);
        fclose(file);

        // Read from the file and send the content to FIFO2
        file = fopen(OUTPUT_FILE, "r");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
        fread(analysis, sizeof(char), BUFFER_SIZE, file);
        fclose(file);

        fd2 = open(FIFO2, O_WRONLY);
        write(fd2, analysis, strlen(analysis) + 1);
        close(fd2);
    }

    return 0;
}


//Process 1: Enter sentences (type 'exit' to quit):
// this is pict.
// Received from Process 2: Characters: 13, Words: 2, Lines: 1

// this is pict. This is pune
// Received from Process 2: Characters: 26, Words: 5, Lines: 1

// This is pict . This is pune.
// Received from Process 2: Characters: 28, Words: 5, Lines: 2

// This is pict . This is pune .
// Received from Process 2: Characters: 29, Words: 6, Lines: 2
