#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct char_list_link {
    struct char_list_link * next;
    struct char_list_link * previous;
    char char_name;
    int number;
} char_list_link;

char_list_link * create_list_link(char const * chars);

char_list_link * get_node_by_name(char_list_link * root_pointer, char const char_name);

char_list_link * delete_node_by_name(char_list_link ** root_pointer, char const char_name);

char_list_link * update_node_by_name(char_list_link ** root_pointer, char const char_name, char_list_link * new_node);

void main()
{
    char_list_link * root_pointer = create_list_link("abcd");
    //char_list_link * current = get_node_by_name(root_pointer, 'b');
    
    //char_list_link * deleted_node = delete_node_by_name( &root_pointer, 'b');
    /*if(deleted_node == NULL) {
        printf("%c is not exists\n", 'b'); 
    } else {
        printf("%c\n", deleted_node->char_name);
    }*/

    char_list_link new_node = {
        NULL,
        NULL,
        'j',
        1
    };
    update_node_by_name(&root_pointer, 'c', &new_node);
    char_list_link *new_list = root_pointer;
    while(new_list != NULL) {
        printf("node %c | %d \n", new_list->char_name, new_list->number);
        new_list = new_list->next;
    }
}


/**
 * create double link
 */
char_list_link * create_list_link(char const * chars)
{
    int length = strlen(chars), start = 0;
    char_list_link * root_pointer, * previous = NULL, * current;
    for(start; start < length; start++) {
        if(start == 0) {
            root_pointer = current = (char_list_link *)malloc(sizeof(char_list_link));
            current->previous = previous;
            current->next = NULL;
            current->char_name = *(chars+start);
            current->number=0;
            previous = current;
        } else {
            current = (char_list_link *)malloc(sizeof(char_list_link));
            current->previous = previous;
            current->next = NULL;
            current->char_name = *(chars+start);
            current->number=0;

            previous->next = current; 
            previous = current;
        }
    } 
    return root_pointer;
}

/**
 * get node by name
 */
char_list_link * get_node_by_name(char_list_link * root_pointer, char const char_name)
{
    char_list_link * current = root_pointer;
    while(current != NULL) {
        if(current->char_name == char_name) {
            return current;
        } else {
            current = current->next;
        }
    } 
    return current;
}

/**
 * delete node by name
 */
char_list_link * delete_node_by_name(char_list_link ** root_pointer, char const char_name)
{
    char_list_link * current = *root_pointer;
    while(current != NULL) {
        if(current->char_name == char_name) {
            if(current->previous == NULL) {
                *root_pointer = current->next;
            } else if(current->next == NULL) {
                current->previous->next = NULL;
            } else {
                current->previous->next = current->next;
                current->next->previous = current->previous;
            }
            return current;
        }
        current = current->next;
    } 
    return current;
}

/**
 * update node by name
 */
char_list_link * update_node_by_name(char_list_link ** root_pointer, char const char_name, char_list_link * new_node)
{
    char_list_link * current = *root_pointer;
    while(current != NULL) {
        if(current->char_name == char_name) {
            if(current->previous == NULL) {
                *root_pointer = new_node;
                new_node->previous = NULL;
                new_node->next = current->next;
            } else if(current->next == NULL) {
                current->previous->next = new_node;
                new_node->previous = current->previous;
                new_node->next = NULL;
            } else {
                current->previous->next = new_node;
                new_node->previous = current->previous;
                new_node->next = current->next;
                current->next->previous = new_node;
            }
            return new_node;
        }
        current = current->next;
    } 
    return current;
}
