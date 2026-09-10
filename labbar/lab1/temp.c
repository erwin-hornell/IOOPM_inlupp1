#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>




bool is_number(char *str)
{
    int len = strlen(str);

    for(int i = 0; i<len; i++)
    {
        bool res = isdigit(str[i]);
        if (res == false)
            
            if (str[i] == '-' && i == 0)
            {

            }
            else 
            {
                return false;
            }
        
        else 
        {
    
        }
    }
    return true;
}


int main(int argc, char *argv[])
{
    if (argc > 1 && is_number(argv[1]))
    {
        printf("%s is a number\n", argv[1]);
    }
    else
    {
        if (argc > 1)
        {
            printf("%s is not a number\n", argv[1]);
        }
        else
        {
            printf("Please provide a command line argument!\n");
        }
    }

    return 0;
}