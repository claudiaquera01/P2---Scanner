#include "utils.h"

int count_operations=0;


void sort_chars(char* array, int len) {
    // the trustworthy bubblesort
    char temp;
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                //swap
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

}

char* generate_token(const char* element, int len, const char* token_identifier) {
    int total_length = len + strlen(token_identifier) + 4; // 4 for "<>, " and '\0'
    // Allocate memory for the token string
    char* token = (char*)malloc(sizeof(char) * (total_length));

    if(strcmp(token_identifier, TOKEN_NONRECOGNIZED) == 0 && (strcmp(element, " ") == 0 || strcmp(element, "\n") == 0 || strcmp(element, "\t") == 0)) {
        sprintf(token, "");
    }else {
        // Construct the token string
        sprintf(token, "<%s, %s>", element, token_identifier);
    }
    return token;
}

char* tokenize(int identificator, char* element, int len) {
    char* token = NULL;

    // Based on the accepted DFA and read string, determine the token
    switch (identificator) {
        case DFA_TYPES: 
            printf("Token |%s| identified as TYPE \n", element); 
            token = generate_token(element, len, TOKEN_TYPE);
            break;
        case DFA_IDENTIFIER:
            printf("Token |%s| identified as IDENTIFIER \n", element); 
            token = generate_token(element, len, TOKEN_IDENTIFIER);
            break;
        case DFA_KEYWORDS:
            printf("Token |%s| identified as KEYWORD \n", element); 
            token = generate_token(element, len, TOKEN_KEYWORD);
            break;
        case DFA_NUMBERS:
            printf("Token |%s| identified as NUMBER \n", element); 
            token = generate_token(element, len, TOKEN_NUMBER); 
            break;
        case DFA_SPECIAL_CHAR:
            printf("Token |%s| identified as SPECIAL CHAR \n", element); 
            token = generate_token(element, len, TOKEN_SPECIALCHAR);
            break;
        case DFA_OPERATORS:
            printf("Token |%s| identified as OPERATOR \n", element); 
            token = generate_token(element, len, TOKEN_OPERAND);
            break;
        case DFA_LITERALS:
            printf("Token |%s| identified as \"LITERAL\" \n", element); 
            token = generate_token(element, len, TOKEN_LITERAL);
            break;
        default:
            //if(strcmp(element, " ") == 0 || strcmp(element, "\n") == 0 || strcmp(element, "\t") == 0) {

            printf("Token |%s| UNRECOGNIZED \n", element); 
            token = generate_token(element, len, TOKEN_NONRECOGNIZED); 
    }

    return token;
}

bool is_delimiter(char c) {
    // The list of possible delimiters
    char delimiters[] = {' ', '\t', '\n', '\r', '\0', '+', '*', '=', '>', '(', ')', ';', '{', '}', '[', ']', ','}; 
    //TODO: we should define the delimiters as a constant in the appropiate place 

    int delimiter_len = sizeof(delimiters) / sizeof(char); 
    // We iterate through all the delimiters to check if c matches any of them
    for (int i = 0; i < delimiter_len; i++) {

        if (c == delimiters[i]) {
            return true; // c is a delimiter
        }

    }

    return false; // c is not a delimiter
}

char* get_file_name(const char* argv1) {

    size_t len = strlen(argv1);
    char* output_filename = (char*)malloc(len + strlen("scn") + 1);

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
