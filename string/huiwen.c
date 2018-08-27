#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ishuiwen(char * str);
void main()
{
    char * str = "abc*(78ba";
    int result = ishuiwen(str);   
    printf("%d\n", result);
}

/**
 * 数组不支持可变数组，否则编译报错，也就是下标不能为变量
 */
int ishuiwen(char * str)
{
    int result = 0;

    char * pointers = malloc(strlen(str) + 1);
    int char_number = 0;
    while(*str != '\0') {
        char current_char = *str;
        if( islower(current_char) || isupper(current_char) ) {
            *(pointers+char_number) = tolower(current_char);
            char_number++;
        }
        str++;
    }
    *(pointers+char_number) = '\0';

    printf("%s\n", pointers);

    char * reverse_pointer = malloc(char_number);
    int length,  offset;
    length = offset = char_number - 1;
    while(offset >= 0) {
        *(reverse_pointer + (length - offset)) = *(pointers + offset);
        offset--;
    }
    *(reverse_pointer + char_number) = '\0';
    printf("%s\n", reverse_pointer);

    if(strcmp(pointers, reverse_pointer) == 0) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}
