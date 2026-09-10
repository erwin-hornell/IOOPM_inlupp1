#include <stdio.h>
#include <stdlib.h>
#include "utils-lab3.h"
#include <time.h>


int main(void){

    srandom(time(NULL)); /// initialize randomness -- call once per program run

    int tal = rand() % 1024; /// generate a random value 
    
    answer_t namn = ask_question("vad är ditt namn?",not_empty ,(convert_func *) strdup);

    printf("Du %s, jag tänker på ett tal... kan du gissa vilket?",namn.string_value);

    answer_t guess_t = ask_question("",is_number,(convert_func *) atoi);
    int guess = guess_t.int_value;
    
    for(int i = 0; i<15; ++i) {
        if (guess == tal){
            puts("bingo");
            printf("Det tog %s %d gissningar att komma fram till %d\n",namn.string_value,i+1,tal);
            return 0;
        }
        else if(guess < tal){
            puts("för litet!");
            guess_t = ask_question("",is_number,(convert_func *) atoi);
            guess = guess_t.int_value;

        }
        else {
            puts("för stort!");
            guess_t = ask_question("",is_number,(convert_func *) atoi);
            guess = guess_t.int_value; 
        }

    }
    printf("nu har du slut på gissningar, talet var %d\n",tal);
    return 0;
}



