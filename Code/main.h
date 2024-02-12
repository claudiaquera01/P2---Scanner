#ifndef MAIN_HEADER
#define MAIN_HEADER

#include "dfatables.h"
#include "errors.h"
#include "scanner.h"
#include "debug.h"
#include "datastructures.h"


#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8191
//^2**13 - 1

#define BUFFER_THRESHOLD 0.75
// when buffer is BUFFER_THRESHOLD, write to file


/*
    TODO: do documentation
*/
int processFile(const char* filename);



#endif
