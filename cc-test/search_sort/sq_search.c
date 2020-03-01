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
int sq_search(RecordType keys[], int n, keyType key)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        if (keys[i].key == key)
        {
            return i;
        }
    }
    return -1;
}

//
int main(int argc, char **argv)
{
    RecordType records[] = {
        {1, 1},
        {2, 2},
        {3, 3},
        {4, 4},
    };

    int index = sq_search(records, sizeof(records) / sizeof(RecordType), 4);
    printf("ind = %d\n", index);
    return 0;
}
