#ifndef DEBUG_HEADER
#define DEBUG_HEADER
#include <stdio.h>
// Define DEBUG directive
#define DEBUG_ON 1
#define DEBUG_OFF 0
#include "datastructures.h"
// Functions
void output_tokens_debug(FILE* output_file, Token* tokens, int num_tokens, int debug_mode);

#endif /* DEBUG_H */
