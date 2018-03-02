#include <stdio.h>

int main()
{
    float celsius, fahr;
    float upper, lower, step;

    lower = 0;
    upper = 300;
    step = 20;

    celsius = lower;
    printf("Celsius  |  Fahrenheit\n");
    while (celsius <= upper)
    {
        fahr = (9.0 / 5.0) * celsius + 32.0;
        printf("%3.0f\t\t%6.1f\n", celsius, fahr);
        celsius += step;
    }
    return 0;
}