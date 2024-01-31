#include "main.h"
#include "errors.h"

int main() {


    // Example error handling
    int errorCode;
    errorCode = MAIN_ERROR_CANT_READ_FILE;
    printf("Error: %s\n", ERROR_MESSAGE_CANT_READ_FILE);

    return errorCode;
}