#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef int keyType;
typedef int dataType;
typedef struct
{
    keyType key;
    dataType data;
} RecordType;

//
int insert_sort(RecordType keys[], int n)
{
    int i = 0, j = 0;
    RecordType tmp;
    for (i = 1; i < n; i++)
    {
        tmp = keys[i];
        j = 0;
        for (j = i - 1; j >= 0 && keys[j].key > tmp.key; j--)
        {
            keys[j + 1].key = keys[j].key;
        }
        keys[j + 1].key = tmp.key;
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

    int index = insert_sort(records, sizeof(records) / sizeof(RecordType));
    printf("ind = %d\n", index);

    int i = 0;
    for (i = 0; i < 4; i++)
    {
        printf("%d\n", records[i].key);
    }
    return 0;
}
