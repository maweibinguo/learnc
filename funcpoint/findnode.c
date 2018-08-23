#include <stdio.h>
#include "./callback.h"

void main()
{
    /**
     * 关于节点的测试
     */
    callback_node first_node, second_node, third_node, fourth_node, * root_pointer;

    root_pointer = &first_node;

    first_node.value = 1;
    first_node.link = &second_node;

    second_node.value = 3;
    second_node.link = &third_node;

    third_node.value = 5;
    third_node.link = &fourth_node;

    fourth_node.value = 7;
    fourth_node.link = NULL;

    int const search_value = 1;
    int const result_for_node = search_node(root_pointer, &search_value, callback_for_node);
    if(result_for_node == 0) {
        printf("the values %d is no exist\n", search_value);
    } else {
        printf("the value %d exists\n", search_value);
    }

    /**
     * 关于字符串的测试
     */
    char list[] = "hello world!";
    char const search_char = 'x';
    int const result_for_char = search_node(list, &search_char, callback_for_string);

    if(result_for_char == 0) {
        printf("the values %c is no exist\n", search_char);
    } else {
        printf("the value %c exists\n", search_char);
    }
}

int const search_node(  void const * root_pointer,
                        void const * search_value, 
                        int const (* callback)(void const * pointer, void const * value) )
{
    int result = 0;

    result = callback(root_pointer, search_value);

    return result;
}

int const callback_for_node(void const * now_value, void const * search_value)
{
    if(now_value == NULL) {
        return 0;
    } else {
        callback_node * now_value_node = (callback_node *)now_value;
        int * search_value_int = (int *)search_value;
        do {
            if(now_value_node->value == *search_value_int) {
                return 1;
            } else {
                now_value_node = now_value_node->link;
            }
        } while(now_value_node->link != NULL);

        return 0;
    }
}

int const callback_for_string(void const * now_value, void const * search_value)
{
    if(now_value == NULL) {
        return 0;
    } else {
        char const * pointer = (char const *)now_value;
        char const * search_value_char = (char const *)search_value;
        while(* pointer != '\0') {
            if(*pointer == *search_value_char) {
                return 1;
            } else {
                pointer++;
            }
        }
        return 0;
    }
}
