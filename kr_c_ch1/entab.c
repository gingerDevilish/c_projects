#include <stdio.h>

#define TAB_LENGTH 4

int main()
{
    int c;
    int column = 0;
    int blanks = 0, tabs = 0;
    while ((c = getchar()) != EOF)
    {
        column++;
        if (c == ' ')
        {
            if (column % TAB_LENGTH)
            {
                blanks++;
            }
            else
            {
                blanks = 0;
                tabs++;
            }
        }
        else
        {
            if (c == '\n')
            {
                column = 0;
                blanks = 0;
                tabs = 0;
            }
            while (tabs--)
            {
                printf("\t");
            }
            if (c == '\t')
            {
                blanks = 0;
                do
                {
                    column++;
                } while (column % TAB_LENGTH);
            }
            while (blanks--)
            {
                printf(" ");
            }
            blanks = 0;
            tabs = 0;
            printf("%c", c);
        }
    }
    return 0;
}