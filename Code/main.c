#include "main.h"


// Function to process a C file character by character
int processFile(const char* filename)
{
    // Open the file
    FILE* input_file = fopen(filename, "rb"); // open as binary
    // Handle error opening target file
    if (input_file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        COUNTFUNC(FPRINTF_COST+RETURN_COST);
        return MAIN_ERROR_CANT_READ_FILE; // TODO: cahnge for define error
    }

    // Preparing output filename
    char* output_filename = get_file_name(filename);

    // Creating output file
    FILE* output_file = fopen(output_filename, "wb");
    COUNTFUNC(2 * OPEN_FILE_COST + IF_COST + ARITHMETIC_COST);
    if (output_file == NULL){ // Handle error when creating output file
        fprintf(stderr, "Error creating output file: %s\n", output_filename);
        COUNTFUNC(FPRINTF_COST + RETURN_COST);
        return MAIN_ERROR_FILE_PROCESSING;
    }

    // Upon completion, close output file and free result buffer

    // Allocate memory for the result buffer
    char* writting_buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    COUNTFUNC(IF_COST+ARITHMETIC_COST);
    if (writting_buffer == NULL) { // Handle error when allocating the buffer
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION);
        fclose(input_file); // Close the file before returning
        COUNTFUNC(FPRINTF_COST + CLOSE_FILE_COST + RETURN_COST);
        return PREPROCESS_ERROR_MEMORY_ALLOCATION; 
    }

    char* current_token = (char*)malloc(sizeof(char) * BUFFER_SIZE); // buffer of the raw token
    COUNTFUNC(IF_COST+ARITHMETIC_COST);
    if (current_token == NULL) { // Handle error when allocating the buffer
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION);
        fclose(input_file); // Close the file before returning
        COUNTFUNC(FPRINTF_COST + RETURN_COST + CLOSE_FILE_COST);
        return PREPROCESS_ERROR_MEMORY_ALLOCATION; 
    }
    current_token[0] = '\0'; // to prevent 1 bug, dont remove


    DFA dfas[NUM_DFA];
    // Import the alphabet of our DFAs
    char alphabet[ALPHABETLEN] = {ALPHABET};
    COUNTFUNC(3 * ARITHMETIC_COST);

    {
        //----------------------------------------------TYPE DFA----------------------------------------------
        
        // Import accepting state list of type table
        int type_accepting[TYPEACCEPTLEN] = {TYPEACCEPT};
        // Initialize type dfa
        initialize_dfa(&dfas[DFA_TYPES], alphabet, TYPEROWS, TYPECOLUMNS, type_accepting, TYPEACCEPTLEN);
        // Import mapping list of type table
        int type_mapping[ALPHABETLEN] = {TYPEMAPPING};
        // Update dfa mapping list with imported one
        fill_column_mapping(&dfas[DFA_TYPES], alphabet, ALPHABETLEN, type_mapping, TYPELENGTH);
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
        fill_column_mapping(&dfas[DFA_IDENTIFIER], alphabet, ALPHABETLEN, identifier_mapping, IDENTIFIERLENGTH);
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
        fill_column_mapping(&dfas[DFA_KEYWORDS], alphabet, ALPHABETLEN, keyword_mapping, KEYWORDLENGTH);
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
        fill_column_mapping(&dfas[DFA_NUMBERS], alphabet, ALPHABETLEN, number_mapping, NUMBERLENGTH);
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
        fill_column_mapping(&dfas[DFA_SPECIAL_CHAR], alphabet, ALPHABETLEN, special_mapping, SPECIALLENGTH);
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
        fill_column_mapping(&dfas[DFA_OPERATORS], alphabet, ALPHABETLEN, operator_mapping, OPERATORLENGTH);
        // Import transition table of operator table
        int operator_doc_table[OPERATORROWS*OPERATORCOLUMNS] = {OPERATORTABLE};
        // Update dfa transition table with imported one
        fill_transition_table(&dfas[DFA_OPERATORS], operator_doc_table);
        
        //----------------------------------------------LITERAL DFA----------------------------------------------
        
        /*
            // Import accepting state list of literal table
            int literal_accepting[LITERALACCEPTLEN] = {LITERALACCEPT};
            // Initialize literal dfa
            initialize_dfa(&dfas[DFA_LITERALS], alphabet, LITERALROWS, LITERALCOLUMNS, literal_accepting, LITERALACCEPTLEN);
            // Import mapping list of literal table
            int literal_mapping[ALPHABETLEN] = {LITERALMAPPING};
            // Update dfa mapping list with imported one
            fill_column_mapping(&dfas[DFA_LITERALS], alphabet, ALPHABETLEN, literal_mapping, LITERALLENGTH);
            // Import transition table of literal table
            int literal_doc_table[LITERALROWS*LITERALCOLUMNS] = {LITERALTABLE};
            // Update dfa transition table with imported one
            fill_transition_table(&dfas[DFA_LITERALS], literal_doc_table);

        */

            // Import accepting state list of literal table
        int literal_accepting[LITERALACCEPTLEN] = {LITERALACCEPT};
        // Initialize literal dfa
        initialize_dfa(&dfas[DFA_LITERALS], alphabet, LITERALROWS, LITERALCOLUMNS, literal_accepting, LITERALACCEPTLEN);
        // Import mapping list of literal table
        int literal_mapping[ALPHABET_LEN_LITERALS] = {LITERALMAPPING_2};
        // Update dfa mapping list with imported one
        fill_column_mapping(&dfas[DFA_LITERALS], alphabet, ALPHABET_LEN_LITERALS, literal_mapping, LITERAL_MAPPING_LENGHT);
        // Import transition table of literal table
        int literal_doc_table[LITERALROWS*LITERALCOLUMNS] = {LITERALTABLE};
        // Update dfa transition table with imported one
        fill_transition_table(&dfas[DFA_LITERALS], literal_doc_table);





    }
    COUNTFUNC(15 * ARITHMETIC_COST);

    int currentChar = getc(input_file); // Initializing variables to iterate through the file
    int look_ahead = getc(input_file);
    bool is_current_char_delimiter = is_delimiter((char)currentChar);
    bool is_look_ahead_delimiter = is_delimiter((char)look_ahead); 
    bool just_added_enter = true; 
    int writ_buff_idx = 0;
    int curr_token_idx = 0; //also serves as length
    // Read the file character by character
    printf("Starting to actually process file! \n\n"); 
    COUNTFUNC(6 * ARITHMETIC_COST+PRINTF_COST);
    while (currentChar != EOF) {

        current_token[curr_token_idx] = (char)currentChar; 
        curr_token_idx++; 

        //printf("Current char: \t\"%c\" \n", currentChar); 

        /*
        bool is_str_candidate = dfas[DFA_LITERALS].alive; 
        bool is_original_state = dfas[DFA_LITERALS].current_state == START; 
        //printf("%d\n", is_original_state); 
        // && !is_original_state 
        if(is_str_candidate && !is_original_state && (char)currentChar == ' ') {

            //go to next iteration
            currentChar = look_ahead; // update chars
            look_ahead = getc(input_file);
            is_current_char_delimiter = is_look_ahead_delimiter;
            is_look_ahead_delimiter = is_delimiter((char)look_ahead);
            COUNTFUNC(IF_COST+ARITHMETIC_COST*2);
            continue; 
        }*/

        for (int i = 0; i < NUM_DFA; i++)  advance_dfa(&dfas[i], (char)currentChar); 

        bool is_str_candidate = dfas[DFA_LITERALS].alive; 

        if(is_str_candidate) {

            //printf("String candidate! \n"); 
            printf("Current (literal) char: \t\"%c\" \n", (char)currentChar); 
            //printf("%s\n\n", current_token); 
            if((char)currentChar == '\"' && dfas[DFA_LITERALS].current_state != START) {
                is_str_candidate = false; 

            }

        }


        COUNTFUNC(2 * ARITHMETIC_COST + PRINTF_COST);
        //if ((is_current_char_delimiter || is_look_ahead_delimiter)) {
        if ((is_current_char_delimiter || is_look_ahead_delimiter) && !is_str_candidate) {

            /*
                this check ensures that when the lookahead is a delimiter, 
                the token is finalized. Also ensures that if the current char is 
                a delimiter, it will be alone by itself. 
                this way the contents "x * y" will be parsed as "x| |*| |y"
            */

            current_token[curr_token_idx] = '\0'; 


            bool success = false;
            COUNTFUNC(2 * ARITHMETIC_COST);
            for (int i = 0; i < NUM_DFA; i++) {

                success = finalize_dfa(&dfas[i]); 
                
                COUNTFUNC(IF_COST);
                if (success) {

                    char* processed_token = tokenize(i, current_token, curr_token_idx); 
                    if(processed_token == NULL) {
                        COUNTFUNC(IF_COST);
                        break; 
                    }
                    
                    int processed_token_len = strlen(processed_token); 

                    memcpy(&writting_buffer[writ_buff_idx], processed_token, processed_token_len); 
                    free(processed_token); 
                    
                    writ_buff_idx += processed_token_len; 
                    COUNTFUNC(processed_token_len + MEMORY_COPY_COST + FREE_MEMORY_COST);

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
                    COUNTFUNC(processed_token_len+MEMORY_COPY_COST+FREE_MEMORY_COST+ARITHMETIC_COST);

                } // space \n, \r or EOF is not an error
            }

            curr_token_idx = 0; //reset buffer
            current_token[0] = '\0'; 

            for (int i = 0; i < NUM_DFA; i++) reset_dfa(&dfas[i]);
            COUNTFUNC(IF_COST+ARITHMETIC_COST*2);
        }

        //The following ifs 
        if(currentChar == '\n' && !just_added_enter) { 

            writting_buffer[writ_buff_idx++] = '\n'; 
            writting_buffer[writ_buff_idx++] = '\n'; 
            just_added_enter = true; 

        } else if(!(currentChar != '\t' && currentChar != ' ' && currentChar != '\0')) {
            just_added_enter = false; 
        }

        if (BUFFER_SIZE * BUFFER_THRESHOLD < writ_buff_idx) { 
            /*the writting buffer is starting to get full. empty it*/
            writting_buffer[writ_buff_idx] = '\0'; 

            //printf("parsed text added: %s\n\n", writting_buffer); 

            // Write scanner output into output file
            fwrite(writting_buffer, sizeof(char), writ_buff_idx + 1, output_file);

            writ_buff_idx = 0; // start again
            COUNTFUNC(2*ARITHMETIC_COST+PRINTF_COST+WRITE_MEMORY_COST);
        }
        currentChar = look_ahead; // update chars
        look_ahead = getc(input_file);
        is_current_char_delimiter = is_look_ahead_delimiter;
        is_look_ahead_delimiter = is_delimiter((char)look_ahead);
        COUNTFUNC(IF_COST+ARITHMETIC_COST*2);
    }


    // Do last iteration

    {
        //its weird but it could finalize with a valid token
        bool success = false;
        COUNTFUNC(ARITHMETIC_COST);
        for (int i = 0; i < NUM_DFA; i++) {

            success = finalize_dfa(&dfas[i]);
            if (success) {

                char* processed_token = tokenize(i, current_token, curr_token_idx); 
                if(processed_token == NULL) {
                    COUNTFUNC(IF_COST);
                    break; 
                }
                
                int processed_token_len = strlen(processed_token); 

                memcpy(&writting_buffer[writ_buff_idx], processed_token, processed_token_len); 
                free(processed_token); 
                writ_buff_idx += processed_token_len; 

                curr_token_idx = 0; //reset buffer
                COUNTFUNC(2*ARITHMETIC_COST+processed_token_len+MEMORY_COPY_COST+FREE_MEMORY_COST);

                break;
            }
            COUNTFUNC(IF_COST);
        }

        if (!success) {
            if(current_token[0] != ' ') {

                char* processed_token = tokenize(ERROR_TOKEN, current_token, curr_token_idx); 
                // ^current token index is also length
                
                int processed_token_len = strlen(processed_token); 

                memcpy(&writting_buffer[writ_buff_idx], processed_token, processed_token_len); 
                free(processed_token); 
                
                writ_buff_idx += processed_token_len; 
                COUNTFUNC(processed_token_len+MEMORY_COPY_COST+FREE_MEMORY_COST);
            } 
        }

        //finally copy the data to the file

        writting_buffer[writ_buff_idx] = '\0';
        //printf("parsed text added: %s\n\n", writting_buffer); 

        // Write scanner output into output file
        fwrite(writting_buffer, sizeof(char), writ_buff_idx, output_file);
        COUNTFUNC(IF_COST+ARITHMETIC_COST+PRINTF_COST+WRITE_MEMORY_COST);

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
    COUNTFUNC(PRINTF_COST+3*FREE_MEMORY_COST+2*CLOSE_FILE_COST+RETURN_COST);

    return 0; //return success
}

int main(int argc, char *argv[])
{
    // Check if a file name is provided as a command-line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MISSING_FILENAME);
        COUNTFUNC(2*FPRINTF_COST+RETURN_COST);
        return MAIN_ERROR_MISSING_FILENAME;
    }

    printf("Calling processFile! \n"); 
    // Call the processFile function with the filename
    int process_return = processFile(argv[1]);
    // Handle error when  processing target file
    if (process_return != 0) {
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_FILE_PROCESSING);
        COUNTFUNC(FPRINTF_COST + RETURN_COST);
        return MAIN_ERROR_FILE_PROCESSING;
    }
    COUNTFUNC(IF_COST + PRINTF_COST + RETURN_COST); 

    printf("\n\n\tTotal cost of execution: %d\n\n", count_operations); 
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
4.  Move parser.exe file to the folder tests
5.  execute: ./parser test1.c



*/



