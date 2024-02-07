#include "main.h"


// Function to process a C file character by character
char* processFile(const char* filename) {
    // Open the file
    FILE* file = fopen(filename, "rb");
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

        // TODO: create all DFAs, initialize them, advance the dfa with the new char
        // if next char is a delimiter, finalize all dfas and add the token to the result
        // if current character is a delimiter, then we also finish all the dfas
        // this way the contents "x * y" will be parsed as "x| |*| |y"




        // For now, let's just print each character
        printf("%c", (char)currentChar);
    } 



    //TODO: redo ^this. We need to write then the buffer is full and start again with a new empty buffer

    //End all dfas

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
