#ifndef UTILS_HEADER 
#define UTILS_HEADER





/*
Sorts the caracters in the array. len is the length of the array. 

Note that array needs to be mutable, therefore using the following will not work: 

    char* my_text = "cute reflection"; 
    sort_chars(my_text, strlen(my_text));

To easly fix it, substitute by the following. 

    char my_text[] = "cute reflection"; 
    sort_chars(my_text, strlen(my_text));

*/
void sort_chars(char* array, int len); 





#endif