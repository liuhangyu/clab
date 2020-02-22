#include <stdio.h>
#include <string.h>

int main()
{

    printf("%ld\n", sizeof("hello"));

    char s[2] = "123322";
    printf("数组长度%ld", sizeof(s));
    printf("\r\n");
    printf("字符串=%s", s);
    printf("\r\n");
    char t[] = "132";
    printf("字符串长度%ld", strlen(s));
    printf("\r\n");
    printf("字符串长度%ld", strlen(t));
    printf("\r\n");
    printf("数组长度%ld", sizeof(t));

    return 0;
}
