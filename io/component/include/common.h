#ifndef COMMON_H
#define COMMON_H

#define true 1
#define false 0

//operation
#define NEW 1
#define BUY 2
#define SALE 3
#define DELETE 4
#define PRINT_NUM 5
#define PRINT_ALL 6
#define END 7

typedef struct component {
    char description[20];//描述
    float cost_each;//进货价
    float total_cost_each;//总进货价
    int id;//编号
    int quantity;//库存数量
    int sell_quantity;//销售数量
    float sell_price;//销售价
    float profit;//利润
    float sell_amount;//销售总金额
    float sell_cost;//销售成本
} component;

typedef struct node {
    component data;
    struct node * next;
    struct node * prev;
}node;

typedef struct header {
    node * next;
    node * prev;
    size_t number;
}header;

extern header root;

extern char title_msg[64];

#endif
