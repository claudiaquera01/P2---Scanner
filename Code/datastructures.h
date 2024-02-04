#ifndef TOKEN_HEADER
#define TOKEN_HEADER



#include <stdlib.h>

#include <string.h>
#include <stdbool.h>


#include "utils.h"



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
typedef struct { //TODO: <- there is a name mussing here after struct (use something like struct_token)
    char lexeme[MAX_LEXEME_LENGTH];
    TokenCategory category;
    int line_number; // For DEBUG mode
} Token;




/*
Represents a Deterministic Finite Automata (DFA, https://en.wikipedia.org/wiki/Deterministic_finite_automaton)

alphabet is a reference to a string containing all valid symbols of the alphabet 
of the automata (sigma). alphabet is a reference and DFA does NOT own it. 
Assumes that the characters in alphaber are SORTED increasingly. Also assumes alphabet 
is constant. 

len_alphabet is the length of the alphabet. 

Each state is represented as an integer. The state 0 is reserved for the rejecting state. 
Also note that the state 1 is the deafult state for the initial state (q0), 
although it can be changed. (but better don't)

num_states is the number of valid states and represents the states (q). 
It counts the number of valid states NOT includeing the rejecting state. 
ex: if num_states == 1, then there will only be the rejecting state (0) and 
the state 1. if num_states == 4, then ther will be the rejecting state (0) 
and the states 1, 2, 3, 4. 

final_states is a list of all the accepting states (F). It should NOT include 0. 
len_final_states is the length of final_states. DFA holds ownership of final_states

current_state is the current state of the automata. 

transition_table (delta) is a matrix that holds all necessary information to 
traverse the DFA. It can be accessed as transition_table[state * (len_alphabet) + symbol_index]
However some usefull functions for doing that are provided, get_dfa_transition_table_value() 
and set_dfa_transition_table_value(). DFA holds ownership of transition_table

alive is true if the automata has NOT reached the rejectiong state (0). 

*/
typedef struct struct_dfa {

    char* alphabet; 
    int len_alphabet; 

    int num_states;     
    int* transition_table; 
    int initial_state; 
    int current_state; 

    int* final_states; 
    int len_final_states; 

    bool alive; 

} DFA; 



//functions

/*
initializes the DFA with the given data. DFA does NOT take ownership of alphabet 
but DOES takeownership of final_states. read the definition of DFA for more info. 
Also note that the alphabet must be constant during the live of the dfa and must be SORTED

Note: the transition table is initialized to values of 0 (go to rejecting state), 
the correct values must be set later. see set_dfa_transition_table_value()
*/
void initialize_dfa(DFA* dfa, char* _alphabet, int _num_states, int* _final_states, int _len_final_states); 

/*
moves the dfa to the next state (according to dfa.current_state, dfa.transition_table 
and symbol)
*/
void move_dfa(DFA* dfa, char symbol); 

/*
    checks if dfa is in end state. returns true if dfa accepts or false otherwise
*/
bool finalize_dfa(DFA* dfa); 

/*
    resets the dfa back to the initial state and back to being alive
*/
void reset_dfa(DFA* dfa); 

/*
uses binary search to determinate the index of the element element in list. 
list must be sorted and len is the length of the list. 

returns the index of element or -1 if the element is not found in the list

this will be used in the dfa for moving the state with the transition table

*/
int get_symbol_index_BS(char* list, int len, char element); 

/*
returns the new state a dfa would go from curr_state when reciving new_char. 
curr_state must be a valid state and new_char must be in the alphabet of the dfa. 
the dfa must be valid and initialized. 

returns the new state or negative value on error: 
returns 0 on succses, or a negative value on error: 
    -1: invalid state: state is neagtive or greater than dfa.num_states
    -2: invalid symbol: char is not in the alphabet
*/
int get_dfa_transition_table_value(DFA* dfa, int curr_state, char symbol); 

/*
modifies a value in the transition table of a dfa. the dfa must be initialized and valid. 
In short, if a dfa is in the state state and recives symbol, this function will set the 
transition value so it goes to new_state. 

returns 0 on succses, or a negative value on error: 
    -1: invalid state: state is neagtive or greater than dfa.num_states
    -2: invalid symbol: char is not in the alphabet
    -3: invalid state: new_state is neagtive or greater than dfa.num_states

*/
int set_dfa_transition_table_value(DFA* dfa, int state, char symbol, int new_state); 

/*
frees all the contents inside the dfa. does NOT free alphabet nor the dfa itself .
*/
void free_dfa(DFA* dfa); 





























#endif