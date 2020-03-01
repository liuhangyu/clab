#include <stdio.h>
#include <string.h>

int main()
{

    char buf1[] = "1234567890";
    char buf2[4];

    int n = sizeof(buf1) / sizeof(char);
    int i = 0;

    printf("%s\n", buf1);
    while (i < n)
    {
        buf2[i] = buf1[i++]; //陷阱
        /*
            buf2[0] = buf1[0],i++=1 ===> buf2[1] = buf[0]
        */
        printf("%d %c\n", i, buf2[i]);
        // buf2[i] = buf1[i];
        // i++;
    }

    printf("%s\n", buf2);
    return 0;
}
