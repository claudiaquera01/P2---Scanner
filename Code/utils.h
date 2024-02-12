#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

#include "errors.h"








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

// Counting operations //////////

int count=0;
#define IF_COST 1
#define FPRINTF_COST 50
#define WRITE_MEMORY_COST 50
#define PRINTF_COST 1
#define LECTURE_MEMORY_COST 50
#define RETURN_COST 1
#define KEEP_MEMORY 10
#define STRING_LEN_COST 5
#define CLOSE_FILE_COST 20
#define ARITHMETIC_COST 1
#define MEMORY_COPY_COST 20
#define FREE_MEMORY_COST 20
#define PRE_FUNC_COST 10

// /////////////////////////////


/**
Sorts the caracters in the array. len is the length of the array.

Note that array needs to be mutable, therefore using the following will not work:

    char* my_text = "cute reflection";
    sort_chars(my_text, strlen(my_text));

To easly fix it, substitute by the following.

    char my_text[] = "cute reflection";
    sort_chars(my_text, strlen(my_text));


 * Sorts characters in an array using bubble sort algorithm.
 * 
 * @param array The array of characters to be sorted
 * @param len The length of the array
 */
void sort_chars(char *array, int len);

/** 
 * Helper function to indicate if a certain character is a delimiter or not.
 * 
 * @param c The character we want to know if it is an delimiter
 * @return True if c is a delimiter or false otherwise.
*/
bool is_delimiter(char c); 


/**
    returns "<element, IDENTIFIACOR_TAG>\0"  //includes the /0
    identificator is the id of the dfa (i.e. DFA_IDENTIFIER, DFA_OPERATORS, ERROR_TOKEN...) 
    (look at the top of utils.h). does NOT hold ownership of element. 

    len is the length of element. 

    element is the string that was identified by the DFA. 

 * Tokenizes an element based on its identifier and length
 * 
 * @param identificator The identifier of the element
 * @param element The element to be tokenized
 * @param len The length of the element
 * @return The tokenized string
 */
char* tokenize(int identificator, char* element, int len); 



/** 
 * Helper function to generate token based on identifier and element
 * 
 * @param element The element for which the token is being generated
 * @param len The length of the element
 * @param token_identifier The identifier tag for the token
 * @return The generated token string
 */
char* generate_token(const char* element, int len, const char* token_identifier);




/*
    based on the name of the file, creates the name of the output file
*/
char* get_file_name(const char *argv1); 























#endif
