#include <stdio.h>
#include <stdlib.h>

//need for stack: push, pop, check; stack_step
//pairs: '' "" [] {} ()
//check in-string, in-symbol &escape sequences \

#define BLOCK 1
#define LINE -1
#define NONE 0

#define STACK_STEP 1000

typedef struct _stack
{
    char *storage;
    int *lines;
    int *columns;
    int capacity;
    int pointer;
} Stack;

Stack *init()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->storage = (char *)calloc(STACK_STEP, sizeof(char));
    stack->lines = (int *)calloc(STACK_STEP, sizeof(int));
    stack->columns = (int *)calloc(STACK_STEP, sizeof(int));
    stack->capacity = STACK_STEP;
    stack->pointer = 0;
    return stack;
}

void push(Stack *stack, char elem, int line, int column)
{
    (stack->storage)[stack->pointer] = elem;
    (stack->lines)[stack->pointer] = line;
    (stack->columns)[stack->pointer] = column;
    ++(stack->pointer);
    if (stack->pointer == stack->capacity)
    {
        stack->capacity += STACK_STEP;
        stack->storage = (char *)realloc(stack->storage, stack->capacity);
        stack->lines = (int *)realloc(stack->lines, stack->capacity);
        stack->columns = (int *)realloc(stack->columns, stack->capacity);
    }
}
char pop(Stack *stack)
{
    --(stack->pointer);
    if ((stack->pointer) >= 0)
    {
        char c = (stack->storage)[stack->pointer];
        (stack->storage)[stack->pointer] = 0;
        return c;
    }
    else
    {
        stack->pointer = 0;
        return 0;
    }
}

char top(Stack *stack)
{
    return (stack->pointer) ? (stack->storage)[stack->pointer - 1] : 0;
}

int is_empty(Stack *stack)
{
    return (stack->pointer) <= 0;
}

void free_stack(Stack *stack)
{
    free(stack->storage);
    free(stack->lines);
    free(stack->columns);
}

void backslash_error(int line, int column)
{
    printf("Illegal backslash '\\' at line %d, column %d\n",
           (column - 1) ? (line - 1) : line,
           (column - 1) ? (column - 1) : -1);
}

void no_opening_char(char c, int line, int column)
{
    printf("Missing opening '%c' for symbol at line %d, column %d\n",
           c, line, column);
}

int main()
{
    int literal = 0, escape = 0;
    int comment = NONE, ready = 0;
    int line = 1, column = 1;
    int c;
    Stack *stack = init();
    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
        case '\'':
            if (!comment)
            {
                if (escape)
                {
                    if (!literal)
                    {
                        backslash_error(line, column);
                        push(stack, '\'', line, column);
                        literal = 1;
                    }
                }
                else
                {
                    if (literal)
                    {
                        if (top(stack) == '\'')
                        {
                            pop(stack);
                            literal = 0;
                        }
                    }
                    else
                    {
                        push(stack, '\'', line, column);
                        literal = 1;
                    }
                }
            }
            escape = 0;
            break;
        case '"': //"
            if (!comment)
            {
                if (escape && !literal)
                {
                    backslash_error(line, column);
                }
                else
                {
                    if (literal)
                    {
                        if (top(stack) == '"') //"
                        {
                            pop(stack);
                            literal = 0;
                        }
                    }
                    else
                    {
                        push(stack, '"', line, column); //"
                        literal = 1;
                    }
                }
            }
            escape = 0;
            break;
        case '\\':
            if (!comment)
            {
                escape = !(escape && literal);
            }
            break;
        case '(':
            if (!literal && !comment)
            {
                if (escape)
                {
                    backslash_error(line, column);
                }
                push(stack, '(', line, column);
            }
            escape = 0;
            break;
        case ')':
            if (!literal && !comment)
            {
                if (escape)
                {
                    backslash_error(line, column);
                }
                if (top(stack) != '(')
                {
                    no_opening_char('(', line, column);
                }
                else
                {
                    pop(stack);
                }
            }
            escape = 0;
            break;
        case '[':
            if (!literal && !comment)
            {
                if (escape)
                {
                    backslash_error(line, column);
                }
                push(stack, '[', line, column);
            }
            escape = 0;
            break;
        case ']':
            if (!literal && !comment)
            {
                if (escape)
                {
                    backslash_error(line, column);
                }
                if (top(stack) != '[')
                {
                    no_opening_char('[', line, column);
                }
                else
                {
                    pop(stack);
                }
            }
            escape = 0;
            break;
        case '{':
            if (!literal && !comment)
            {
                if (escape)
                {
                    backslash_error(line, column);
                }
                push(stack, '{', line, column);
            }
            escape = 0;
            break;
        case '}':
            if (!literal && !comment)
            {
                if (escape)
                {
                    backslash_error(line, column);
                }
                if (top(stack) != '{')
                {
                    no_opening_char('{', line, column);
                }
                else
                {
                    pop(stack);
                }
            }
            escape = 0;
            break;
        case '\n':
            switch (comment)
            {
            case BLOCK:
                break;
            case LINE:
                comment = NONE;
                break;
            case NONE:
                if (!escape && literal)
                {
                    printf("Illegal line break in a literal, line %d", line);
                }
            }
            ++line;
            column = 0;
            escape = 0;
            break;
        case '/':
            if (!literal)
            {
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
            }
            escape = 0;
            break;
        case '*':
            if (!literal)
            {
                if (comment == NONE && ready)
                {
                    comment = BLOCK;
                    ready = 0;
                }
                if (comment == BLOCK)
                {
                    ready = 1;
                }
            }
            escape = 0;
            break;
        default:
            if (escape && !literal)
            {
                backslash_error(line, column);
            }
            escape = 0;
            break;
        }
        column++;
    }

    if (!is_empty(stack))
    {
        printf("Here are all unclosed pairs:\n");
        while (!is_empty(stack))
        {
            printf("Symbol %c on line %d, column %d\n",
                   (stack->storage)[stack->pointer - 1],
                   (stack->lines)[stack->pointer - 1],
                   (stack->columns)[stack->pointer - 1]);
            pop(stack);
        }
    }
    free_stack(stack);
    return 0;
}