#include "debug.h"

int num=0;
char* debug_mode(char* element , int identificator, int len, int debug_mode) {
    // Write tokens in the output version
    char* token=(char*)malloc(sizeof(char) * (len+4));
    if(debug_mode==DEBUG_ON){
        if(num==START){
            printf("\n %d ",num);
            sprintf(token, "\n %d",num);
            num++;
            COUNTFUNC(2*PRINTF_COST+ARITHMETIC_COST);
        }
        if(strcmp(DEBUG_KEY,element)==0){
            token=tokenize(identificator, element, len);
            printf("\n %d ",num);
            sprintf(token, "\n %d",num);
            num++;
            COUNTFUNC(2*PRINTF_COST+ARITHMETIC_COST);
        }else{
            token=tokenize(identificator, element, len);
        }
        COUNTFUNC(2*IF_COST);
    }else{
        token=(char*)malloc(sizeof(char) * (len));
        token=tokenize(identificator, element, len);
        COUNTFUNC(ARITHMETIC_COST);
    }
    COUNTFUNC(ARITHMETIC_COST+RETURN_COST+IF_COST);
    return token;
}
