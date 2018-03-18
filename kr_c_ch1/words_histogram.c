#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define IN 1
#define OUT 0

int main()
{
    FILE *buf = fopen("words_histogram.txt", "w");
    int c, status = OUT;
    while ((c = getchar()) != EOF)
    {
        if (isspace(c))
        {
            if (status == IN)
            {
                fputc('\n', buf);
            }
            status = OUT;
        }
        else
        {
            status = IN;
            fputc('+', buf);
        }
    }
    fputc('\n', buf);
    fclose(buf);
    buf = fopen("words_histogram.txt", "r");
    while ((c = fgetc(buf)) != EOF)
    {
        putchar(c);
    }
    fclose(buf);
    return 0;
}