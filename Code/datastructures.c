
#include "datastructures.h"
#include "dfatables.h"

void initialize_dfa(DFA* dfa, char* _alphabet, int _num_states, int _num_columns, int* _final_state, int _final_state_len) { 


    dfa->alphabet = _alphabet; 
    dfa->len_alphabet = strlen(dfa->alphabet); 

    dfa->num_columns = _num_columns; 
    dfa->column_map = (int*)calloc(_num_columns, sizeof(int)); 

    dfa->num_states = _num_states; 
    dfa->transition_table = (int*)calloc(sizeof(int), _num_columns * dfa->num_states); 
    // ^ all the table is initialized to 0. this way, if a connection is not defined, the 
    // DFA will automatically reject the string

    dfa->final_states = _final_state; 
    dfa->len_final_states = _final_state_len; 

    dfa->initial_state = INITIALSTATE; // default values
    dfa->current_state = INITIALSTATE;

    dfa->alive = true; 

}

int set_symbol_mapping(DFA* dfa, char symb, int col) {

    int index = get_symbol_index_BS(dfa->alphabet, dfa->len_alphabet, symb); 

    if(index == -1) return -1; 

    dfa->column_map[index] = col; 


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

int get_dfa_transition_table_value(DFA* dfa, int curr_state, int column) {

    if(dfa->num_states < curr_state || curr_state < 0) return -1; 
    //make sure that the state is valid or we risk a bad memory access

    return dfa->transition_table[curr_state * dfa->len_alphabet + column]; 

}

int set_dfa_transition_table_value(DFA* dfa, int state, int column, int new_state) {

    if(dfa->num_states < state || state < 0) return -1; 
    if(dfa->num_states < new_state || new_state < 0) return -2; 
    //make sure that the state is valid or we risk a bad memory access

    dfa->transition_table[state * dfa->len_alphabet + column] = new_state; 
    return 0; //success

}

void advance_dfa(DFA* dfa, char symbol) {

    int char_index = get_symbol_index_BS(dfa->alphabet, dfa->len_alphabet, symbol); // get column of the transition table
    if(char_index == -1) { //reject
        //symbol is not in the alphabet
        dfa->current_state = REJECTSTATE;
        dfa->alive = false; 
        return; 
    } 

    int column_index = dfa->column_map[char_index]; 
    
    int new_state = dfa->transition_table[dfa->current_state * dfa->len_alphabet + column_index]; 
    // ^ compute new state
    dfa->current_state = new_state; //go to new state

    if(new_state == 0) { 
        //has been rejected
        dfa->alive = false; 
    }


}

bool finalize_dfa(DFA* dfa) {

    if(!dfa->alive) return false; //fast return

    int final_state = dfa->current_state; 

    for(int i = 0; i < dfa->len_final_states; i++) {

        if(final_state == dfa->final_states[i]) {
            return true; 
        }
    }

    return false; 
}

void reset_dfa(DFA* dfa) {
    dfa->current_state = INITIALSTATE;
    dfa->alive = true; 
}

void free_dfa(DFA* dfa) {

    //int whileif = 0; 
    //viva la revoluction!!!!

    
    free(dfa->final_states); 
    free(dfa->transition_table);

}







































































