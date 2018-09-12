#include <stdio.h>
#include <stdlib.h>
#include "./single.h"

void main()
{
    single_node first_node, second_node, third_node, fourth_node, * root_pointer;

    root_pointer = &first_node;

    first_node.value = 1;
    first_node.link = &second_node;

    second_node.value = 3;
    second_node.link = &third_node;

    third_node.value = 5;
    third_node.link = &fourth_node;

    fourth_node.value = 7;
    fourth_node.link = NULL;

    single_node * current =  insert_node(&root_pointer, 100);

    int index = 1;
    while(current != NULL) {
        printf("the %d node, the value is %d\n", index++, current->value);
        current = current->link;
    }
}

single_node * insert_node(single_node ** direct_root, int insert_value)
{
    single_node * new_node_pointer = malloc(sizeof(single_node));  

    //指针也是有类型的: * direct_root 得到的是一个single_node 类型的指针
    single_node * root_pointer_origin = * direct_root;

    /**
     * 如果原有不存在任何节点
     */
    if(root_pointer_origin == NULL) {
        root_pointer_origin = new_node_pointer;
        new_node_pointer->value = insert_value;
        new_node_pointer->link = NULL;
        return root_pointer_origin;
    }

    /**
     * 是否比最小的节点还要小
     */
    if(root_pointer_origin->value > insert_value) {
        new_node_pointer->value = insert_value;
        new_node_pointer->link = root_pointer_origin;
        //改变根指针的指向 
        root_pointer_origin = new_node_pointer;
    } else {
        /**
         * 遍历直到比最后一个节点还大
         */ 
        single_node * current = root_pointer_origin;
        single_node * previous = NULL;
        while(current->value < insert_value) {
            previous = current;
            current = current->link;
            if(current == NULL) {
                break;
            }
        }

        if(current == NULL) {
            previous->link = new_node_pointer;
            new_node_pointer->link = NULL;
        } else {
            previous->link = new_node_pointer;
            new_node_pointer->link = current;
        }
        new_node_pointer->value = insert_value;
    }


    return root_pointer_origin;
}
