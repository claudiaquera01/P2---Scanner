#ifndef UTILS_HEADER
#define UTILS_HEADER

#define NUM_DFA 7

#define DFA_TYPES 0
#define DFA_IDENTIFIER 1
#define DFA_KEYWORDS 2
#define DFA_NUMBERS 3
#define DFA_SPECIAL_CHAR 4
#define DFA_OPERATORS 5
#define DFA_LITERALS 6

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

/*returns true/false depending on if it is a delimiter or not*/
bool is_delimiter(char *c); // TODO: still not implemented

#endif