#include "utils.h"

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

/* #define DFA_TYPES 0
#define DFA_IDENTIFIER 1
#define DFA_KEYWORDS 2
#define DFA_NUMBERS 3
#define DFA_SPECIAL_CHAR 4
#define DFA_OPERATORS 5
#define DFA_LITERALS 6
#define ERROR_TOKEN -1 */

char* tokenize(int accepted_dfa, const char* read_string) {
    
    char* token = NULL;

    // Based on the accepted DFA and read string, determine the token
    if (accepted_dfa == 1) {
        // Example tokenization logic
        token = malloc(sizeof(char) * (strlen("TOKEN_TYPE_1") + 1));
        strcpy(token, "TOKEN_TYPE_1");
    } else if (accepted_dfa == 2) {
        // Example tokenization logic
        token = malloc(sizeof(char) * (strlen("TOKEN_TYPE_2") + 1));
        strcpy(token, "TOKEN_TYPE_2");
    } else {
        // Default tokenization logic
        token = malloc(sizeof(char) * (strlen("UNKNOWN_TOKEN") + 1));
        strcpy(token, "UNKNOWN_TOKEN");
    }

    return token;
}


