#include "debug.h"

int num = 1;
int debug = DEBUG_OFF; 
//int debug = DEBUG_ON; 

char* debug_mode(const char* element, int len, const char* token_identifier) {
    // Allocate memory for the token string
    char* token = (char*)malloc(sizeof(char) * (len + BUFFER_LEN));
    if (token == NULL) {
        return DEBUG_MODE_ERROR_MEMORY_ALLOCATION;
    }

    token[0] = '\0'; 

    if(mustIgnoreElement(element)) {
        return token; 
    }

    if (debug == DEBUG_ON) {
        if (num == START) {
            sprintf(token, "\n %d ", num);
            num++;
            COUNTFUNC(ARITHMETIC_COST+PRINTF_COST);
        }

        if(strcmp(DEBUG_KEY,element) == 0){
            sprintf(token, "\n %d ", num);  // Add the number before the token
            COUNTFUNC(PRINTF_COST);
        }
        strcat(token, generate_token(element, len, token_identifier));
        //TODO: ^free memory

        if(strcmp(DEBUG_KEY, element) == 0){
            num++;
            COUNTFUNC(ARITHMETIC_COST);
        }
        //num++;
        COUNTFUNC(ARITHMETIC_COST + PRINTF_COST + 2*IF_COST);
    } else {
        token=generate_token(element, len, token_identifier);
        
    }

    return token;
}
