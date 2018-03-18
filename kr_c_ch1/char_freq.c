#include <stdio.h>

int main()
{
    long freq[256] = {0};
    int c;
    while ((c=getchar())!=EOF)
    {
        freq[c]++;
    }
    printf("\n");
    for (int i=0; i<256; i++, printf("\n"))
    {
        for (int j=0; j<freq[i]; j++, printf("+"));
    }
    return 0;
}