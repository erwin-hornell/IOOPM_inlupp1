#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{

 if (argc<2 || argc>3)
 {
  puts("fel antal arg");
 }
 else
 {
  int row = atoi(argv[1]);
  int inc =atoi(argv[2]);

  for (int i = 0; i < row; ++i)
  {
    printf("\n");
    for (int x = 0; x < (i + 1) * inc; x++)
    {
      printf("*");
    }
  }
}
  return 0;
}
