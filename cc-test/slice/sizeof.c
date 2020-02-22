#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
int main(int argc, char **argv)
{
    int a, ab[4] = {1111, 3, 5, 6};
    printf("%ld\n", sizeof(a));
    printf("%ld\n", sizeof(ab));

    int i = 0;
    char **list = (char **)malloc(3);
    for (i = 0; i < 3; i++)
    {
        list[i] = (char *)malloc(1000 * sizeof(char));
        memset(list[i], 0, 1000 * sizeof(char));
        printf("len %ld %ld\n", sizeof(list[i]), strlen((list[i]))); //err sizeof
    }

    {
        int i = 0;
        char **list = (char **)malloc(3);
        for (i = 0; i < 3; i++)
        {
            list[i] = (char *)malloc(1000 * sizeof(char));
            memset(list[i], 0, 1000 * sizeof(char));
        }
    }
}
