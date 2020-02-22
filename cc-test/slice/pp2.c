#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int Array(int n, char (*list)[2], char init_str[], int init_str_len)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (sizeof(char[2]) < init_str_len)
        {
            printf("too length\n");
            char *paddr = list[i];
            free(paddr);
            // paddr = (char *)malloc(100 * sizeof(char));// 修改形参大小
            // paddr = (char *)realloc(paddr, init_str_len + 1);
            // char(*paddr)[100] = (char(*)[100])realloc(list, 3 * sizeof(char[100]));
            // list = paddr;
            // sprintf(list[i], "%s", init_str);
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
    char(*list)[2] = NULL;
    list = (char(*)[2])malloc(3 * sizeof(char[2]));

    Array(3, list, "hello", sizeof("hello"));

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        printf("p[%d] = %s\n", i, list[i]);
    }

    free(list);
}