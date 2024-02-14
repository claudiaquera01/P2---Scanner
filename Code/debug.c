#include "debug.h"
int num=0;
char* debug_mode(const char* element, int len, const char* token_identifier) {
    // Allocate memory for the token string
    char* token = (char*)malloc(sizeof(char) * (len + BUFFER_LEN));
    if (token == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    if (debug == DEBUG_ON) {
        if (num == START) {
            sprintf(token, "\n %d ", num);
            num++;
            COUNTFUNC(ARITHMETIC_COST+PRINTF_COST);
        }
        if(strcmp(DEBUG_KEY,element)==0){
            sprintf(token, "\n %d ", num);  // Add the number before the token
            COUNTFUNC(PRINTF_COST);
        }
        strcat(token, generate_token(element, len, token_identifier));

        if(strcmp(DEBUG_KEY,element)==0){
            num++;
            COUNTFUNC(ARITHMETIC_COST);
        }
        //num++;
        COUNTFUNC(ARITHMETIC_COST + PRINTF_COST + 2*IF_COST);
    } else {
        if(strcmp(DEBUG_KEY,element)==0){
            //sprintf(token, "\n ");  // Add the number before the token
            strcat(token, "\n ");
        }
        strcat(token, generate_token(element, len, token_identifier));

        sprintf(token, " ");  // Add space to avoid rare characters
        strcat(token, generate_token(element, len, token_identifier));
        COUNTFUNC(3*ARITHMETIC_COST + PRINTF_COST + IF_COST);
    }
    return token;
}
