#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{
    int c, state = OUT, outcount = 0;
    while ((c = getchar()) != EOF)
    {
        if ((c == '\n') || (c == '\t') || (c == ' '))
        {
            state = OUT;
            if (!outcount)
            {
                printf("\n");
            }
            outcount++;
        }
        else
        {
            outcount = 0;
            state = IN;
            printf("%c", c);
        }
    }
    return 0;
}