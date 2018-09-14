#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "./queue.h"

/**
 * 初始化队列
 */
queue * init_queue()
{
    node * header_node = (node *)malloc(sizeof(node)); 
    assert(header_node != NULL);
    header_node->next = NULL;
    queue * queue_list = (queue *)malloc(sizeof(queue_list));
    assert(queue_list != NULL);
    queue_list->length = 0;
    queue_list->head = queue_list->tail = header_node;
    return queue_list;
}

void show_queue(queue * queue_list)
{
    assert(queue_list->length != 0);

    node * this = queue_list->head->next;
    while(this != NULL) {
        printf("%d --> ", this->data);
        this = this->next;
    }
    printf("NULL\n");
}

node * push(queue * queue_list, data_type value)
{
    node * new_node = (node *)malloc(sizeof(node));
    new_node->data = value;
    new_node->next = NULL;

    queue_list->tail->next = new_node;
    queue_list->tail = new_node;
    queue_list->length++;

    return new_node;
}

node pop(queue * queue_list)
{
    assert(queue_list->length != 0);

    node result;

    node * header_node = queue_list->head;
    node * pop_node = header_node->next;
    header_node->next = pop_node->next;
    result = *pop_node;
    free(pop_node);
    queue_list->length--;
    if(queue_list->length == 0) {
        queue_list->tail = queue_list->head;
    }

    return result;
}

int clear_queue(queue * queue_list)
{
    assert(queue_list->length != 0);

    queue_list->length = 0;
    queue_list->tail = queue_list->head;
    node * header_node = queue_list->head;
    node * this = header_node->next, * next;
    header_node->next = NULL;
    while(this != NULL) {
        next = this->next;
        free(this);
        this = next;
    }
    return OK;
}

#if IS_DEBUG
void main()
{

    //初始化
    queue * queue_list = init_queue();

    //入队
    push(queue_list, 1);
    push(queue_list, 2);
    push(queue_list, 3);

    //清空队列
    clear_queue(queue_list);

    //遍历
    show_queue(queue_list);

    //出队
    node first = pop(queue_list);
    first = pop(queue_list);
    first = pop(queue_list);
    first = pop(queue_list);
    printf("%d\n", first.data);
}
#endif
