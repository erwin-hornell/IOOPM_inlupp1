#include <stdio.h>
#include <stdlib.h>


void prinum(int num)
{
    if(num % 3 == 0 && num % 5 == 0)
    {
        printf("fizz buzz,");
    }
    else if(num % 3 == 0)
    {
        printf("fizz,");
    }
    else if(num % 5 == 0)
    {
        printf("buzz,");
    }
    else 
    {
        printf("%d,",num);
    }
}



int main(int argc, char *argv[])
{
    int x = atoi(argv[1]);

    for(int i = 1; i<=x; i++)
    {
        prinum(i);
    }
    return 0;
}
