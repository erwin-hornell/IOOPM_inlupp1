#include <stdio.h>
#include <stdlib.h>

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
        // spara antalet lästa tecken i read
    }
    while (read == 0);

    return buf;
}


int main(void){
    int buf_siz = 255;
    int read = 0;
    char buf[buf_siz];

    ask_question_string("skriv din fråga", buf, buf_siz);

    printf("din fråga var %s\n",buf);

}
