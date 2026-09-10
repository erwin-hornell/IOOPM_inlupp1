#include <stdio.h>


int main(void)

{
  int sum = 0;  
  for(int x = 1; x<=10; x=x+1)
    {
        printf("\n");
        sum=sum+x;
        for(int i = 1; i<=x; i=i+1)
        {
            printf("*");
            //sum=sum+i;
        }
            
    }
   printf("%d\n",sum); 


  return 0;
}
