#ifndef UTILS_LAB3_H
#define UTILS_LAB3_H


typedef union { 
  int   int_value;
  float float_value;
  char *string_value;
} answer_t;

typedef bool check_func(char *);

typedef answer_t convert_func(char *);



extern char *strdup(const char *);

int read_string(char *buf, int buf_siz);

bool is_number(char *str);

bool not_empty(char *str);

answer_t ask_question(char *question, check_func *check,convert_func *con);

int ask_question_int(char *question);

char *ask_question_string(char *question);

#endif