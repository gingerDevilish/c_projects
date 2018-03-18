#include <stdio.h>

float ctof(float c)
{
    return (9.0 / 5.0) * c + 32.0;
}

float ftoc(float f)
{
    return (f - 32.0) * (5.0 / 9.0);
}

int main()
{
    char *s = "%6.2fC is %6.2fF;\t\t%6.2fF is %6.2fC\n";
    for (float i = -50.0; i <= 50.0; printf(s, i, ctof(i), i, ftoc(i)), i += 5.0)
        ;
    return 0;
}