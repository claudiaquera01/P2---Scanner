
int function(int x) {

    return x + 3; 

}

int main(int argc, char** argv) {

    int MyValue = 31415; 
    int NumberOfPixels = 150 * 32 + 64; 

    NumberOfPixels = MyValue * 0; 

    int i = 0; 

    while(MyValue > i) {

        if(i > 240) {
            printf("The current number is ()d", function(i)); 
        } 
        else {
            i = i + NumberOfPixels; 
        }
        i += 1; 
    }

    char MyFunnyList[] = "Forgotten information"; 

    void* my_unrecognized_variable = "This cannot be recognized by the undersoce"; 



    return 0; 
}