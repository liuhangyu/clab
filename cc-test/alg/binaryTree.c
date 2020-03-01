
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define MaxChild 10

typedef int dataType;
typedef struct node
{
    dataType data;
    struct node *lchild, *rchild;
} node, *binTree;

int pre_data_visit(binTree *t)
{
    if (*t != NULL)
    {
        printf("data=%d\n", (*t)->data);
        pre_data_visit(&((*t)->lchild));
        pre_data_visit(&((*t)->rchild));
    }
    return 0;
}

// int mid_data_visit(binTree t)
// {
//     if (t)
//     {

//         mid_data_visit(t->lchild);
//         printf("data=%d\n", t->data);
//         mid_data_visit(t->rchild);
//     }
//     return 0;
// }

// int end_data_visit(binTree t)
// {
//     if (t)
//     {
//         end_data_visit(t->lchild);
//         end_data_visit(t->rchild);
//         printf("data=%d\n", t->data);
//     }
//     return 0;
// }

int create_tree(binTree *t)
{
    dataType a;
    scanf("%d", &a);
    if (a == 0)
        *t = NULL;
    else
    {
        *t = (node *)malloc(sizeof(node));
        (*t)->data = a;
        create_tree((&(*t)->lchild));
        create_tree((&(*t)->rchild));
    }
}
//
int main(int argc, char **argv)
{
    binTree tree = (node *)malloc(sizeof(node));
    create_tree(&tree);
    pre_data_visit(&tree);

    return 0;
}
