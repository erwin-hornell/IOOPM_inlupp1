#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

extern char *strdup(const char *);

typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool check_func(char *);

typedef answer_t convert_func(char *);


/// Hjälpfunktion till ask_question_string
bool not_empty(char *str)
{
  return strlen(str) > 0;
}



answer_t ask_question(char *question, check_func *check,convert_func *con){

    char buf[255];
    int buf_siz = 255;
    bool done = false; 
    answer_t answer;
    
    do
    {
    
    printf("%s\n",question);

    int read = read_string(buf, buf_siz); //buf = "svar"


    if (check(buf)){
        answer = con(buf);
        done = true;
    }

    else{puts("försök igen");}

    } while (!done);

    return answer;
    
    }



int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func *) atoi);
  return answer.int_value; // svaret som ett heltal
}




char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func *) strdup).string_value;
}
