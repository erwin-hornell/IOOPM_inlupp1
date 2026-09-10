#include <stdio.h>
#include <stdlib.h>
#include "utils.h"






int main(void){

    int buf_siz = 255;
    int tal = rand() % 1024; 
    char buf[buf_siz];

    ask_question_string("vad är ditt namn?", buf, buf_siz);

    printf("Du %s, jag tänker på ett tal... kan du gissa vilket?",buf);

    int guess = ask_question_int("");

    for(int i = 0; i<15; ++i) {
        if (guess == tal){
            puts("bingo");
            printf("Det tog %s %d gissningar att komma fram till %d\n",buf,i+1,tal);
            return 0;
        }
        else if(guess < tal){
            puts("för litet!");
            guess = ask_question_int("");
        }
        else {
            puts("för stort!");
            guess = ask_question_int("");
        }

    }
    printf("nu har du slut på gissningar, talet var %d\n",tal);
    return 0;
}