#include "main.h"
#include "errors.h"

int main(int argc, char *argv[]) {
    // Check if a file name is provided as a command-line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_MISSING_FILENAME);
        return MAIN_ERROR_MISSING_FILENAME;
    }

    // Open the file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        fprintf(stderr, "Error: %s\n", ERROR_MESSAGE_CANT_READ_FILE);
        return MAIN_ERROR_CANT_READ_FILE;
    }

    // Read the file character by character
    int currentChar;
    while ((currentChar = getc(file)) != EOF) {
        // Process the current character (you'll add your logic here)
        // For now, let's just print each character
        printf("%c", (char)currentChar);
    }

    // Close the file
    fclose(file);

    return SCANNER_SUCCESS;
}
