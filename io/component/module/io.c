#include <stdio.h>
#include <stdlib.h>
#include "../include/io.h"

static FILE * fp = NULL;

void print_title(char * title)
{
    printf("\n-----------+---------------------+-----------+-----------+-----------+-----------+-----------+-----------+------------\n");
    printf("%s", title);
    printf("\n-----------+---------------------+-----------+-----------+-----------+-----------+-----------+-----------+------------\n");
}

void clear_buffer_stdin()
{
    scanf("%*[^\n]");
    scanf("%*c");
}

size_t write_component_data()
{
    if(root.number == 0) {
        return root.number;
    } else {
        fp = fopen(FILE_NAME, "wb+");
        node * this = root.prev;
        component item;
        int add_num;
        while(this != NULL) {
            item = this->data;
            add_num = fwrite(&item, sizeof(component), 1, fp);
            if(add_num != 1) {
                perror("");
                exit(EXIT_FAILURE);
            }
            this = this->next;
            root.number++;
        }
        fclose(fp);
        return root.number;
    }
}

header init()
{
    if(fp == NULL) {
        fp = fopen(FILE_NAME, "rb");
    }

    //说明文件不存在
    if(fp == NULL) {
        return root;
    }

    //只是定义了指针变量，并未开辟实际存储数据的内存
    node * this = NULL;
    node * prev = NULL;
    component item;

    //fread 第一个参数需要的是实在的内存,单纯的指针并没有组件需要的内存空间
    while(fread(&item, sizeof(component), 1, fp) == 1) {
        if(root.number == 0) {
            this = prev = malloc(sizeof(node));
            this->data = item;
            this->next = NULL;
            this->prev = NULL;
            root.next = root.prev = this;
        } else {
            this = malloc(sizeof(node)); 
            this->data = item;
            this->next = NULL;
            this->prev = prev;

            prev->next = this;
            prev = this;
        }
        root.number++;
    }

    fclose(fp);
    return root;
}
