#ifndef SINGLE_H
#define SINGLE_H

#define IS_DEBUG 1

#define INIT_SIZE 10

typedef int data_type;

typedef struct node {
    union{
        data_type data;
        int length;
    } data;
    struct node * next;
} node, * header_node;

extern node * init_chain_list_head();

extern node * init_chain_list_tail();

extern node * delete_node(node * header_node, int position);

extern node * insert_node(node * header_node, int position, data_type value);

extern node * clear_node(node * header_node);

extern void show_list(node * header_node);
#endif
