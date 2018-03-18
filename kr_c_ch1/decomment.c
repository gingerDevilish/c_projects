#include <stdio.h>
// includes

#define BLOCK 1
#define LINE -1
#define NONE 0
/* defines */

int main()
{
    int c;
    int comment = NONE;
    int ready = 0;
    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
        case '/':
            if (comment == NONE)
            {
                if (ready)
                {
                    comment = LINE;
                    ready = 0;
                }
                else
                {
                    ready = 1;
                }
            }
            if ((comment == BLOCK) && ready)
            {
                ready = 0;
                comment = NONE;
            }
            break;
        case '*':
            if (comment == NONE)
            {
                if (ready)
                {
                    comment = BLOCK;
                    ready = 0;
                }
                else
                {
                    printf("*");
                }
            }
            if (comment == BLOCK)
            {
                ready = 1;
            }
            break;
        case '\n':
            if (comment == LINE)
            {
                comment = NONE;
            }
            ready = 0;
            if (comment != BLOCK)
            {
                printf("\n");
            }
            break;
        default:
            if (comment == NONE)
            {
                if (ready)
                {
                    printf("/");
                }
                printf("%c", c);
            }
            ready = 0;
        }
    }
    return 0;
}