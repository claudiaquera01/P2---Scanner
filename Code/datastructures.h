#ifndef TOKEN_HEADER
#define TOKEN_HEADER
#define MAX_LEXEME_LENGTH 100
typedef enum {
    CAT_NUMBER,
    CAT_IDENTIFIER,
    CAT_KEYWORD,
    CAT_LITERAL,
    CAT_OPERAND,
    CAT_SPECIALCHAR,
    CAT_NONRECOGNIZED
} TokenCategory;

// Define token structure
typedef struct {
    char lexeme[MAX_LEXEME_LENGTH];
    TokenCategory category;
    int line_number; // For DEBUG mode
} Token;

//functions
#endif