#include "main.h"


// Function to process a C file character by character
char* processFile(const char* filename) {
    // Open the file
    FILE* file = fopen(filename, "rb");
    // Handle error opening target file
    if (file == NULL) { 
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    // Allocate memory for the result buffer
    char* resultBuffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    // Handle error when allocating the buffer
    if (resultBuffer == NULL) {
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION);
        fclose(file);  // Close the file before returning
        return NULL;
    }

    // Initializing variables to iterate through the file
    int currentChar;
    int bufferIndex = 0;
    // Read the file character by character
    while ((currentChar = getc(file)) != EOF) {
        // Process the current character

        // TODO: create all DFAs, initialize them, advance the dfa with the new char
        // if next char is a delimiter, finalize all dfas and add the token to the result
        // if current character is a delimiter, then we also finish all the dfas
        // this way the contents "x * y" will be parsed as "x| |*| |y"

        // TEST: Copy file into buffer
        resultBuffer[bufferIndex] = (char) currentChar;
        bufferIndex++;
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
    // Handle error when  processing target file
    if (resultBuffer == NULL) {
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_FILE_PROCESSING);
        return MAIN_ERROR_FILE_PROCESSING;
    }

    // Preparing output filename
    char output_filename[(strlen(argv[1]) + strlen("scn"))];
    strcpy(output_filename, argv[1]);
    strcat(output_filename, "scn");

    // Creating output file
    FILE* output = fopen(output_filename, "wb");
    // Handle error when creating output file
    if (output == NULL) {
        fprintf(stderr, "Error creating output file: %s\n", output_filename);
        return MAIN_ERROR_FILE_PROCESSING;
    }
    // Write scanner output into output file
    fwrite(resultBuffer, sizeof(char) * strlen(resultBuffer), 1, output);

    // Upon completion, close output file and free result buffer
    fclose(output);
    free(resultBuffer);

    // TESTING DFA TABLES
    int test[] = {KEYWORDTABLE};
    for(int i=0; i < KEYWORDROWS; i++){
        for(int j=0; j< KEYWORDCOLUMNS; j++){
            printf("|%d|", test[i*KEYWORDCOLUMNS + j]);
        }
        printf("\n");
    }
    return SCANNER_SUCCESS;
}
