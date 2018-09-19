#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int data_type;

typedef struct node{
    struct node * left_pointer;
    struct node * right_pointer;
    data_type data;    
} node, * bitree;

static char str_list[] = "AB#D##C##";
static int index = 0;

void create_node(bitree * tree)
{
    char data = str_list[index++];
    printf("%c\n", data);
    if(data != '#') {
        *tree = (bitree)malloc(sizeof(node));
        (*tree)->data = data;
        create_node(&((*tree)->left_pointer));
        create_node(&((*tree)->right_pointer)); 
    }
}

void pre_show_bitree(bitree tree_list)
{
    if(tree_list != NULL) {
        printf("%c\n", tree_list->data);       
        pre_show_bitree(tree_list->left_pointer);
        pre_show_bitree(tree_list->right_pointer);
    } else {
        printf("#\n");
    }
    return;
}

void destory_bitree(bitree * tree_list)
{
    if((*tree_list)->left_pointer) {
        destory_bitree( &((*tree_list)->left_pointer) );
    }
    if((*tree_list)->right_pointer) {
        destory_bitree( &( (*tree_list)->right_pointer ) );
    }
    free(*tree_list);
    *tree_list = NULL;
}

void main()
{
    bitree tree = NULL;

    create_node(&tree);

    printf("\n++++++++++++++++++++++++++++++++++++++\n");

    pre_show_bitree(tree);

    printf("\n++++++++++++++++++++++++++++++++++++++\n");

    destory_bitree(&tree);
    pre_show_bitree(tree);
}
