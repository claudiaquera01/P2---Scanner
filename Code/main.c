#include "main.h"


// Function to process a C file character by character
int *processFile(const char *filename)
{
    // Open the file
    FILE *input_file = fopen(filename, "rb"); // open as binary
    // Handle error opening target file
    if (input_file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 1; // TODO: cahnge for define error
    }

    // Preparing output filename
    char *output_filename = get_file_name(filename);

    // Creating output file
    FILE *output_file = fopen(output_filename, "wb");
    if (output_file == NULL){ // Handle error when creating output file
        fprintf(stderr, "Error creating output file: %s\n", output_filename);
        return MAIN_ERROR_FILE_PROCESSING;
    }

    // Upon completion, close output file and free result buffer

    // Allocate memory for the result buffer
    char *resultBuffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    // Handle error when allocating the buffer
    if (resultBuffer == NULL) {
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION);
        fclose(input_file); // Close the file before returning
        return 2; // TODO: cahnge for define error
    }

    DFA dfas[NUM_DFA];
    // TODO: initialize all DFAs

    // why is currentcahr an int ????
    int currentChar = getc(input_file); // Initializing variables to iterate through the file
    char look_ahead = getc(input_file);
    bool is_current_char_delimiter = is_delimiter((char)currentChar);
    bool is_look_ahead_delimiter = is_delimiter((char)look_ahead);
    int bufferIndex = 0;
    // Read the file character by character
    while (currentChar != EOF) {
        // Process the current character

        // TODO: create all DFAs, initialize them, advance the dfa with the new char
        // if next char is a delimiter, finalize all dfas and add the token to the result
        // if current character is a delimiter, then we also finish all the dfas
        // this way the contents "x * y" will be parsed as "x| |*| |y"

        for (int i = 0; i < NUM_DFA; i++) {

            advance_dfa(&dfas[i], currentChar);

        }

        if (is_current_char_delimiter || is_look_ahead_delimiter) {

            /*
                this check ensures that when the lookahead is a delimiter, 
                the token is finalized. Also ensures that if the current char is 
                a delimiter, it will be alone by itself. 
            */

            bool success = false;
            for (int i = 0; i < NUM_DFA; i++) {

                success = finalize_dfa(&dfas[i]);
                if (success)
                {
                    // TODO: get token and add it to result buffer
                    // (also update bufferindex)

                    break;
                }
            }

            if (!success) {
                // TODO: implement this
                //could be space ' ' or could be an actual error
                // think about more possible exeptions
            }

            for (int i = 0; i < NUM_DFA; i++) reset_dfa(&dfas[i]);
        }

        // TEST: Copy file into buffer
        resultBuffer[bufferIndex] = (char)currentChar; // write what is needed
        bufferIndex++;                                 // update index accordingly

        if (BUFFER_SIZE * BUFFER_THRESHOLD < bufferIndex) {
            resultBuffer[bufferIndex] = '\0';
            bufferIndex++;

            // Write scanner output into output file
            fwrite(resultBuffer, sizeof(char), bufferIndex, output_file);

            bufferIndex = 0; // start again
        }
        currentChar = look_ahead; // update chars
        look_ahead = (char)getc(input_file);
        is_current_char_delimiter = is_look_ahead_delimiter;
        is_look_ahead_delimiter = is_delimiter(look_ahead);
    }

    // End all dfas

    for (int i = 0; i < NUM_DFA; i++) free_dfa(&dfas[i]); //free all dfas

    // Close the file
    free(resultBuffer);
    free(output_filename);

    fclose(input_file);
    fclose(output_file);

    return 0; //return success
}

int main(int argc, char *argv[])
{
    // Check if a file name is provided as a command-line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MISSING_FILENAME);
        return MAIN_ERROR_MISSING_FILENAME;
    }

    // Call the processFile function with the filename
    char *resultBuffer = processFile(argv[1]);
    // Handle error when  processing target file
    if (resultBuffer == NULL) {
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_FILE_PROCESSING);
        return MAIN_ERROR_FILE_PROCESSING;
    }

    // TESTING DFA TABLES
    int test[] = {KEYWORDTABLE};
    for (int i = 0; i < KEYWORDROWS; i++) {
        for (int j = 0; j < KEYWORDCOLUMNS; j++) {
            printf("|%d|", test[i * KEYWORDCOLUMNS + j]);
        }
        printf("\n");
    }
    return SCANNER_SUCCESS;
}

char *get_file_name(char *argv1) {

    // TODO: complete this
    // Allocate space for new name, construct it and return

    /*
    char name[(strlen(argv[1]) + strlen("scn"))];
    strcpy(output_filename, argv[1]);
    strcat(output_filename, "scn");

    */

    //^this code does NOT work, you cannot allocate a non-constant space on the stack. Use malloc

    size_t len = strlen(argv1);
    char *output_filename = (char *)malloc(len + strlen("scn") + 1);

    // Check if memory allocation was successful
    if (output_filename == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy the input filename to the output filename, appending .scn to it
    strcpy(output_filename, argv1);
    strcat(output_filename, "scn");

    return output_filename;
}