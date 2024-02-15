#include "utils.h"

int count_operations = 0;
char delimiters[] = {' ', '\t', '\n', '\r', '\0', '+', '*', '=', '>', '(', ')', ';', '{', '}', '[', ']', ','};

void sort_chars(char* array, int len) {
    // the trustworthy bubblesort
    char temp;
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            COUNTFUNC(ARITHMETIC_COST * 2 + 3 * IF_COST);
            if (array[j] > array[j + 1]) {
                //swap
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                COUNTFUNC(ARITHMETIC_COST * 3);
            }
        }
    }

}

bool mustIgnoreElement(const char* element){
    COUNTFUNC(IF_COST * 5 + RETURN_COST);
    return (strcmp(element, " ") == 0 ||
            strcmp(element, "\n") == 0 ||
            strcmp(element, "\t") == 0 ||
            strcmp(element, "\r") == 0 ||
            strcmp(element, "\0") == 0);
}

char* generate_token(const char* element, int len, const char* token_identifier) {
    int total_length = len + strlen(token_identifier) + 4; // 4 for "<>, " and '\0'
    // Allocate memory for the token string
    char* token = (char*)malloc(sizeof(char) * (total_length));
    COUNTFUNC(ARITHMETIC_COST * 2 + 2 * IF_COST);

    if (mustIgnoreElement(element)) {
        //sprintf(token, " ");
        //COUNTFUNC(FPRINTF_COST); 
        token[0] = '\0'; // add nothing
        COUNTFUNC(ARITHMETIC_COST);


    } else {
        // Construct the token string
        sprintf(token, "<%s, %s> ", element, token_identifier);
        COUNTFUNC(FPRINTF_COST); 
    }
    COUNTFUNC(RETURN_COST);
    return token;
}

char* tokenize(int identificator, char* element, int len) {
    char* token = NULL;

    COUNTFUNC(ARITHMETIC_COST*2 + PRINTF_COST);
    // Based on the accepted DFA and read string, determine the token
    switch (identificator) {
        case DFA_TYPES:
            printf("Token |%s| identified as TYPE \n", element);
            token = debug_mode(element, len, TOKEN_TYPE);
            break;
        case DFA_IDENTIFIER:
            printf("Token |%s| identified as IDENTIFIER \n", element);
            token = debug_mode(element, len, TOKEN_IDENTIFIER);
            break;
        case DFA_KEYWORDS:
            printf("Token |%s| identified as KEYWORD \n", element);
            token = debug_mode(element, len, TOKEN_KEYWORD);
            break;
        case DFA_NUMBERS:
            printf("Token |%s| identified as NUMBER \n", element);
            token = debug_mode(element, len, TOKEN_NUMBER);
            break;
        case DFA_SPECIAL_CHAR:
            printf("Token |%s| identified as SPECIAL CHAR \n", element);
            token = debug_mode(element, len, TOKEN_SPECIALCHAR);
            break;
        case DFA_OPERATORS:
            printf("Token |%s| identified as OPERATOR \n", element);
            token = debug_mode(element, len, TOKEN_OPERAND);
            break;
        case DFA_LITERALS:
            printf("Token |%s| identified as \"LITERAL\" \n", element);
            token = debug_mode(element, len, TOKEN_LITERAL);
            break;
        default:
            printf("Token |%s| UNRECOGNIZED \n", element);
            token = debug_mode(element, len, TOKEN_NONRECOGNIZED);
    }
    COUNTFUNC(RETURN_COST);
    return token;
}

bool is_delimiter(char c) {
    // The list of possible delimiters
    //char delimiters[] = {' ', '\t', '\n', '\r', '\0', '+', '*', '=', '>', '(', ')', ';', '{', '}', '[', ']', ','};

    int delimiter_len = sizeof(delimiters) / sizeof(char);
    COUNTFUNC(ARITHMETIC_COST + RETURN_COST);
    // We iterate through all the delimiters to check if c matches any of them
    for (int i = 0; i < delimiter_len; i++) {
        COUNTFUNC(IF_COST*2 + ARITHMETIC_COST);
        if (c == delimiters[i]) {
            return true; // c is a delimiter
        }

    }

    return false; // c is not a delimiter
}

char* get_file_name(const char* argv1) {

    size_t len = strlen(argv1);
    char* output_filename = (char*)malloc(len + strlen("scn") + 1);
    COUNTFUNC(ARITHMETIC_COST * 2);

    // Check if memory allocation was successful
    if (output_filename == NULL) {
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MEMORY_ALLOCATION);
        COUNTFUNC(FPRINTF_COST + IF_COST);
        exit(EXIT_FAILURE);
    }

    // Copy the input filename to the output filename, appending scn to it
    strcpy(output_filename, argv1);
    strcat(output_filename, "scn");

    COUNTFUNC(RETURN_COST);
    return output_filename;
}
