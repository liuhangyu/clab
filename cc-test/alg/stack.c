#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define STACK_INIT_SIZE 10
#define STACK_INCR_SIZE 5

typedef int ElemType;

typedef struct
{
    ElemType *tail;
    ElemType *top;
    int stacksize;
} Stack;

int init_stack(Stack *s)
{
    s->tail = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if (s->tail == NULL)
    {
        return -1;
    }
    s->top = s->tail;
    s->stacksize = STACK_INIT_SIZE;
    return 0;
}

int push(Stack *s, ElemType e)
{
    if (s->top - s->tail >= s->stacksize)
    {
        s->tail = (ElemType *)realloc(s->tail, (s->stacksize + STACK_INCR_SIZE) * sizeof(ElemType));
        if (s->tail == NULL)
        {
            return -1;
        }
        s->top = s->tail + s->stacksize; // * sizeof(ElemType);
        s->stacksize = s->stacksize + STACK_INCR_SIZE;
    }
    *(s->top) = e;
    s->top = ++(s->top); // + 1 * sizeof(ElemType);
    printf("%d %p\n", e, s->top);
    return 0;
}

int pop(Stack *s, ElemType *e)
{
    if (s->top == s->tail)
    {
        return -1;
    }
    s->top = --(s->top); // - 1 * sizeof(ElemType);
    *e = *(s->top);
    return 0;
}

int clear_stack(Stack *s)
{
    s->top = s->tail;
    return 0;
}

int destory_stack(Stack *s)
{
    int i = 0;
    // ElemType *p = NULL;
    // for (i = 0; i < s->stacksize; i++)
    // {
    //     p = s->tail;
    //     s->tail = p + 1;
    //     free(p);
    // }
    free(s->tail);
    s->tail = s->top = NULL;
    s->stacksize = 0;
}

int main(int argc, char **argv)
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    int ret = init_stack(s);
    printf("create ret = %d\n", ret);

    int i = 0;
    for (i = 0; i < 20; i++)
    {
        ElemType a = i;
        ret = push(s, a);
        if (ret == -1)
        {
            printf("push ret = %d\n", ret);
        }
    }
    for (i = 0; i < 20; i++)
    {
        ElemType a;
        ret = pop(s, &a);
        if (ret == -1)
        {
            printf("pop failt ret = %d\n", ret);
        }
        else
        {
            printf("pop %d ret = %d\n", a, ret);
        }
    }

    destory_stack(s);
    free(s);
    return 0;
}