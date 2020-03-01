
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define MaxChild 10

typedef int dataType;
typedef struct node
{
    dataType data;
    struct node *child[MaxChild];
} node;
//
int main(int argc, char **argv)
{

    return 0;
}
