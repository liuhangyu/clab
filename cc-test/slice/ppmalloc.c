#include <stdio.h>
#include <stdlib.h>
int main()
{
    int num = 3;
    int(*p)[5] = NULL;

    p = (int(*)[5])malloc(num * sizeof(int[5]));
    if (NULL == p)
    {
        return -1;
    }

    for (int i = 0; i < num; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            p[i][j] = 5 * i + j;
        }
    }
    for (int i = 0; i < num; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }

    printf("p[1][3]: %d\n", p[1][3]);

    free(p);
}
