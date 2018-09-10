#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/io.h"
#include "../include/config.h"
#include "../include/operation.h"

static node * get_node_byid(int id);
static void __print_component(int id);

void new_component()
{
    component record;

    //确认组建数据
    confirm_id(&record.id);
    confirm_description(record.description);
    confirm_cost_each(&record.cost_each);
    confirm_sell_price(&record.sell_price);
    confirm_quantity(&record.quantity);
    record.sell_quantity = 0;
    record.profit = 0;
    record.sell_amount = 0;
    record.sell_cost = 0;
    float total_cost_each = record.quantity * record.cost_each;
    record.total_cost_each = total_cost_each;

    //将节点追加到尾部
    node * new_node = malloc(sizeof(node));
    new_node->data = record;
    if(root.number == 0) {
        new_node->next = NULL;
        new_node->prev = NULL;    
        root.next = new_node;
        root.prev = new_node;
    } else {
        node * old_last_node = root.next;
        new_node->next = NULL;
        new_node->prev = old_last_node;
        old_last_node->next = new_node;
    }
    
    root.number++;

    //写入文件
    write_component_data(record);
    
    sprintf(title_msg, "编号为%d的零件添加成功", record.id);
    print_title(title_msg);
}

void sale_component(int id)
{
    int retry_num = 1;
    int sell_quantity = 0;
    int match_num;
    while(retry_num <= MAX_RETRY_NUM) {
        node * ser_node = get_node_byid(id);    
        component * record = &ser_node->data;
        printf("请输入销售的数量:\n");
        match_num = scanf("%d", &sell_quantity);
        if(match_num != 1) {
            print_title("请输入一个正确的整数");
            retry_num++;
        } else if(sell_quantity <= 0) {
            print_title("销售数量必须是一个大于0的数字");
            retry_num++;
        } else if(sell_quantity > record->quantity) {
            sprintf(title_msg, "剩余库存数为%d", record->quantity);
            print_title(title_msg);
            retry_num++;
        } else {
            printf("销售数量%d已经录入成功\n\n", sell_quantity);
            float profit = 0;
            record->profit = profit;   
            record->quantity = record->quantity - sell_quantity;
            record->sell_quantity = record->sell_quantity + sell_quantity;
            record->sell_cost = record->sell_quantity * record->cost_each;
            record->sell_amount = record->sell_quantity * record->sell_price;
            record->profit = record->sell_amount - record->sell_cost;
            clear_buffer_stdin();
            //将内存数据写入文件
            write_component_data();
            break;
        }
        
        clear_buffer_stdin();
    }
}

void buy_component(int id)
{
    node * src_node = get_node_byid(id);
    component * data = &src_node->data;
    confirm_add_quantity(&data->quantity);
    write_component_data();
}

void delete_component(int id)
{
    node * prev = NULL, * next = NULL, * this = NULL;
    if(root.number == 0) {
        print_title("目前库存中没有任何的商品，请添加商品再操作");
        return;
    }

    this = get_node_byid(id);
    next = this->next;
    prev = this->prev;
    if(next == NULL && prev == NULL) {
        root.next = NULL;
        root.prev = NULL;
    } else if(next == NULL) {
        prev->next = NULL;
        root.next = prev;
    } else if(prev == NULL) {
        next->prev = NULL;
        root.prev = next;
    } else {
        prev->next = next;
        next->prev = prev;
    }

    //最后释放该节点存放的内存
    free(this);
    write_component_data();
    root.number--;
    print_title("删除成功");
}

void print_component(int id)
{
    node * s_node;
    if(s_node == NULL) {
        print_title("该零件不存在");
        return;
    } else {
        __print_component(id);
    }
   
}

void print_all_component()
{
    if(root.number == 0) {
        print_title("目前没有零部件");
        return;
    } else {
        __print_component(0);
    }
}

void confirm_description(char * desc)
{
    int retry_num = 1;
    char title_msg[64];

    while(retry_num <= MAX_RETRY_NUM) {
        printf("请输出零件描述:\n");
        clear_buffer_stdin();
        scanf("%19[A-Z0-9a-z_\t ]", desc);
        if(strlen(desc) > MAX_DESCRIPTION_LENGTH) {
            sprintf(title_msg, "最大的描述长度为%d字符",MAX_DESCRIPTION_LENGTH);
            print_title(title_msg);
            retry_num++;
        } else {
            printf("描述%s录入成功\n\n", desc);
            return;
        }
    }
}

void confirm_cost_each(float * cost_each)
{
    int retry_num = 1;

    while(retry_num <= MAX_RETRY_NUM) {
        clear_buffer_stdin();
        printf("请输入产品单价:\n");

        int match_num = scanf("%f", cost_each);
        if(match_num == 1 && *cost_each > 0) {
            printf("价格%4.2f录入成功\n\n", *cost_each);
            return;
        } else if(match_num != 1) {
            print_title("请输入一个正确的浮点数");
            retry_num++;
        } else {
            print_title("产品单价必须是一个大于0的数字");
            retry_num++;
        }
    }
}

