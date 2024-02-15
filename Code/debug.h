#ifndef DEBUG_HEADER
#define DEBUG_HEADER


#include <stdio.h>
#include "datastructures.h"
#include "utils.h" 



// Define DEBUG directive
#define DEBUG_ON 1
#define DEBUG_OFF 0
#define DEBUG_KEY "\n"
#define START 0
#define BUFFER_LEN 400


extern int debug;

extern int num;

// Functions: 


/** 
    We use the function tokenize to get the token but we can apply the normal mode, 
    or the debug mode
*/
char* debug_mode(const char* element, int len, const char* token_identifier);


#endif 