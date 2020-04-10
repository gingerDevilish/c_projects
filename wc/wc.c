#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>

#define BYTES -1
#define CHARS 1
#define NONE 0

#define IN 1
#define OUT 0

int main(int argc, char **argv)
{
    int SYMBOLS = BYTES, WORDS = 1, LINES = 1;
    int files = 0, offset = 1;
    FILE **file;
    int *symbols, *words, *lines;
    int symbols_total = 0, words_total = 0, lines_total = 0;
    if (argc > 1)
    {
        if (argv[1][0] == '-')
        {
            SYMBOLS = NONE;
            WORDS = 0;
            LINES = 0;
            offset++;
            char *counter = argv[1];
            while (*counter++)
            {
                switch (*counter)
                {
                case 'c':
                    SYMBOLS = BYTES;
                    break;
                case 'l':
                    LINES = 1;
                    break;
                case 'm':
                    SYMBOLS = CHARS;
                    break;
                case 'w':
                    WORDS = 1;
                    break;
                case 0:
                    break;
                default:
                    printf("Unable to parse options\n");
                    return 1;
                }
            }
        }
        if (argc > offset)
        {
            files = argc - offset;
            file = (FILE **)malloc(sizeof(FILE *) * (argc - files));
            if (!file)
            {
                printf("Memory error. Unable to allocate memory for file descriptors\n");
                return 2;
            }
        }
        else
        {
            file = &stdin;
        }
    }
    else
    {
        WORDS = 1;
        LINES = 1;
        file = &stdin;
    }

    symbols = (int *)calloc(files, sizeof(int));
    words = (int *)calloc(files, sizeof(int));
    lines = (int *)calloc(files, sizeof(int));

    if (!(symbols && words && lines))
    {
        printf("Memory error. Unable to allocate memory for file descriptors\n");
        free(symbols);
        free(words);
        free(lines);
        if (argc - offset)
        {
            free(file);
        }
        return 2;
    }
    for (int i = 0; i < files; i++)
    {
        file[i] = fopen(argv[i + offset], SYMBOLS == BYTES ? "rb" : "r");
        if (!file[i])
        {
            printf("Unable to open file:\n%s\n", argv[i + offset]);
            free(symbols);
            free(words);
            free(lines);
            for (int j = 0; j <= i; j++)
            {
                if (
                    fclose(file[j]))
                {
                    printf("Something went wrong while closing the file:\n%s\n", argv[j + offset]);
                }
            }
            if (argc - offset)
            {
                free(file);
            }
            return 3;
        }
    }

    files = files ? files : 1;

    for (int i = 0; i < files; i++)
    {
        int c;
        int state = OUT;
        if (SYMBOLS == CHARS)
        {
            while ((c = fgetwc(file[i])) != WEOF)
            {
                
                
                symbols[i]++;
                symbols_total++;
                
                
                if (iswspace(c))
                {
                    if (state == IN)
                    {
                        state = OUT;
                        words[i]++;
                        words_total++;
                    }
                }
                else
                {
                    state = IN;
                }
                if (c == '\n')
                {
                    lines[i]++;
                    lines_total++;
                }
            }
        }
        else
        {
            while ((c = fgetc(file[i])) != EOF)
            {
                symbols[i]++;
                symbols_total++;
                if (isspace(c))
                {
                    if (state == IN)
                    {
                        state = OUT;
                        words[i]++;
                        words_total++;
                    }
                }
                else
                {
                    state = IN;
                }
                if (c == '\n')
                {
                    lines[i]++;
                    lines_total++;
                }
            }
            words[i]++;
            words_total++;
        }
        if (fclose(file[i]))
        {
            printf("Something went wrong while closing the file:\n%s\n", (argc == offset) ? "stdin" : argv[i + offset]);
        }
    }
    if (argc - offset)
    {
        free(file);
    }

    for (int i = 0; i < files; i++)
    {
        printf("File: %s\n", (argc == offset) ? "stdin" : argv[i + offset]);
        if (SYMBOLS)
        {
            printf("%s: %6d\t", (SYMBOLS == CHARS) ? "Characters" : "Bytes", symbols[i]);
        }
        if (WORDS)
        {
            printf("Words: %6d\t", words[i]);
        }
        if (LINES)
        {
            printf("Lines: %6d\t", lines[i]);
        }
        printf("\n\n");
    }

    free(symbols);
    free(words);
    free(lines);

    printf("Total:\n");
    if (SYMBOLS)
    {
        printf("%s: %6d\t", (SYMBOLS == CHARS) ? "Characters" : "Bytes", symbols_total);
    }
    if (WORDS)
    {
        printf("Words: %6d\t", words_total);
    }
    if (LINES)
    {
        printf("Lines: %6d\t", lines_total);
    }
    printf("\n\n");

    return 0;
}
