#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int ask_question_int(char *question)
{

  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s\n", question);
      conversions = scanf("%d", &result); 
      int c;
      do
        {
          c = getchar();
        }
      while (c != '\n' && c != EOF);
      putchar('\n');
    }
  while (conversions < 1);
  return result;
}

int read_string(char *buf, int buf_siz)
{
    int i = 0;
    int c;

    c = getchar();

    while (c != '\n' && c != EOF && i < buf_siz - 1)
    {
        buf[i] = c;
        i++;
        c = getchar();
    }

    buf[i] = '\0';

    if (c != '\n' && c != EOF)
    {
        while (c != '\n' && c != EOF)
        {
            c = getchar();
        }
    }

    return i;
}

    



char *ask_question_string(char *question, char *buf, int buf_siz) {
  
    int read;

    do
    {
        printf("%s\n",question); // skriv ut question
        read = read_string(buf, buf_siz);// kör read_string(...)
        
    }
    while (read == 0);

    return buf;
}
