#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "./single.h"

node * init_chain_list_head()
{
    node * header_node = malloc(sizeof(node));
    header_node->next = NULL;
    header_node->data.length = 0;

    int start = 0;
    for(start; start < INIT_SIZE; start++) {
        node * new_node = (node *)malloc(sizeof(node));  
        new_node->data.data = start;
        new_node->next = header_node->next;
        header_node->next = new_node;
        header_node->data.length++;
    }

    return header_node;
}

node * init_chain_list_tail()
{
    node * header_node = malloc(sizeof(node));
    header_node->next = NULL;
    header_node->data.length = 0;

    int start = 0;
    node * prev = header_node;
    for(start; start < INIT_SIZE; start++) {
        node * new_node = (node * )malloc(sizeof(node));
        new_node->data.data = start;
        new_node->next = NULL;
        prev->next = new_node;
        prev = new_node;
        header_node->data.length++;
    }

    return header_node;
}

node * delete_node(node * header_node, int position)
{
    assert(position >= 0);
    assert(position < header_node->data.length);
    assert(header_node->data.length != 0);

    node * this = header_node->next, * prev = header_node;
    int start = 0;
    while(this != NULL && start < position) {
        prev = this;
        this = this->next;
        start++;
    }

    assert(this != NULL);
    assert(start == position);
    
    prev->next = this->next;
    free(this);
    header_node->data.length--;

    return header_node;
}

node * insert_node(node * header_node, int position, data_type value)
{
    assert(position >= 0);

    node * this = header_node->next, * prev = header_node;
    int start = 0;
    while(this != NULL && start < position) {
        prev = this;
        this = this->next;
        start++;
    }

    assert(this != NULL);
    assert(start == position);

    node * new_node = (node *)malloc(sizeof(node));
    new_node->data.data = value;
    new_node->next = this;
    prev->next = new_node;
    header_node->data.length++;

    return header_node;
}

node * clear_node(node * header_node)
{
    assert(header_node != NULL);

    node * this = header_node, * next = NULL;
    while(this != NULL) {
        next = this->next;
        free(this);
        this = next;
    }

    header_node->data.length = 0;
    header_node->next = NULL;
    return header_node;
}

void show_list(node * header_node)
{
    assert(header_node != NULL);
    node * this = header_node->next;
    printf("( length : %d )", header_node->data.length);
    while(this != NULL) {
        printf("%d --> ", this->data.data);
        this = this->next;
    }
    printf("NULL\n");
}

#if IS_DEBUG
void main()
{
    node * header_node = init_chain_list_head();
    show_list(header_node);

    header_node = init_chain_list_tail();
    show_list(header_node);

    header_node = delete_node(header_node, 2);
    show_list(header_node);

    header_node = insert_node(header_node, 8, 100);
    show_list(header_node);

    header_node = clear_node(header_node);
    show_list(header_node);
}
#endif