void confirm_id(int * id)
{
    int retry_num = 1;

    while(retry_num <= MAX_RETRY_NUM) {
        clear_buffer_stdin();
        printf("请输入产品编号:\n");

        int match_num = scanf("%d", id);
        if(match_num != 1) {
            print_title("请输入一个正确的整数");
            retry_num++;
        } else if(id <= 0) {
            print_title("产品编号必须是一个大于0的数字");
            retry_num++;
        } else {
            node * result = get_node_byid(*id);
            if(result != NULL) {
                sprintf(title_msg, "产品编号%d已经存在", *id);         
                print_title(title_msg);
                retry_num++;
            } else {
                printf("产品编号%d已经录入成功\n\n", *id);
                return;
            }
        }
    }
}

void confirm_quantity(int * quantity)
{
    int retry_num = 1;

    while(retry_num <= MAX_RETRY_NUM) {
        clear_buffer_stdin();
        printf("请输入产品数量:\n");

        int match_num = scanf("%d", quantity);
        if(match_num != 1) {
            print_title("请输入一个正确的整数");
            retry_num++;
        } else if(quantity <= 0) {
            print_title("产品数量必须是一个大于0的数字");
            retry_num++;
        } else {
            printf("产品数量%d已经录入成功\n\n", *quantity);
            return;
        }
    }
}

void confirm_add_quantity(int * quantity)
{
    int retry_num = 1;
    int add_num = 0;
    while(retry_num <= MAX_RETRY_NUM) {
        clear_buffer_stdin();
        printf("请输入本次新增的产品数量:\n");

        int match_num = scanf("%d", &add_num);
        if(match_num != 1) {
            print_title("请输入一个正确的整数");
            retry_num++;
        } else if(add_num <= 0) {
            print_title("新增数量必须是一个大于0的数字");
            retry_num++;
        } else {
            *quantity = add_num + *quantity;
            printf("新增产品数量%d已经录入成功，当前库存数为%d\n\n", add_num, *quantity);
            return;
        }
    }
}

void confirm_sell_price(float * sell_price)
{
    int retry_num = 1;

    while(retry_num <= MAX_RETRY_NUM) {
        clear_buffer_stdin();
        printf("请输入销售价格:\n");

        int match_num = scanf("%f", sell_price);
        if(match_num != 1) {
            print_title("请输入一个正确的价格");
            retry_num++;
        } else if(sell_price <= 0) {
            print_title("销售价格不得为0");
            retry_num++;
        } else {
            printf("销售价格%4.2f已经录入成功\n\n", *sell_price);
            return;
        }
    }
}

static node * get_node_byid(int id)
{
    node * result = NULL;
    if(root.number == 0) {
        return result;
    }
        
    //是否该编号已经存在
    node * this = root.prev;
    while(this != NULL) {
        if(id == this->data.id) {
            result = this;
            return result;
        }
        this = this->next;
    }

    return result;
}

int get_operate_id()
{
    int id = 0;
    int retry_num = 1;

    while(retry_num <= MAX_RETRY_NUM) {
        clear_buffer_stdin();
        printf("请输入产品编号:\n");

        int match_num = scanf("%d", &id);
        if(match_num != 1) {
            print_title("请输入一个正确的整数");
            retry_num++;
        } else if(id <= 0) {
            print_title("产品编号必须是一个大于0的数字");
            retry_num++;
        } else {
            node * ser_node = get_node_byid(id);
            if(ser_node == NULL) {
               sprintf(title_msg, "编号为%d产品并不存在,请重新输入", id); 
               print_title(title_msg);
               retry_num++;
            } else {
                return id;
            }
        }
    }
    return 0;
}

static void __print_component(int id)
{
    printf("-----------+---------------------+-----------+-----------+-----------+-----------+-----------+-----------+------------\n");
    printf("   编号    |  描述               |   进货价  |  销售价   |  库存数   |  销售数   |  销售额   |   成本    | 利润\n");
    printf("-----------+---------------------+-----------+-----------+-----------+-----------+-----------+-----------+------------\n");

    if(id > 0) {
        node * ser_node = get_node_byid(id);
        component * data = &ser_node->data;
            printf(" %-10d| %s| %-10.2f| %-10.2f| %-10d| %-10d| %-10.2f| %-10.2f| %-10.2f\n",
                data->id,
                    strncat(data->description, "                       ", MAX_DESCRIPTION_LENGTH-strlen(data->description)),
                data->cost_each,
                data->sell_price,
                data->quantity,
                data->sell_quantity,
                data->sell_amount,
                data->sell_amount,
                data->profit);
    } else {
        node * this = root.prev;
        component * data;
        while(this != NULL) {
            data = &this->data;
            printf(" %-10d| %s| %-10.2f| %-10.2f| %-10d| %-10d| %-10.2f| %-10.2f| %-10.2f\n",
                    data->id,
                    strncat(data->description, "                       ", MAX_DESCRIPTION_LENGTH-strlen(data->description)),
                    data->cost_each,
                    data->sell_price,
                    data->quantity,
                    data->sell_quantity,
                    data->sell_amount,
                    data->sell_cost,
                    data->profit);
            this = this->next;
        }
    }
}
