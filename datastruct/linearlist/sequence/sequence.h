#ifndef SEQUENCE_H
#define SEQUENCE_H

#define IS_DEBUG 1
#define MAX_SIZE 20
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

typedef int status;

typedef int data_type;

typedef struct sqlist {
    data_type data[MAX_SIZE];
    int length;
} sqlist;

extern status init(sqlist * list);

extern status append_ele(sqlist * list, data_type * value);

extern status add_elem(sqlist * list, int position, data_type * value);

extern status insert_elem(sqlist * list, int position, data_type * value);

extern status delete_elem(sqlist * list, int position);

extern status update_elem(sqlist * list, int position, data_type * value);

extern data_type get_elem(sqlist * list, int position);

extern status clear_elem(sqlist * list);

extern status union_ele(sqlist * list_one, sqlist * list_two);

#endif
