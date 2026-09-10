#include <stdio.h>
#include <string.h>

int fib(int num){

    if (num==0){
        return 0; 
    }
    else if (num == 1) {
        return 1; 
    }
    else {
        return fib(num-1)+fib(num-2);
    }
}

int main(void){
    int tot = fib(7);
    printf("%d\n",tot);
}