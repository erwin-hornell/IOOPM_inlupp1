#include <stdio.h>

int main(void)
{
  int x = 1;
  int y = 2;
  printf("x = %d\n", x);
  printf("y = %d\n", y);
  puts("=====");
  
  int tmp = x;
  x = y;
  y = tmp;

  printf("x = %d\n", x);
  printf("y = %d\n", y);

/*
  int i = 1;              // deklaration och initiering av iterationsvariabeln
  while (i <= 10)         // iterationsvillkor (utför blocket så länge i är mindre än 11)
  {                       // loop-kropp (utförs så länge iterationsvillkoret är uppfyllt)
    printf("%d\n", i);    // skriv ut 1, och en radbrytning
    i = i + 1;            // öka i:s värde med 1 (förändring av iterationsvariabeln)
  }
*/

  for(int x = 1; x<=10; x=x+1)
    {
        printf("%d\n", x);
    }


  return 0;
}

