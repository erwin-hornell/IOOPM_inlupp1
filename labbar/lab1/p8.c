#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
    {
        int a = atoi(argv[1]);
        for(int i = 2;i<a; i++){
            for(int x = 2; x<a; x++){
                int b = x*i;
                 if (a == b)
                    {
                        puts("ej primtal");
                        return 0;
                    
                     }
                 else
                     {
                        
                     }
            }

        }
         
        puts("primtal");
        return 0;

    }