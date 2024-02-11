#ifndef UTILS_HEADER
#define UTILS_HEADER

#define NUM_DFA 7
// total number of dfas

// identifier for dfas
#define DFA_TYPES 0
#define DFA_IDENTIFIER 1
#define DFA_KEYWORDS 2
#define DFA_NUMBERS 3
#define DFA_SPECIAL_CHAR 4
#define DFA_OPERATORS 5
#define DFA_LITERALS 6

#define ERROR_TOKEN -1


#define TOKEN_TYPE "CAT_TYPE" 
#define TOKEN_IDENTIFIER "CAT_IDENTIFIER"
#define TOKEN_KEYWORD "CAT_KEYWORD"
#define TOKEN_NUMBER "CAT_NUMBER"
#define TOKEN_SPECIALCHAR "CAT_SPECIALCHAR"
#define TOKEN_OPERAND "CAT_OPERAND"
#define TOKEN_LITERAL "CAT_LITERAL"
#define TOKEN_NONRECOGNIZED "CAT_NONRECOGNIZED"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

/*
Sorts the caracters in the array. len is the length of the array.

Note that array needs to be mutable, therefore using the following will not work:

    char* my_text = "cute reflection";
    sort_chars(my_text, strlen(my_text));

To easly fix it, substitute by the following.

    char my_text[] = "cute reflection";
    sort_chars(my_text, strlen(my_text));

*/
void sort_chars(char *array, int len);


//Returns true if c is a delimiter or false if it is not

bool is_delimiter(char c); 


/*
returns "<element, IDENTIFIACOR_TAG>\0"  //includes the /0
identificator is the id of the dfa (i.e. DFA_IDENTIFIER, DFA_OPERATORS, ERROR_TOKEN...) 
(look at the top of utils.h). does NOT hold ownership of element. 

len is the length of element. 

element is the string that was identified by the DFA. 

*/
char* tokenize(int identificator, char* element, int len); 
char* generate_token(const char* element, int len, const char* token_identifier);


#endif