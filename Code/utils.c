#include "utils.h"

/**
 * Sorts characters in an array using bubble sort algorithm.
 * 
 * @param array The array of characters to be sorted
 * @param len The length of the array
 */
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

/** 
 * Helper function to generate token based on identifier and element
 * 
 * @param element The element for which the token is being generated
 * @param len The length of the element
 * @param token_identifier The identifier tag for the token
 * @return The generated token string
 */
char* generate_token(const char* element, int len, const char* token_identifier) {
    int total_length = len + strlen(token_identifier) + 4; // 4 for "<>, " and '\0'
    // Allocate memory for the token string
    char* token = (char*)malloc(sizeof(char) * (total_length));
    // Construct the token string
    sprintf(token, "<%s, %s>", element, token_identifier);
    return token;
}

/** 
 * Tokenizes an element based on its identifier and length
 * 
 * @param identificator The identifier of the element
 * @param element The element to be tokenized
 * @param len The length of the element
 * @return The tokenized string
 */
char* tokenize(int identificator, char* element, int len) {
    char* token = NULL;

    // Based on the accepted DFA and read string, determine the token
    switch (identificator) {
        case DFA_TYPES:
            token = generate_token(element, len, TOKEN_TYPE);
            break;
        case DFA_IDENTIFIER:
            token = generate_token(element, len, TOKEN_IDENTIFIER);
            break;
        case DFA_KEYWORDS:
            token = generate_token(element, len, TOKEN_KEYWORD);
            break;
        case DFA_NUMBERS:
            token = generate_token(element, len, TOKEN_NUMBER);
            break;
        case DFA_SPECIAL_CHAR:
            token = generate_token(element, len, TOKEN_SPECIALCHAR);
            break;
        case DFA_OPERATORS:
            token = generate_token(element, len, TOKEN_OPERAND);
            break;
        case DFA_LITERALS:
            token = generate_token(element, len, TOKEN_LITERAL);
            break;
        default:
            token = generate_token(element, len, TOKEN_NONRECOGNIZED);
    }

    return token;
}





