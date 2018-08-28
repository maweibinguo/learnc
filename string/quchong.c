#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1;
#define false 0;

int delete_repetition(char * src);

void main()
{
    //数组名代表指针常量不能够被修改list++
    //字符串常量也不可以被修改
    char list[] = "a*&^^%%$bcdefbdeABf";
    int is_sensitive = false;
    delete_repetition(list);
    int start = 0;
    while(list[start] != '\0') {
        printf("%c\n", list[start]);
        start++;
    }
}

/**
 * 不支持形参有默认值
 */
int delete_repetition(char * src)
{
    char current_char = ' ';
    char * pointer = NULL;
    while( (current_char = *src++) != '\0') {
        while( ( pointer = strchr(src, current_char) ) != NULL) {
            while(*pointer != '\0') {
                *pointer = *(pointer + 1);
                pointer++;
            }     
        }
    }
}
