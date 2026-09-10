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

    




int main(void)
{
    int buf_siz = 255;
    int read = 0;
    char buf[buf_siz];

    puts("Läs in en sträng:");
    read = read_string(buf, buf_siz);
    printf("'%s' (%d tecken)\n", buf, read);

    puts("Läs in en sträng till:");
    read = read_string(buf, buf_siz);
    printf("'%s' (%d tecken)\n", buf, read);

    return 0;
}