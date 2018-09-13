#ifndef SINGLE_H
#define SINGLE_H

#define IS_DEBUG 1

#define TRUE 1
#define FALSE 0

#define OK 1
#define WRONG 0

#define INIT_SIZE 10

typedef float data_type;

typedef int status;

typedef struct node {
    data_type data;
    struct node * next;
} node;

extern node * init_header_node();
extern status init_chain_list_head(node * header);
extern status init_chain_list_foot(node * header);
extern void traverse_chain_node(node * header);
extern status insert_chain_node(node * header, int position, data_type value);
extern status delete_chain_node(node * header, int position);
extern status clear_chain_node(node * header);
extern node * get_chain_node(node * header, int position);
#endif
