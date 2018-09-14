#ifndef QUEUE_H
#define QUEUE_H

#define IS_DEBUG 1
#define INIT_SIZE 10

#define OK 1
#define WRONG 0

typedef int data_type;

typedef struct node{
    data_type data;
    struct node * next;
}node;

typedef struct queue{
    node * head;
    node * tail;
    int length;
}queue;

#endif
