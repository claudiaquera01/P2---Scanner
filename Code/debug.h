#ifndef DEBUG_HEADER
#define DEBUG_HEADER
#include <stdio.h>
// Define DEBUG directive
#define DEBUG_ON 1
#define DEBUG_OFF 0
#define DEBUG_KEY "\n"
#define START 0
extern int debug;
extern int num;
#include "datastructures.h"
#include "utils.h"
// Functions
/* We use the function tokenize to get the token but we can apply the normal mode, or the debug mode*/
//char* debug_mode(int debug_mode; char* element , int identificator, int len, int debug_mode);
char* debug_mode(const char* element, int len, const char* token_identifier);
#endif /* DEBUG_H */
