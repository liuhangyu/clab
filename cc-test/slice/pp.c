#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void func(int n, char str[][5])
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("str[%d] = %s\n", i, str[i]);
    }
    return;
}

int main(int argc, char **argv)
{
    char *p[3];
    char str[][5] = {"abc", "123", "ert"};
    func(3, str);
}