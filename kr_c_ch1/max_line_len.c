#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int get_line(char **line, int starting_size);

void copy(char to[], char from[]);

int main()
{
    int len;
    int max;
    char *line = NULL;
    char *longest = NULL;

    max = 0;
    while ((len = get_line(&line, MAXLINE)) > 0)
    {
        if (len > max)
        {
            max = len;
            longest = (char *)realloc(longest, max);
            copy(longest, line);
        }
    }
    if (max > 0)
    {
        printf("%s", longest);
    }
    free(line);
    free(longest);
    return 0;
}

int get_line(char **s, int chunk)
{
    int c, i;
    int lim = chunk;
    *s = (char *)realloc(*s, lim);
    for (i = 0; ((c = getchar()) != EOF) && (c != '\n'); ++i)
    {
        (*s)[i] = c;
        if (i == lim - 2)
        {
            lim += chunk;
            *s = (char *)realloc(*s, lim);
        }
    }
    if (c == '\n')
    {
        (*s)[i] = c;
        ++i;
    }
    (*s)[i] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
    {     
        ++i;
    }
}