#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "./single.h"

/**
 * 初始化头指针
 */
node * init_header_node()
{
    node * header = (node *)malloc(sizeof(node));
    assert(header != NULL);
    header->next = NULL;
    return header;
}

/**
 * 头插法创建链表
 */
status init_chain_list_head(node * header)
{
    float start = 0;

    for(start; start < INIT_SIZE; start++) {
        node * new_node = (node *)malloc(sizeof(node));
        assert(new_node != NULL);
        new_node->data = start;
        new_node->next = header->next;
        header->next = new_node;
    }

    return OK;
}

/**
 * 尾插法创建链表
 */
status init_chain_list_foot(node * header)
{
    float start = 0;
    node * last = header;
    for(start; start < INIT_SIZE; start++) {
        node * new_node = (node *)malloc(sizeof(node));
        new_node->data = start;
        new_node->next = NULL;
        last->next = new_node;
        last = new_node;
    }
    return OK;
}

/**
 * 遍历节点
 */
void traverse_chain_node(node * header)
{
    if(header == NULL) {
        printf("element is empty\n");
        exit(1);
    }

    node * this = header->next;

    while(this != NULL) {
        printf("%4.2f --> ",this->data);
        this = this->next;
    }
    printf("NULL");
    printf("\n");
}

/**
 * 插入节点
 */
status insert_chain_node(node * header, int position, data_type value)
{
    if(position < 0) {
        return WRONG;
    }
    
    node * this, * prev;
    this = prev = header;
    int count = -1;
    while(this != NULL && count < position) {
        prev = this;
        this = this->next;
        count++;
    }

    if(this == NULL || count != position) {
        return WRONG;
    }
    node * new_node = (node *)malloc(sizeof(node));
    new_node->next = this->next;
    new_node->data = value;
    prev->next = new_node;
    free(this);
    return OK;
}

/**
 * 删除节点
 */
status delete_chain_node(node * header, int position)
{
    node * this, * prev;
    this = prev = header;

    int start = -1;
    while(this != NULL && start < position) {
        start++;
        prev = this;
        this = this->next;
    }

    if(this == NULL || start != position) {
        return WRONG;
    }

    prev->next = this->next;
    free(this);
    return OK;
}

/**
 * 清除所有节点
 */

status clear_chain_node(node * header)
{
    node * this, * next;
    this = next  = header->next;
    while(this != NULL) {
        next = this->next;
        free(this);
        this = next;
    }
    header->next = NULL;
    return OK;
}

/**
 * 获取节点
 */
node * get_chain_node(node * header, int position)
{
    int start = -1;
    node * this = header;
    while(this != NULL && start < position) {
        start++;
        this = this->next;
    }

    return this;
}

#if IS_DEBUG

void main()
{
    //初始化头指针
    node * header = init_header_node();

    //头插法
    //init_chain_list_head(header);
    //traverse_chain_node(header);

    //尾插法
    init_chain_list_foot(header);
    traverse_chain_node(header);

    //插入节点到指定位置
    insert_chain_node(header, 9, -3);
    traverse_chain_node(header);

    //删除指定位置的节点
    delete_chain_node(header, 1);
    traverse_chain_node(header);

    //清除所有节点
    //clear_chain_node(header);
    //traverse_chain_node(header);

    // 获取节点
    node * result = get_chain_node(header, 8);
    assert(result != NULL);
    printf("%4.2f\n", result->data);
}

#endif
