
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

    dfa->initial_state = 1; // default values
    dfa->current_state = 1; 

    dfa->alive = true; 

}

int get_symbol_index_BS(char* list, int len, char element) {
    //binary search
    int l = 0; //left
    int r = len - 1; //right
    int m; //middle

    while(l <= r) {
        m = (l + r) >> 1; // floor  l+r / 2
        if(list[m] < element) {
            l = m + 1; 
        } else if (element < list[m]) {
            r = m - 1; 
        } else { // element == list[m]
            return m; 
        }

    }

    return -1; //unsuccessful

}

int get_dfa_transition_table_value(DFA* dfa, int curr_state, char symbol) {

    if(dfa->num_states < curr_state || curr_state < 0) return -1; 
    //make sure that the state is valid or we risk a bad memory access

    int char_index = get_symbol_index_BS(dfa->alphabet, dfa->len_alphabet, symbol); // get column of the transition table
    if(char_index < 0) return -2; //if not in alphabet return error

    return dfa->transition_table[curr_state * dfa->len_alphabet + char_index]; 

}

int set_dfa_transition_table_value(DFA* dfa, int state, char symbol, int new_state) {

    if(dfa->num_states < state || state < 0) return -1; 
    if(dfa->num_states < new_state || new_state < 0) return -3; 
    //make sure that the state is valid or we risk a bad memory access

    int char_index = get_symbol_index_BS(dfa->alphabet, dfa->len_alphabet, symbol); // get column of the transition table
    if(char_index < 0) return -2; //if not in alphabet return error

    dfa->transition_table[state * dfa->len_alphabet + char_index] = new_state; 
    return 0; //success

}

void advance_dfa(DFA* dfa, char symbol) {
    int char_index = get_symbol_index_BS(dfa->alphabet, dfa->len_alphabet, symbol); // get column of the transition table
    if(char_index == -1) { //reject
        dfa->current_state = 0; 
        dfa->alive = false; 
        return; 
    }
    
    int new_state = dfa->transition_table[dfa->current_state * dfa->len_alphabet + char_index]; 
    // ^ compute new state
    dfa->current_state = new_state; //go to new state

    if(new_state == 0) { 
        //has been rejected
        dfa->alive = false; 
    }


}

bool finalize_dfa(DFA* dfa) {

    if(!dfa->alive) return false; 

    int final_state = dfa->current_state; 

    for(int i = 0; i < dfa->len_final_states; i++) {

        if(final_state == dfa->final_states[i]) {
            return true; 
        }
    }

    return false; 
}

void reset_dfa(DFA* dfa) {
    dfa->current_state = 1; 
    dfa->alive = true; 
}

void free_dfa(DFA* dfa) {

    free(dfa->transition_table); 
    free(dfa->final_states); 

}







































































