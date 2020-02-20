#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

const int LENGHT_STR = 5;

char **make(int len)
{
    int i = 0;
    char **list = NULL;

    if (len > 0)
    {
        list = (char **)malloc(len);
        for (i = 0; i < len; i++)
        {
            list[i] = (char *)malloc(LENGHT_STR * sizeof(char));
            memset(list[i], 0, LENGHT_STR);
            // printf("len %d %ld\n", LENGHT_STR, strlen((list[i])));
        }
    }
    return list;
}

char **append(char *slice[], int args, ...)
{
    int i = 0, str_len = 0;
    char *ptr = NULL;
    va_list valist;
    /* 为 args 个参数初始化 valist */
    va_start(valist, args);

    /* 访问所有赋给 valist 的参数 */
    for (i = 0; i < args; i++)
    {
        ptr = va_arg(valist, char *);
        str_len = strlen(ptr);
        if (sizeof((*slice)[i]) > str_len)
        {
            strncpy((*slice)[i], ptr, strlen(ptr));
        }
        else
        {
            printf("%p\n", (*slice)[i]);
            free((*slice)[i]);
            (*slice)[i] = (char *)malloc((str_len + 1) * sizeof(char));
            strncpy((*slice)[i], ptr, strlen(ptr));
        }
        printf("%s %s\n", ptr, (*slice)[i]);
    }

    /* 清理为 valist 保留的内存 */
    va_end(valist);

    return slice;
}

int main(int argc, char **argv)
{
    int i = 0;
    char **slice = make(100);

    char **p = append(slice, 2, "hello world1", "hello world2");
    if (p)
    {
        for (i = 0; strlen(p[i]) != 0; i++)
        {
            printf("main-> %s %ld\n", p[i], strlen(p[i]));
        }
    }
}

/*
https://www.cnblogs.com/zhangyachen/p/8035577.html

go
slice := make([]string,0)

*/