#include "debug.h"

// Function to output tokens in debug mode
oid output_tokens_debug(FILE* output_file, Token* tokens, int num_tokens, int debug_mode) {
    // Write tokens in the output version
    int num;
    num=0;
    for (int i = 0; i < num_tokens; i++) {
        if(num!=tokens[i].line_number){
            //fprintf(output_file, "\n");
            printf("\n");
            if (debug_mode == DEBUG_ON) {
                //fprintf(output_file, "%d ", tokens[i].line_number);
                printf("%d ", tokens[i].line_number);
            }
        }

        const char* category_str;
        switch (tokens[i].category) {
            case CAT_NUMBER:
                category_str = "CAT_NUMBER";
                break;
            case CAT_IDENTIFIER:
                category_str = "CAT_IDENTIFIER";
                break;
            case CAT_KEYWORD:
                category_str = "CAT_KEYWORD";
                break;
            case CAT_LITERAL:
                category_str = "CAT_LITERAL";
                break;
            case CAT_OPERAND:
                category_str = "CAT_OPERAND";
                break;
            case CAT_SPECIALCHAR:
                category_str = "CAT_SPECIALCHAR";
                break;
            case CAT_NONRECOGNIZED:
                category_str = "CAT_NONRECOGNIZED";
                break;
            default:
                category_str = "UNKNOWN";
                break;
        }

        //fprintf(output_file, "<%s, %s>", tokens[i].lexeme, category_str);
        printf("<%s, %s>", tokens[i].lexeme, category_str);
        //Add a line break after each token
        if (num!=tokens[i].line_number){
            num++;
        }
    }
}
