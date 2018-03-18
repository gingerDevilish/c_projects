#include <stdio.h>

#define LIMIT 80
#define TAB_LEN 4

int main()
{
    int len = 0;
    int c;
    int blanks = 0;
    int line_started = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            if (line_started)
            {
                blanks = blanks + TAB_LEN - ((len - 1) % TAB_LEN);
                len = len + (TAB_LEN - (len - 1) % TAB_LEN) - 1;
            }
        }
        else
        {
            if (c == ' ')
            {
                if (line_started)
                {
                    blanks++;
                    len++;
                }
            }
            else if (c == '\n')
            {
                printf("\n");
                len = 0;
                line_started = 1;
            }
            else
            {
                line_started = 1;
                len++;
                for (; blanks; printf(" "), blanks--)
                    ;
                printf("%c", c);
            }
            if (len >= 80)
            {
                line_started = 0;
                blanks = 0;
                len = 0;
                printf("\n");
            }
        }
    }
    return 0;
}