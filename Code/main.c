#include "main.h"


// Function to process a C file character by character
char* processFile(const char* filename) {
    // Open the file
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    // Allocate memory for the result buffer
    char* resultBuffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    if (resultBuffer == NULL) {
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION);
        fclose(file);  // Close the file before returning
        return NULL;
    }

    int currentChar;
    int bufferIndex = 0;

    // Read the file character by character
    while ((currentChar = getc(file)) != EOF) {
        // Process the current character
        // For now, let's just print each character
        printf("%c", (char)currentChar);
    }

    // Close the file
    fclose(file);

    // TODO: Return the result buffer or perform further processing
    return resultBuffer;
}

int main(int argc, char *argv[]) {
    // Check if a file name is provided as a command-line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MISSING_FILENAME);
        return MAIN_ERROR_MISSING_FILENAME;
    }

    // Call the processFile function with the filename
    char* resultBuffer = processFile(argv[1]);

    if (resultBuffer == NULL) {
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_FILE_PROCESSING);
        return MAIN_ERROR_FILE_PROCESSING;
    }

    // TODO: Handle the resultBuffer or perform further processing
    // For now, we'll just print the resultBuffer
    printf("\nResult buffer: %s", resultBuffer);

    // Free the result buffer when done
    free(resultBuffer);

    return SCANNER_SUCCESS;
}
