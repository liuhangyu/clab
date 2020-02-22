#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int Array(int n, char **list, int list_item_length, char init_str[], int init_str_len)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (list_item_length < init_str_len)
        {
            printf("too length %ld %ld\n", strlen(list[i]), sizeof(list[i]));
            list[i] = (char *)realloc(list[i], init_str_len + 1);
            sprintf(list[i], "%s", init_str);
        }
        else
        {
            sprintf(list[i], "%s", init_str);
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    char *list[3];
    list[0] = (char *)malloc(sizeof(char) * 2);
    list[1] = (char *)malloc(sizeof(char) * 2);
    list[2] = (char *)malloc(sizeof(char) * 2);

    Array(3, list, sizeof(char[2]), "hello world", sizeof("hello world"));

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        // printf("p[%d] = %s %ld\n", i, list[i], sizeof(list[i]));
        printf("p[%d] = %s \n", i, list[i]);
    }

    free(list[0]);
    free(list[1]);
    free(list[2]);
}