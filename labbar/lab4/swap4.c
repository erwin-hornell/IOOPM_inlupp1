#include <stdio.h>
#include <string.h>

void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}


void print(char *str)
{
   char *start = str;                   //start adress på str
   char *end = start + strlen(str)-1;   //slutet adress på str
   while(start<=end){
        putchar(*start);
        start = start +1; 
   }
}


int main(void)
{
  int x = 7;
  int y = 42;
  swap(&x, &y);
  printf("%d, %d\n", x, y);

  char text[] = "hej";
    print(text);
  
  return 0;
}

