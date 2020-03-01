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
//
int bin_search(RecordType keys[], int n, keyType key)
{
    int low = 0;
    int high = n - 1;
    int mid = 0;
    printf("low = %d hight = %d\n", low, high);

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (keys[mid].key == key)
        {
            return mid;
        }
        if (keys[mid].key < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }

        printf("low = %d hight = %d\n", low, high);
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

    int index = bin_search(records, sizeof(records) / sizeof(RecordType), 4);
    printf("ind = %d len=%ld\n", index, sizeof(records) / sizeof(RecordType));
    return 0;
}
