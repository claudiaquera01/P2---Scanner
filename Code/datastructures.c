
#include "datastructures.h"


void initialize_dfa(DFA* dfa, char* _alphabet, int _num_states, int* _final_states, int _len_final_states) {

    dfa->alphabet = _alphabet; 
    dfa->len_alphabet = strlen(dfa->alphabet); 

    dfa->num_states = _num_states; 
    dfa->transition_table = (int*)calloc(sizeof(int), dfa->len_alphabet * dfa->num_states); 
    // ^ all the table is initialized to 0. this way, if a connection is not defined, the 
    // DFA will automatically reject the string

    dfa->final_states = _final_states; 
    dfa->len_final_states = _len_final_states; 

    dfa->initial_state = 1; // deafult values
    dfa->current_state = 1; 

    dfa->alive = true; 

}



int get_symbol_index_BS(char* list, int len, char element) {
    
    int l = 0; //left
    int r = len - 1; //right
    int m; //middle

    while(l <= r) {
        m = (l + r) >> 1; // floor  l+r / 2
        if(list[m] < element) {
            l = m + 1; 
        } else if (element < list[m]) {
            r = m - 1; 
        } else { // elemnet == list[m]
            return m; 
        }

    }

    return -1; //unsuccessfull

}



int get_transition_table_element(DFA* dfa, int curr_state, char new_char) {

    if(dfa->num_states < curr_state || curr_state < 0) return -1; 
    //make sure that the state is valid or we risk a bad memory access

    int char_index = get_symbol_index_BS(dfa->alphabet, dfa->len_alphabet, new_char); // get column of the transition table
    if(char_index < 0) return -1; //if not in alphabet return error

    return dfa->transition_table[curr_state * dfa->len_alphabet + char_index]; 

}



void free_dfa(DFA* dfa) {

    free(dfa->transition_table); 
    free(dfa->final_states); 

}







































































