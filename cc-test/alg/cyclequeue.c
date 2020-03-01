#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef int ElemType;
#define MAX_SIZE 10
typedef struct cyclequeue
{
    /* data */
    ElemType *base;
    int head;
    int tail;
} cyclequeue;

int init_cycle_queue(cyclequeue *c)
{
    c->base = (ElemType *)malloc(MAX_SIZE * sizeof(ElemType));
    if (c->base == NULL)
    {
        return -1;
    }
    c->head = c->tail = 0;

    return 0;
}

int en_cycle_queue(cyclequeue *c, ElemType e)
{
    if ((c->tail + 1) % MAX_SIZE == c->head)
    {
        return -1;
    }

    c->base[c->tail] = e;
    c->tail = (c->tail + 1) % MAX_SIZE;
    printf("head:%d  tail:%d\n", c->head, c->tail);
    return 0;
}

int de_cycle_queue(cyclequeue *c, ElemType *e)
{
    if (c->head == c->tail)
    {
        // printf("c->base[c->tail] = %d\n", c->base[c->tail]);
        return -1;
    }
    *e = c->base[c->head];
    c->head = (c->head + 1) % MAX_SIZE;
    return 0;
}

//
int main(int argc, char **argv)
{
    cyclequeue c;
    init_cycle_queue(&c);
    int i = 0, ret;
    for (i = 0; i < 11; i++)
    {
        ret = en_cycle_queue(&c, i);
        if (ret != 0)
        {
            printf("%d\n", ret);
        }
    }

    do
    {
        ElemType a;
        ret = de_cycle_queue(&c, &a);
        if (ret != -1)
        {
            printf("ret=%d %d\n", ret, a);
        }
    } while (ret != -1);
    return 0;
}