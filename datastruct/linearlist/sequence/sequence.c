#include <stdio.h>
#include <stdlib.h>
#include "./sequence.h"

/**
 * 初始化顺序链表
 */
status init(sqlist * list)
{
    list->length = 0;
    return OK;
}

/**
 * 追加元素
 */
status append_ele(sqlist * list, data_type * value)
{
    if(list->length == MAX_SIZE) {
        return ERROR;
    }
    list->data[list->length] = *value;
    list->length++;
    return OK;
}

/**
 * 为顺序链表添加元素
 */
status insert_elem(sqlist * list, int position, data_type * value)
{
    if(list->length == MAX_SIZE) {
        return ERROR;
    }

    if(position < 0 || position >= MAX_SIZE || position > list->length) {
        return ERROR;
    }

    if(position == list->length) {
        list->data[position] = *value;
    } else {
        data_type this = list->length - 1, next = list->length;
        do{
            list->data[next] = list->data[this];
            next = this;
            this = this - 1;
        } while(this >= position);
        list->data[position] = *value;
    }
    list->length++;

    return OK;
}

/**
 * 删除顺序链表中的元素
 */
status delete_elem(sqlist * list, int position)
{
    if(list->length == 0) {
        return ERROR;
    }
    if(position < 0 || position >= list->length) {
        return ERROR;
    }

    if(position == list->length) {
        list->length--;
    } else {
        data_type this = position, next = position + 1;
        do {
            list->data[this] = list->data[next];
            this = next;
            next = next + 1;
        } while(next <= list->length);
    }
    list->length--;
    return OK;
}

/**
 * 更新顺序链表中的元素
 */
status update_elem(sqlist * list, int position, data_type * value)
{
    if(position < 0 || position >= list->length) {
        return ERROR;
    }
    list->data[position] = *value;
    return OK;
}

/**
 * 获取顺序链表中的元素
 */
data_type get_elem(sqlist * list, int position)
{
    if(position < 0 || position >= list->length) {
        printf("wrong");
        exit(EXIT_FAILURE);
    }
    return list->data[position];
}

/**
 * 清除顺序链表
 */
status clear_elem(sqlist * list)
{
    list->length = 0;
    return ERROR;  
}

/**
 * 合并顺序链表,将list_two中的元素合并到list_one中来
 */
status union_ele(sqlist * list_one, sqlist * list_two)
{
    int left_number = MAX_SIZE - list_one->length;
    if(list_two->length > left_number) {
        return ERROR;
    }
    int start = 0;
    for(start; start < list_two->length; start++) {
        int add_position = start + list_one->length;
        list_one->data[add_position] = list_two->data[start];
    }
    return OK;
}

/**
 * 遍历
 */
static traverse(sqlist * list)
{
    int start = 0;
    for(start; start<list->length; start++) {
        printf("position : %d | value : %c\n", start, list->data[start]);
    }
}

#if IS_DEBUG

void main()
{
    //定义静态链表，向系统要内存
    sqlist list;

    //初始化数据
    init(&list);   

    //追加元素
    int start = 0;
    for(start; start < 10; start++) {
        data_type value = 'A' + start;
        append_ele(&list, &value);
    }
    traverse(&list);
    
    printf("\n\n====================================\n\n");

    //插入元素
    data_type value = 'K';
    insert_elem(&list, 0, &value);
    traverse(&list);

    printf("\n\n====================================\n\n");

    //删除元素
    delete_elem(&list, 9);
    traverse(&list);

    printf("\n\n====================================\n\n");

    //删除元素
    value = 'W';
    update_elem(&list, 0, &value);
    traverse(&list);

    printf("\n\n====================================\n\n");

    //获取元素
    value = get_elem(&list, 8);
    printf("%c\n", value);
}

#endif
