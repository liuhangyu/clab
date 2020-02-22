#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

const int LENGHT_STR = 5;

char **make(char list[][100], int len)
{
    int i = 0;
    // char **v = NULL;

    if (len > 0)
    {
        list = (char **)malloc(len);
        for (i = 0; i < len; i++)
        {
            list[i] = (char *)malloc(LENGHT_STR * sizeof(char));
            memset(list[i], 0, LENGHT_STR);
            // printf("len %ld %ld\n", sizeof(*list[i]), strlen((list[i])));
        }
    }
    return list;
}

int append(char slice[][LENGHT_STR], int args, ...)
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
        if (LENGHT_STR > str_len)
        {
            strncpy((slice)[i], ptr, strlen(ptr));
        }
        else
        {
            printf("%p\n", (slice)[i]);
            // free(slice[i]);
            // *(slice[i]) = (char *)malloc((str_len + 1) * sizeof(char));
            // strncpy(slice[i], ptr, strlen(ptr));
        }
        printf("%s %s\n", ptr, slice[i]);
    }

    /* 清理为 valist 保留的内存 */
    va_end(valist);

    return 0;
}

int main(int argc, char **argv)
{
    int i = 0;
    char *slice[100] = NULL;
    slice = make(slice, 100);

    append(slice, 2, "hello world1", "hello world2");
    // if (p)
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