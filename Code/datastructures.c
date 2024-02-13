
#include "datastructures.h"
#include "dfatables.h"
#include "utils.h"

void initialize_dfa(DFA* dfa, char* _alphabet, int _num_states, int _num_columns, int* _final_state, int _final_state_len) { 

	COUNTFUNC(LECTURE_MEMORY_COST * 3); // Memory allocation costs for alphabet, final_state and column map

    dfa->alphabet = _alphabet; 
    dfa->len_alphabet = strlen(dfa->alphabet); 

    dfa->num_columns = _num_columns; 
    dfa->column_map = (int*)calloc(dfa->len_alphabet, sizeof(int));
	COUNTFUNC(WRITE_MEMORY_COST + 4*ARITHMETIC_COST);

    dfa->num_states = _num_states; 
    dfa->transition_table = (int*)calloc(sizeof(int), _num_columns * (dfa->num_states + 1)); 
    // ^ all the table is initialized to 0. this way, if a connection is not defined, the 
    // DFA will automatically reject the string. +1 is for rejecting state
	COUNTFUNC(LECTURE_MEMORY_COST + 7*ARITHMETIC_COST);

    dfa->final_states = _final_state; 
    dfa->len_final_states = _final_state_len; 

    dfa->initial_state = INITIALSTATE; // default values
    dfa->current_state = INITIALSTATE;

    dfa->alive = true;


}


int set_symbol_mapping(DFA* dfa, char symb, int col) {

    int index = get_symbol_index_BS(dfa->alphabet, dfa->len_alphabet, symb); 

	COUNTFUNC(IF_COST + RETURN_COST + ARITHMETIC_COST);
    if(index == -1){
		return -1; //return error and avoid bad memory access
	}

    COUNTFUNC(ARITHMETIC_COST);
    dfa->column_map[index] = col;

    return 0;
}



/*TODO: alphabet length is already on dfa. Its not needed. We should get the lenght of 
the mapping vector and check that it has the same length as the alphabet length. */
int fill_column_mapping(DFA* dfa, char* _alphabet, int alphabet_length, int* mapping_vector) {

    int mapping_vector_len = -1; //TODO: put this as a perameter
	COUNTFUNC(ARITHMETIC_COST + IF_COST + RETURN_COST);

    if(alphabet_length < mapping_vector_len){
		return 2; //crash for bad memory access
	}

    // Copy documentation mapping into dfa column mapping
    int alphabet_len = dfa->len_alphabet;
    COUNTFUNC(ARITHMETIC_COST);
    for(int i = 0; i < alphabet_len; i++){
		COUNTFUNC(IF_COST + ARITHMETIC_COST); // For conditional checks of i
        set_symbol_mapping(dfa, _alphabet[i], mapping_vector[i]);
    }

    return (int)(alphabet_length != mapping_vector_len); 
    //^returns 0 if the lengths are exact or 1 if not (some mapping vector positions are left unchaged). 
}

int get_dfa_transition_table_value(DFA* dfa, int curr_state, int column) {

    COUNTFUNC(IF_COST * 2 + RETURN_COST); //IF_COST for the conditional checks
    if(dfa->num_states < curr_state || curr_state < 0) {
        return -1;
    } //make sure that the state is valid or we risk a bad memory access

    COUNTFUNC(ARITHMETIC_COST);
    return dfa->transition_table[curr_state * dfa->len_alphabet + column];
}


int set_dfa_transition_table_value(DFA* dfa, int state, int column, int new_state) {

	COUNTFUNC(IF_COST * 4 + RETURN_COST); // IF_COST for the conditional checks (2 per if)
    if(dfa->num_states < state || state < 0) return -1; 
    if(dfa->num_states < new_state || new_state < 0) return -2; 
    //make sure that the state is valid or we risk a bad memory access

	COUNTFUNC(ARITHMETIC_COST)
    dfa->transition_table[state * dfa->num_columns + column] = new_state;
    return 0; //success

}

int fill_transition_table(DFA* dfa, int* doc_table) {
    // Copy documentation transition table into dfa transition table
    for (int i = 0; i < dfa->num_states; i++) {
		COUNTFUNC(IF_COST + ARITHMETIC_COST);
        for (int j = 0; j < dfa->num_columns; j++) {
			COUNTFUNC(IF_COST + ARITHMETIC_COST*2);
            set_dfa_transition_table_value(dfa, i, j, doc_table[i * dfa->num_columns + j]);
        }
    }
	COUNTFUNC(RETURN_COST);
    return 0;
}


void advance_dfa(DFA* dfa, char symbol) {

	COUNTFUNC(IF_COST * 2 + RETURN_COST);
    int char_index = get_symbol_index_BS(dfa->alphabet, dfa->len_alphabet, symbol); // get column of the transition table
    if(char_index == -1) { //reject
        //symbol is not in the alphabet
        dfa->current_state = REJECTSTATE;
        dfa->alive = false; 
        return; 
    } 

    int column_index = dfa->column_map[char_index];
    
    int new_state = dfa->transition_table[dfa->current_state * dfa->num_columns + column_index];
    // ^ compute new state
	COUNTFUNC(ARITHMETIC_COST * 2);
    dfa->current_state = new_state; //go to new state

    if(new_state == 0) { 
        //has been rejected
        dfa->alive = false;
        COUNTFUNC(ARITHMETIC_COST);
    }


}


bool finalize_dfa(DFA* dfa) {

	COUNTFUNC(IF_COST + RETURN_COST);
    if(!dfa->alive) return false; //fast return

    int final_state = dfa->current_state;
    COUNTFUNC(ARITHMETIC_COST);

    for(int i = 0; i < dfa->len_final_states; i++) {
		COUNTFUNC(IF_COST*2 + ARITHMETIC_COST); // If cost for the i check and the if inside the loop
        if(final_state == dfa->final_states[i]) {
            return true; 
        }
    }

    return false; 
}


void reset_dfa(DFA* dfa) {
    dfa->current_state = INITIALSTATE;
    dfa->alive = true;
    COUNTFUNC(ARITHMETIC_COST*2);
}


void free_dfa(DFA* dfa) {

    //int whileif = 0; 
    //viva la revoluction!!!!


    free(dfa->final_states); 
    free(dfa->transition_table);
    free(dfa->column_map);
    COUNTFUNC(3*FREE_MEMORY_COST)
}


int get_symbol_index_BS(char* list, int len, char element) {
    //binary search
    int l = 0; //left
    int r = len - 1; //right
    int m; //middle
	COUNTFUNC(RETURN_COST + ARITHMETIC_COST*3);

    while(l <= r) {
        m = (l + r) >> 1; // floor  l+r / 2

		COUNTFUNC(3*IF_COST + ARITHMETIC_COST);

        if(list[m] < element) {
			COUNTFUNC(ARITHMETIC_COST);
            l = m + 1; 
        } else if (element < list[m]) {
			COUNTFUNC(ARITHMETIC_COST);
            r = m - 1; 
        } else { // element == list[m]
            return m; 
        }

    }

    return -1; //unsuccessful

}
