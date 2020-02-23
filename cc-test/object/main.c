#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef LINKLIST_H
#define LINKLIST_H

//////////////
/////////////////
// C 实现的多态
//https://www.ibm.com/developerworks/cn/linux/l-cn-cpolym/index.html
typedef struct Node *linkList;

typedef enum dtype
{
    dt_int = 1,
    dt_char,
    dt_string,
    dt_double
} dtype;

struct Node
{
    void *data;
    dtype dt;
    linkList next;

    //func
    void (*initFirst)(linkList, dtype, void *);
    void (*linkListOutput)(linkList);
};

linkList initLinklist();
void initFirst(linkList h, dtype type, void *data);
void linkListOutput(linkList h);
#endif

//define string
#define STR_LENGTH_DEF 5
typedef struct string
{
    int nLen;
    char data[0];
} string;

string *new_str(int len, char *p)
{
    string *str = (string *)malloc(sizeof(string) + len);
    memset(str->data, 0, len);
    str->nLen = len;
    memcpy(str->data, p, len);
    // printf("%s\n", str->data);
    return str;
}

void free_str(string *str)
{
    if (str != NULL)
    {
        free(str);
    }
}

//main.c
linkList
initLinklist(dtype type)
{
    linkList link = (linkList)malloc(sizeof(struct Node));

    switch (type)
    {
    case dt_int:
        link->data = (int *)malloc(sizeof(int));
        break;
    case dt_char:
        link->data = (char *)malloc(sizeof(char));
        break;
    case dt_string:
        link->data = (string *)malloc(sizeof(string) + STR_LENGTH_DEF);
        memset(link->data, 0, STR_LENGTH_DEF);
        ((string *)(link->data))->nLen = STR_LENGTH_DEF;
        break;
    case dt_double:
        link->data = (double *)malloc(sizeof(double));
        break;
    default:
        printf("You should point which output function is wanted!\n");
        break;
    }

    // link->data = NULL;
    link->next = NULL;
    link->dt = type;

    link->initFirst = initFirst;
    link->linkListOutput = linkListOutput;
    return link;
}

void initFirst(linkList h, dtype type, void *data)
{
    linkList link = initLinklist(type);
    switch (type)
    {
    case dt_int:
        *(int *)(link->data) = *(int *)(data);
        break;
    case dt_char:
        *(char *)(link->data) = *(char *)(data);
        break;
    case dt_string:
        if (((string *)(link->data))->nLen < ((string *)data)->nLen)
        {
            // printf("too length %d %d\n", ((string *)(link->data))->nLen, ((string *)data)->nLen);
            link->data = (string *)realloc(link->data, ((string *)data)->nLen);
            memset(link->data, 0, ((string *)data)->nLen);
            ((string *)(link->data))->nLen = ((string *)data)->nLen;
            memcpy(((string *)(link->data))->data, ((string *)data)->data, ((string *)data)->nLen);
            // printf("%s\n", ((string *)data)->data);
        }
        else
        {
            memcpy(((string *)(link->data))->data, ((string *)data)->data, ((string *)data)->nLen);
        }
        break;
    case dt_double:
        *(double *)(link->data) = *(double *)(data);
        break;
    default:
        printf("You should point which output function is wanted!\n");
        break;
    }
    // link->data = *data;
    link->next = h->next;
    h->next = link;
}

void linkListOutput(linkList h)
{
    linkList p = h->next;
    while (p)
    {
        switch (p->dt)
        {
        case dt_int:
            printf("%d\n", *(int *)(p->data));
            p = p->next;
            break;
        case dt_char:
            printf("%c\n", *(char *)(p->data));
            p = p->next;
            break;
        case dt_string:
            printf("%s %d\n", ((string *)(p->data))->data, ((string *)(p->data))->nLen);
            p = p->next;
            break;
        case dt_double:
            printf("%f\n", *(double *)(p->data));
            p = p->next;
            break;
        default:
            printf("You should point which output function is wanted!\n");
        }
    }
    // printf("\n");
}

void freelinkList(linkList h)
{
    linkList ptr = NULL;
    linkList p = h->next;
    while (p)
    {
        switch (p->dt)
        {
        case dt_int:
            free(p->data);
            ptr = p;
            p = p->next;
            free(ptr);
            break;
        case dt_char:
            free(p->data);
            ptr = p;
            p = p->next;
            free(ptr);
            break;
        case dt_string:
            free_str((string *)(p->data));
            ptr = p;
            p = p->next;
            free(ptr);
            break;
        case dt_double:
            free(p->data);
            ptr = p;
            p = p->next;
            free(ptr);
            break;
        default:
            printf("You should point which output function is wanted!\n");
        }
    }
    // printf("\n");
    // if (h)
    // {
    //     free(h);
    // }
}

int main()
{
    //int
    if (0)
    {
        linkList head = initLinklist(dt_int);
        int i;
        for (i = 0; i < 20; i++)
        {
            initFirst(head, dt_int, &i);
        }
        linkListOutput(head);
        if (head != NULL)
        {
            freelinkList(head);
            free(head->data);
            free(head);
        }
    }

    //char
    if (0)
    {
        linkList head = initLinklist(dt_char);
        int i;
        for (i = 0; i < 20; i++)
        {
            char a = i + 33;
            initFirst(head, dt_char, &a);
        }
        linkListOutput(head);
        if (head != NULL)
        {
            freelinkList(head);
            free(head->data);
            free(head);
        }
    }

    if (0)
    {
        linkList head = initLinklist(dt_string);
        int i;
        for (i = 0; i < 20; i++)
        {
            char p[20];
            int ret = sprintf(p, "hello world %d", i);
            if (ret != -1)
            {
                // printf("ret = %d\n", ret);
                string *str = new_str(sizeof(p), p);
                if (str != NULL)
                {
                    initFirst(head, dt_string, str);
                    free_str(str);
                }
            }
        }
        linkListOutput(head);
        if (head != NULL)
        {
            freelinkList(head);
            free(head->data);
            free(head);
        }
    }

    if (1)
    {
        linkList head = initLinklist(dt_double);
        int i;
        for (i = 0; i < 20; i++)
        {
            double a = i + 33.11;
            initFirst(head, dt_double, &a);
        }
        linkListOutput(head);
        if (head != NULL)
        {
            freelinkList(head);
            free(head->data);
            free(head);
        }
    }
    return 0;
}
