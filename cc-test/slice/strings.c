#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct my_string
{
    int nLen;
    char data[0];
} my_string;

my_string *make(int len)
{
    my_string *pstr = (my_string *)malloc(sizeof(my_string) + len);
    memset(pstr->data, 0, len);
    pstr->nLen = len;
    return pstr;
}

int copy_val(my_string *str, char *s, int slen)
{
    if (str->nLen <= slen)
    {
        return -1;
    }
    memcpy(str->data, s, slen);
    return 0;
}

int getLen(my_string *str)
{
    return str->nLen;
}

char *getData(my_string *str)
{
    return (str->data);
}

void delete (my_string *str)
{
    if (str != NULL)
    {
        free(str);
    }
}

int main()
{
    my_string *pstr = make(41);

    char p[] = "sssssssssssssssssssssssssssssssssssssss";
    printf("%ld %ld\n", sizeof(p), strlen(p));

    int ret = copy_val(pstr, "ssssssssssssssssssssssssssssssssssssss", sizeof(p));
    printf("ret=%d %s\n", ret, pstr->data);

    printf("%s\n", getData(pstr));

    delete (pstr);
    return 0;
}
/*

valgrind ./main



https://blog.csdn.net/guoyajie1990/article/details/78451966
https://blog.csdn.net/hyqsong/article/details/50863746
*/