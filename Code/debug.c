#include "debug.h"

int num = 1;
int debug = DEBUG_OFF; 
//int debug = DEBUG_ON; 

char* debug_mode(const char* element, int len, const char* token_identifier) {
    // Allocate memory for the token string
    char* token = (char*)malloc(sizeof(char) * (len + BUFFER_LEN));
    if (token == NULL) {
        // TODO: Handle memory allocation failure
        return NULL;
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
        COUNTFUNC(3*ARITHMETIC_COST + PRINTF_COST + IF_COST);

        if(strcmp(DEBUG_KEY, element) == 0){
            //sprintf(token, "\n ");  // Add the number before the token
            strcat(token, "\n ");
        } 
        
        char* aux = generate_token(element, len, token_identifier); 

        strcat(token, aux); 
        //free(aux); 
        // ^freeing this is giving an error and is driving me crazy
        aux = generate_token(element, len, token_identifier); 
        //strcat(token, aux); 


        //strcat(token, generate_token(element, len, token_identifier));

        //sprintf(token, " ");  // Add space to avoid rare characters 

        
        /*
        char* aux = generate_token(element, len, token_identifier); 
        strcat(token, aux);
        free(aux); 

        sprintf(token, " ");  // Add space to avoid rare characters 

        aux = generate_token(element, len, token_identifier); //I do not understand why we need to generate token twice, but i freed the requested memory
        strcat(token, aux);
        free(aux); */
        
    }

    return token;
}
