#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "./include/config.h"
#include "./include/io.h"
#include "./include/menu.h"
#include "./include/operation.h"

#define PASSWORD "123456"
extern int auth_password();

void main(void)
{
    int auth_res = auth_password();
    if(auth_res == false) {
        exit(EXIT_FAILURE);
    }

    root = init();
    int operation;
    int id=0;
    while(true) {
        print_menu();
        print_title("请选择你的操作:");
        scanf("%d", &operation);
        switch(operation) {
           case NEW:
                new_component();                
                break;
           case BUY:
                id = get_operate_id();
                if(id) buy_component(id);
                break;
           case SALE:
                id = get_operate_id();
                if(id) sale_component(id);
                break;
           case DELETE:
                id = get_operate_id();
                if(id) delete_component(id);
                break;
           case PRINT_NUM:
                id = get_operate_id();
                if(id) print_component(id);
                break;
           case PRINT_ALL:
                print_all_component();
                break;
           case END:
                return;
                break;
           default:
                break;
        }
    }
}

int auth_password()
{
    char password[32];
    int retry_num = 1;
    sprintf(title_msg, "请输入系统的使用密码, 最多重试%d次:", MAX_RETRY_NUM);
    print_title(title_msg);
    for(retry_num; retry_num <= MAX_RETRY_NUM; retry_num++) {
        scanf("%s",password);
        if(strcmp(password, PASSWORD) == 0) {
            print_title("密码输入正确");
            return true;
        } else {
            int left_retry_num = MAX_RETRY_NUM - retry_num;
            if(left_retry_num > 0) {
                sprintf(title_msg, "密码输入错误，还可以尝试%d次", MAX_RETRY_NUM - retry_num);
                print_title(title_msg);
            } else {
                sprintf(title_msg, "密码输入错误，系统退出");
                print_title(title_msg);
                return false;
            }
        }
    }
}
