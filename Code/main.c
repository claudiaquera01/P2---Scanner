#include "main.h"


// Function to process a C file character by character
int processFile(const char* filename)
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
    // Import the alphabet of our DFAs
    char alphabet[ALPHABETLEN] = {ALPHABET};

    {
        //----------------------------------------------TYPE DFA----------------------------------------------
        // Import accepting state list of type table
        int type_accepting[TYPEACCEPTLEN] = {TYPEACCEPT};
        // Initialize type dfa
        initialize_dfa(&dfas[DFA_TYPES], alphabet, TYPEROWS, TYPECOLUMNS, type_accepting, TYPEACCEPTLEN);
        // Import mapping list of type table
        int type_mapping[ALPHABETLEN] = {TYPEMAPPING};
        // Update dfa mapping list with imported one
        fill_column_mapping(&dfas[DFA_TYPES], alphabet, ALPHABETLEN, type_mapping);
        // Import transition table of type table
        int type_doc_table[TYPEROWS*TYPECOLUMNS] = {TYPETABLE};
        // Update dfa transition table with imported one
        fill_transition_table(&dfas[DFA_TYPES], type_doc_table);
        //----------------------------------------------IDENTIFIER DFA----------------------------------------------
        // Import accepting state list of identifier table
        int identifier_accepting[IDENTIFIERACCEPTLEN] = {IDENTIFIERACCEPT};
        // Initialize identifier dfa
        initialize_dfa(&dfas[DFA_IDENTIFIER], alphabet, IDENTIFIERROWS, IDENTIFIERCOLUMNS, identifier_accepting, IDENTIFIERACCEPTLEN);
        // Import mapping list of identifier table
        int identifier_mapping[ALPHABETLEN] = {IDENTIFIERMAPPING};
        // Update dfa mapping list with imported one
        fill_column_mapping(&dfas[DFA_IDENTIFIER], alphabet, ALPHABETLEN, identifier_mapping);
        // Import transition table of identifier table
        int identifier_doc_table[IDENTIFIERROWS*IDENTIFIERCOLUMNS] = {IDENTIFIERTABLE};
        // Update dfa transition table with imported one
        fill_transition_table(&dfas[DFA_IDENTIFIER], identifier_doc_table);
        //----------------------------------------------KEYWORD DFA----------------------------------------------
        // Import accepting state list of keyword table
        int keyword_accepting[KEYWORDACCEPTLEN] = {KEYWORDACCEPT};
        // Initialize keyword dfa
        initialize_dfa(&dfas[DFA_KEYWORDS], alphabet, KEYWORDROWS, KEYWORDCOLUMNS, keyword_accepting, KEYWORDACCEPTLEN);
        // Import mapping list of keyword table
        int keyword_mapping[ALPHABETLEN] = {KEYWORDMAPPING};
        // Update dfa mapping list with imported one
        fill_column_mapping(&dfas[DFA_KEYWORDS], alphabet, ALPHABETLEN, keyword_mapping);
        // Import transition table of keyword table
        int keyword_doc_table[KEYWORDROWS*KEYWORDCOLUMNS] = {KEYWORDTABLE};
        // Update dfa transition table with imported one
        fill_transition_table(&dfas[DFA_KEYWORDS], keyword_doc_table);
        //----------------------------------------------NUMBER DFA----------------------------------------------
        // Import accepting state list of number table
        int number_accepting[NUMBERACCEPTLEN] = {NUMBERACCEPT};
        // Initialize number dfa
        initialize_dfa(&dfas[DFA_NUMBERS], alphabet, NUMBERROWS, NUMBERCOLUMNS, number_accepting, NUMBERACCEPTLEN);
        // Import mapping list of number table
        int number_mapping[ALPHABETLEN] = {NUMBERMAPPING};
        // Update dfa mapping list with imported one
        fill_column_mapping(&dfas[DFA_NUMBERS], alphabet, ALPHABETLEN, number_mapping);
        // Import transition table of number table
        int number_doc_table[NUMBERROWS*NUMBERCOLUMNS] = {NUMBERTABLE};
        // Update dfa transition table with imported one
        fill_transition_table(&dfas[DFA_NUMBERS], number_doc_table);
        //----------------------------------------------SPECIAL CHAR DFA----------------------------------------------
        // Import accepting state list of special char table
        int special_accepting[SPECIALACCEPTLEN] = {SPECIALACCEPT};
        // Initialize special char dfa
        initialize_dfa(&dfas[DFA_SPECIAL_CHAR], alphabet, SPECIALROWS, SPECIALCOLUMNS, special_accepting, SPECIALACCEPTLEN);
        // Import mapping list of special table
        int special_mapping[ALPHABETLEN] = {SPECIALMAPPING};
        // Update dfa mapping list with imported one
        fill_column_mapping(&dfas[DFA_SPECIAL_CHAR], alphabet, ALPHABETLEN, special_mapping);
        // Import transition table of special char table
        int special_doc_table[SPECIALROWS*SPECIALCOLUMNS] = {SPECIALTABLE};
        // Update dfa transition table with imported one
        fill_transition_table(&dfas[DFA_SPECIAL_CHAR], special_doc_table);
        //----------------------------------------------OPERATOR DFA----------------------------------------------
        // Import accepting state list of operator table
        int operator_accepting[OPERATORACCEPTLEN] = {OPERATORACCEPT};
        // Initialize operator dfa
        initialize_dfa(&dfas[DFA_OPERATORS], alphabet, OPERATORROWS, OPERATORCOLUMNS, operator_accepting, OPERATORACCEPTLEN);
        // Import mapping list of operator table
        int operator_mapping[ALPHABETLEN] = {OPERATORMAPPING};
        // Update dfa mapping list with imported one
        fill_column_mapping(&dfas[DFA_OPERATORS], alphabet, ALPHABETLEN, operator_mapping);
        // Import transition table of operator table
        int operator_doc_table[OPERATORROWS*OPERATORCOLUMNS] = {OPERATORTABLE};
        // Update dfa transition table with imported one
        fill_transition_table(&dfas[DFA_OPERATORS], operator_doc_table);
        //----------------------------------------------LITERAL DFA----------------------------------------------
        // Import accepting state list of literal table
        int literal_accepting[LITERALACCEPTLEN] = {LITERALACCEPT};
        // Initialize literal dfa
        initialize_dfa(&dfas[DFA_LITERALS], alphabet, LITERALROWS, LITERALCOLUMNS, literal_accepting, LITERALACCEPTLEN);
        // Import mapping list of literal table
        int literal_mapping[ALPHABETLEN] = {LITERALMAPPING};
        // Update dfa mapping list with imported one
        fill_column_mapping(&dfas[DFA_LITERALS], alphabet, ALPHABETLEN, literal_mapping);
        // Import transition table of literal table
        int literal_doc_table[LITERALROWS*LITERALCOLUMNS] = {LITERALTABLE};
        // Update dfa transition table with imported one
        fill_transition_table(&dfas[DFA_LITERALS], literal_doc_table);
    }


    int currentChar = getc(input_file); // Initializing variables to iterate through the file
    int look_ahead = getc(input_file);
    bool is_current_char_delimiter = is_delimiter((char)currentChar);
    bool is_look_ahead_delimiter = is_delimiter((char)look_ahead);
    int writ_buff_idx = 0;
    int curr_token_idx = 0; //also serves as length
    // Read the file character by character
    printf("Starting to actually process file! \n\n"); 

    while (currentChar != EOF) {

        current_token[curr_token_idx] = (char)currentChar; 
        curr_token_idx++; 

        printf("Current char: \t\"%c\" \n", currentChar); 


        for (int i = 0; i < NUM_DFA; i++)  advance_dfa(&dfas[i], (char)currentChar);


        if (is_current_char_delimiter || is_look_ahead_delimiter) {

            /*
                this check ensures that when the lookahead is a delimiter, 
                the token is finalized. Also ensures that if the current char is 
                a delimiter, it will be alone by itself. 
                this way the contents "x * y" will be parsed as "x| |*| |y"
            */

            current_token[curr_token_idx + 1] = '\0'; 


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

                    break;
                }
            }

            if (!success) {
                // TODO: think about more possible exeptions

                //could be space ' ' or could be an actual error
                if(current_token[0] != ' ' || (char)currentChar != '\n' || (char)currentChar != '\r' || currentChar == EOF) {
                    //assume error
                    char* processed_token = tokenize(ERROR_TOKEN, current_token, curr_token_idx); 
                    // ^current token index is also length
                    
                    int processed_token_len = strlen(processed_token); 

                    memcpy(&writting_buffer[writ_buff_idx], processed_token, processed_token_len); 
                    free(processed_token); 
                    
                    writ_buff_idx += processed_token_len; 


                } // space \n, \r or EOF is not an error
            }

            curr_token_idx = 0; //reset buffer
            current_token[0] = '\0'; 

            for (int i = 0; i < NUM_DFA; i++) reset_dfa(&dfas[i]);

        }

        if (BUFFER_SIZE * BUFFER_THRESHOLD < writ_buff_idx) { 
            /*the writting buffer is starting to get full. empty it*/
            writting_buffer[writ_buff_idx] = '\0'; 

            printf("parsed text added: %s\n\n", writting_buffer); 

            // Write scanner output into output file
            fwrite(writting_buffer, sizeof(char), writ_buff_idx + 1, output_file);

            writ_buff_idx = 0; // start again
        }
        currentChar = look_ahead; // update chars
        look_ahead = getc(input_file);
        is_current_char_delimiter = is_look_ahead_delimiter;
        is_look_ahead_delimiter = is_delimiter((char)look_ahead);
    }


    // Do last iteration

    printf("Final iteration! \n"); 


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

            } 
        }

        //finally copy the data to the file

        writting_buffer[writ_buff_idx] = '\0';
        printf("parsed text added: %s\n\n", writting_buffer); 

        // Write scanner output into output file
        fwrite(writting_buffer, sizeof(char), writ_buff_idx + 1, output_file);

    }

    // End all dfas

    printf("Ended processing file! \n"); 


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
        COUNTFUNC(IF_COST)
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        COUNTFUNC(FPRINTF_COST)
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MISSING_FILENAME);
        COUNTFUNC(FPRINTF_COST)
        COUNTFUNC(RETURN_COST)
        return MAIN_ERROR_MISSING_FILENAME;
    }

    printf("Calling processFile! \n"); 
    // Call the processFile function with the filename
    int process_return = processFile(argv[1]);
    // Handle error when  processing target file
    if (process_return != 0) {
        COUNTFUNC(IF_COST)
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_FILE_PROCESSING);
        COUNTFUNC(FPRINTF_COST)
        COUNTFUNC(RETURN_COST)
        return MAIN_ERROR_FILE_PROCESSING;
    }
    COUNTFUNC(RETURN_COST)
    return SCANNER_SUCCESS;
}















/*

compilation: 

gcc main.c utils.c datastructures.c debug.c errors.c -o parser

Execution: 

./parser test1.c


How to do it: 

1.  go to ./Code
2.  Compile using previous command
3.  execute: cd tests
4.  execute: ./parser test1.c



*/



