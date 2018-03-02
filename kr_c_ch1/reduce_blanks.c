#include <stdio.h>

int main()
{
    int c, counter = 0;
    while((c=getchar())!=EOF)
    {
        if(c==' ')
        {
            if(!counter++)
            {
                printf("%c", c);
            }
        }
        else
        {
            counter=0;
            printf("%c", c);
        }
    }
    return 0;
}