#include "main.h"


// Function to process a C file character by character
int processFile(const char *filename)
{
    // Open the file
    FILE* input_file = fopen(filename, "rb"); // open as binary
    // Handle error opening target file
    if (input_file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return MAIN_ERROR_CANT_READ_FILE; // TODO: cahnge for define error
    }

    // Preparing output filename
    char* output_filename = get_file_name(filename);

    // Creating output file
    FILE* output_file = fopen(output_filename, "wb");
    if (output_file == NULL){ // Handle error when creating output file
        fprintf(stderr, "Error creating output file: %s\n", output_filename);
        return MAIN_ERROR_FILE_PROCESSING;
    }

    // Upon completion, close output file and free result buffer

    // Allocate memory for the result buffer
    char* writting_buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    if (writting_buffer == NULL) { // Handle error when allocating the buffer
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION);
        fclose(input_file); // Close the file before returning
        return PREPROCESS_ERROR_MEMORY_ALLOCATION; // TODO: cahnge for define error
    }

    char* current_token = (char*)malloc(sizeof(char) * BUFFER_SIZE); // buffer of the raw token
    if (current_token == NULL) { // Handle error when allocating the buffer
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION);
        fclose(input_file); // Close the file before returning
        return PREPROCESS_ERROR_MEMORY_ALLOCATION; // TODO: cahnge for define error
    }
    current_token[0] = '\0'; // to prevent 1 bug, dont remove


    DFA dfas[NUM_DFA];
    // TODO: initialize all DFAs
    char typealphabet[TYPECOLUMNS] = {TYPEALPHABET};
    initialize_dfa(&dfas[TYPEDFA], typealphabet, TYPEROWS, TYPEACCEPT);
    char identifieralphabet[IDENTIFIERCOLUMNS] = {IDENTIFIERALPHABET};
    initialize_dfa(&dfas[IDENTIFIERDFA], identifieralphabet, IDENTIFIERROWS, IDENTIFIERACCEPT);
    char keywordalphabet[KEYWORDCOLUMNS] = {KEYWORDALPHABET};
    initialize_dfa(&dfas[KEYWORDDFA], keywordalphabet, KEYWORDROWS, KEYWORDACCEPT);
    char numberalphabet[NUMBERCOLUMNS] = {NUMBERALPHABET};
    initialize_dfa(&dfas[NUMBERDFA], numberalphabet, NUMBERROWS, NUMBERACCEPT);
    char specialalphabet[SPECIALCOLUMNS] = {SPECIALALPHABET};
    initialize_dfa(&dfas[SPECIALDFA], specialalphabet, SPECIALROWS, SPECIALACCEPT);
    char operatoralphabet[OPERATORCOLUMNS] = {OPERATORALPHABET};
    initialize_dfa(&dfas[OPERATORDFA], operatoralphabet, OPERATORROWS, OPERATORACCEPT);
    char literalalphabet[LITERALCOLUMNS] = {LITERALALPHABET};
    initialize_dfa(&dfas[LITERALDFA], literalalphabet, LITERALROWS, LITERALACCEPT);
    // =======================================================================================
    // =======================================================================================
    // =======================================================================================

    int currentChar = getc(input_file); // Initializing variables to iterate through the file
    int look_ahead = getc(input_file);
    bool is_current_char_delimiter = is_delimiter((char)currentChar);
    bool is_look_ahead_delimiter = is_delimiter((char)look_ahead);
    int writ_buff_idx = 0;
    int curr_token_idx = 0; //also serves as length
    // Read the file character by character
    while (currentChar != EOF) {


        current_token[curr_token_idx] = (char)currentChar; 
        curr_token_idx++; 

        for (int i = 0; i < NUM_DFA; i++)  advance_dfa(&dfas[i], (char)currentChar);


        if (is_current_char_delimiter || is_look_ahead_delimiter) {

            /*
                this check ensures that when the lookahead is a delimiter, 
                the token is finalized. Also ensures that if the current char is 
                a delimiter, it will be alone by itself. 
                this way the contents "x * y" will be parsed as "x| |*| |y"
            */

            bool success = false;
            for (int i = 0; i < NUM_DFA; i++) {

                success = finalize_dfa(&dfas[i]);
                if (success) {

                    char* processed_token = tokenize(i, current_token, curr_token_idx); 
                    // ^current token index is also length
                    
                    int processed_token_len = strlen(processed_token); 

                    memcpy(&writting_buffer[writ_buff_idx], processed_token, processed_token_len); 
                    free(processed_token); 
                    
                    writ_buff_idx += processed_token_len; 

                    curr_token_idx = 0; //reset buffer

                    break;
                }
            }

            if (!success) {
                // TODO: implement this
                // think about more possible exeptions

                //could be space ' ' or could be an actual error
                if(current_token[0] != ' ') {
                    //assume error
                    char* processed_token = tokenize(ERROR_TOKEN, current_token, curr_token_idx); 
                    // ^current token index is also length
                    
                    int processed_token_len = strlen(processed_token); 

                    memcpy(&writting_buffer[writ_buff_idx], processed_token, processed_token_len); 
                    free(processed_token); 
                    
                    writ_buff_idx += processed_token_len; 

                    curr_token_idx = 0; //reset buffer
                    current_token[0] = '\0'; 

                } // space is not an error
            }

            for (int i = 0; i < NUM_DFA; i++) reset_dfa(&dfas[i]);

        }


        if (BUFFER_SIZE * BUFFER_THRESHOLD < writ_buff_idx) { 
            /*the writting buffer is starting to get full. empty it*/
            writting_buffer[writ_buff_idx] = '\0';

            // Write scanner output into output file
            fwrite(writting_buffer, sizeof(char), writ_buff_idx + 1, output_file);

            writ_buff_idx = 0; // start again
        }
        currentChar = look_ahead; // update chars
        look_ahead = getc(input_file);
        is_current_char_delimiter = is_look_ahead_delimiter;
        is_look_ahead_delimiter = is_delimiter(look_ahead);
    }


    // Do last iteration

    {
        //its weird but it could finalize with a valid token
        bool success = false;
        for (int i = 0; i < NUM_DFA; i++) {

            success = finalize_dfa(&dfas[i]);
            if (success) {

                char* processed_token = tokenize(i, current_token, curr_token_idx); 
                // ^current token index is also length
                
                int processed_token_len = strlen(processed_token); 

                memcpy(&writting_buffer[writ_buff_idx], processed_token, processed_token_len); 
                free(processed_token); 
                writ_buff_idx += processed_token_len; 

                curr_token_idx = 0; //reset buffer


                break;
            }
        }

        if (!success) {
            if(current_token[0] != ' ') {

                char* processed_token = tokenize(ERROR_TOKEN, current_token, curr_token_idx); 
                // ^current token index is also length
                
                int processed_token_len = strlen(processed_token); 

                memcpy(&writting_buffer[writ_buff_idx], processed_token, processed_token_len); 
                free(processed_token); 
                
                writ_buff_idx += processed_token_len; 
                curr_token_idx = 0; //reset buffer
                current_token[0] = '\0'; 

            } // space is not an error
        }

    }

    // End all dfas

    for (int i = 0; i < NUM_DFA; i++) free_dfa(&dfas[i]); //free all dfas

    // Close the file
    free(writting_buffer);
    free(output_filename);
    free(current_token); 

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
    int process_return = processFile(argv[1]);
    // Handle error when  processing target file
    if (process_return != 0) {
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

char *get_file_name(const char *argv1) {

    size_t len = strlen(argv1);
    char* output_filename = (char *)malloc(len + strlen("scn") + 1);

    // Check if memory allocation was successful
    if (output_filename == NULL) {
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION);
        exit(EXIT_FAILURE);
    }

    // Copy the input filename to the output filename, appending scn to it
    strcpy(output_filename, argv1);
    strcat(output_filename, "scn");

    return output_filename;
}
