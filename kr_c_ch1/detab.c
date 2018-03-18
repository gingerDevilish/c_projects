#include <stdio.h>

#define TAB_LENGTH 4

int main()
{
    int c;
    int column = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            do
            {
                printf(" ");
                column++;
            } while (column % TAB_LENGTH);
        }
        else if (c == '\n')
        {
            printf("\n");
            column = 0;
        }
        else
        {
            printf("%c", c);
            column++;
        }
    }
    return 0;
}