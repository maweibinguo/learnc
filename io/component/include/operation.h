#ifndef OPERATION_H
#define OPERATION_H 

extern void new_component();

extern void sale_component(int id);

extern void buy_component(int id);

extern void delete_component(int id);

extern void print_component(int id);

extern void print_all_component();

extern void confirm_description(char * desc);

extern void confirm_total_const_each(float * total_cost_each);

extern void confirm_cost_each(float * cost_each);

extern void confirm_id(int * id);

extern void confirm_quantity(int * quantity);

extern void confirm_add_quantity(int * add_quantity);

extern void confirm_sell_price(float * sell_price);

extern int get_operate_id();
#endif
