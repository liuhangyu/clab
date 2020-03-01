#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef int ElemType;

typedef struct QNode
{
    ElemType data;
    struct QNode *next;
} QNode, *QNodePtr;

typedef struct LinkQueue
{
    QNodePtr head;
    QNodePtr tail;
} LinkQueue;

int init_queue(LinkQueue *q)
{
    q->head = (QNodePtr)malloc(sizeof(QNode));
    if (q->head == NULL)
    {
        return -1;
    }
    q->tail = q->head;
    q->head->next = NULL;

    return 0;
}

int en_queue(LinkQueue *q, ElemType e)
{
    QNodePtr p = (QNodePtr)malloc(sizeof(QNode));
    if (p == NULL)
    {
        return -1;
    }
    p->data = e;
    p->next = NULL;
    //队尾添加
    q->tail->next = p;
    q->tail = p;
    return 0;
}

int de_queue(LinkQueue *q, ElemType *e)
{
    QNodePtr p = NULL;
    if (q->head == q->tail)
    {
        return -1;
    }
    //堆头出队
    p = q->head->next;
    *e = p->data;
    q->head->next = p->next;

    if (q->tail == p)
    {
        q->tail = q->head;
    }
    free(p);
    return 0;
}

int destory_queue(LinkQueue *q)
{
    while (q->head)
    {
        q->tail = q->head->next;
        free(q->head);
        q->head = q->tail;
    }
}
//
int main(int argc, char **argv)
{
    LinkQueue q;
    init_queue(&q);

    int i = 0, ret;
    for (i = 0; i < 20; i++)
    {
        ret = en_queue(&q, i);
        if (ret != 0)
        {
            printf("ret = %d\n", ret);
        }
    }

    while (ret != -1)
    {
        ElemType e;
        ret = de_queue(&q, &e);
        if (ret != -1)
        {
            printf("%d\n", e);
        }
    }

    destory_queue(&q);
    return 0;
}