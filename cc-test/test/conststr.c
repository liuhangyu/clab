#include <stdio.h>
#include <string.h>

int main()
{

    if (0)
    {
        char *p = "xyz";
        char *q;
        q = p;
        q[1] = 'Y'; //程序静态存储区不被修改 否则崩溃
        printf("%s\n", q);
    }

    return 0;
}
