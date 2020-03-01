#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef int keyType;

//
int select_sort(keyType keys[], int n)
{
    int i, j, min;
    keyType tmp;
    for (i = 1; i <= n - 1; i++)
    {
        min = i;
    }
    return 0;
}

//
int main(int argc, char **argv)
{
    RecordType records[4] = {
        {2, 1},
        {4, 2},
        {1, 3},
        {3, 4},
    };

    int index = select_sort(records, sizeof(records) / sizeof(RecordType));
    printf("ind = %d\n", index);

    int i = 0;
    for (i = 0; i < 4; i++)
    {
        printf("%d\n", records[i].key);
    }
    return 0;
}
