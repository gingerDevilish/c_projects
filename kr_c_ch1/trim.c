#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 256

int get_line(char **line, int starting_size);

int main()
{
    int len;
    char *line = NULL;

    while ((len = get_line(&line, MAXLINE)) > 0)
    {
        int l = len;
        while (isspace(line[l - 1]))
        {
            line[--l] = 0;
        }
        printf("[%s]", line);
    }

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