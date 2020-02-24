#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef int ElemType;
typedef struct node
{
    ElemType data;
    struct node *next;
} Node, *LinkList;

typedef struct List
{
    LinkList head;
    LinkList tail;
} List, *ListSet;

//返回头尾节点 尾插发
ListSet CreateLinkList(int n)
{
    int i = 0;
    LinkList p = NULL;

    ListSet li = (ListSet)malloc(sizeof(struct List));
    li->head = NULL;
    li->tail = NULL;

    for (i = 0; i < n; i++)
    {
        p = (LinkList)malloc(sizeof(struct List));
        p->data = 100;
        p->next = NULL;

        if (li->head == NULL)
        {
            li->head = p;
        }
        else
        {
            li->tail->next = p;
        }
        li->tail = p;
    }

    return li;
}

typedef enum opht
{
    Head = 1,
    Tail
} opht;

void insertList(ListSet *list, opht o, ElemType e)
{
    LinkList p = NULL;
    p = (LinkList)malloc(sizeof(struct List));
    p->data = e;
    p->next = NULL;

    if (o == Head)
    {
        if (*list == NULL)
        {
            (*list)->head = p;
            (*list)->tail = p;
            p->next = NULL;
        }
        else
        {
            //头插法
            p->next = (*list)->head->next;
            (*list)->head->next = p;
        }
    }
    else
    {
        if (*list == NULL)
        {
            (*list)->head = p;
            (*list)->tail = p;
            p->next = NULL;
        }
        else
        {
            (*list)->tail->next = p;
            (*list)->tail = p;
        }
    }
}

void delLink(ListSet *list, LinkList p)
{
    LinkList r = NULL;
    if ((*list)->head != (*list)->tail && (*list)->head == p)
    {
        if (p != (*list)->head)
        {
            (*list)->head = p->next;
            free(p); //删除p
        }
    }
    else
    {
        for (r = (*list)->head->next; r != p; r = r->next)
            ;
        if (r->next != NULL)
        {
            if (r->next == (*list)->tail)
            {
                (*list)->tail = r;
                r->next = p->next;
                free(p);
            }
            else
            {
                r->next = p->next;
                free(p);
            }
        }
    }
}

void destoryLink(ListSet *list)
{
    LinkList p = NULL;
    LinkList n = NULL;
    p = (*list)->head;
    while (p != NULL)
    {
        n = p->next;
        free(p);
        p = n;
    }
    free(*list);
    *list = NULL;
}

int main(int argc, char **argv)
{
    CreateLinkList(100);
    return 0;
}