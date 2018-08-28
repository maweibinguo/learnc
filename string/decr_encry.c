#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DEBUG 1
#define true 1
#define false 0
#define ALPHA_LENGTH 27

char * prepare_key(char * key);
int init_key(char * key);
int delete_repetition(char * key);
char * fill_left_char(char * key);

char * get_alpha_list();
char * get_dictionary(char const * key);
int getchar_position(char *key, char const char_num);
void encrypt(char * data, char const * key);
void decrypt(char * data, char const * key);

#if defined(DEBUG)
#define DEBUG_PRINT(pointer) printf("%s\n", pointer); exit(EXIT_FAILURE)
#endif

void main()
{
    char *key = "HeLlo";
    //char *list = "hELlow" 和下面的声明有所不同，最大的区别是:list指针指向的字符串常量是不可写的，只能够读
    char list[] = "hHEELlOow";//这里指向的内存地址是可写的
    encrypt(list, key);
    printf("\r\n\r\n============================================================\r\n\r\n");
    char de_list[] = "hDAAJlNow";
    decrypt(de_list, key);
}

char * prepare_key(char * key)
{
    char * list = NULL;

    if(init_key(key) == false) {
        printf("init key failed");
        exit(EXIT_FAILURE);
    }

    delete_repetition(key);

    list = fill_left_char(key);

    return list;
}

int init_key(char * key)
{
    int result = false;

    if(*key == '\0') {
        printf("key is empty");
        exit(EXIT_FAILURE);
    }

    while(*key != '\0') {
        if(isalpha(*key)) {
            //Segmentation fault, 由于使用了数组不会再发生这样的错误,之前是因为对只读内存进行了写操作
            *key = toupper(*key);
        } else {
            printf("%c is not a alpha\n", *key);
            exit(EXIT_FAILURE);
        }
        key++;
    }

    result = true;
    return result;
}

int delete_repetition(char * key)
{
    char search = ' ';
    char * pointer = NULL;

    while( (search = *key++) != '\0') {
        while( (pointer = strchr(key, search)) != NULL) {
            while(*pointer != '\0') {
                *pointer = *(pointer + 1);
                pointer++;
            } 
        }
    } 

    return true;
}

char * fill_left_char(char * key)
{
    char start = 'A', end = 'Z';
    char * pointer = malloc(ALPHA_LENGTH);
    strcpy(pointer, key);

    int offset = 0, key_length = strlen(key);
    for(start; start <= end; start++) {
        if(strchr(key, start) == NULL) {
            *(pointer + key_length + offset) = start;
            offset++;
        }
    }
    *(pointer + ALPHA_LENGTH - 1) = '\0';

    return pointer;
}

/**
 * 获取字母表
 */
char * get_alpha_list()
{
    //如果没有static这里是会报错 : warning: function returns address of local variable
    //我们一定要注意函数返回的是标量 还是地址:
    //1 、如果是标量的话只是一个单纯的值，这样不会有任何问题
    //2 、如果是地址的话，那么可能就会报上面的这个错误，因为该地址可能在函数运行结束后，内存被回收
    //我们可以通过static 方式 ，或者malloc的方式(malloc的内存需要我们手动free), 而static在整个运行期间内都存在
    static char alpha_list[ALPHA_LENGTH];
    char start = 'A', end = 'Z';
    int offset = 0;

    for(start; start <= end; start++) {
        alpha_list[offset] = start;
        offset++;
    }
    alpha_list[ALPHA_LENGTH - 1] = '\0';
    return alpha_list;
}

/**
 * 获取密码词典
 */
char * get_dictionary(char const * key)
{
    char desc[strlen(key) + 1];
    strcpy(desc, key);
    char * dictionary = prepare_key(desc);  
    return dictionary;
}

/**
 * 加密数据
 */
void encrypt(char * data, char const * key)
{
    char * alpha_list = get_alpha_list();
    char * dictionary = get_dictionary(key);

    //分配内存并初始化
    char * encrypt_data = malloc(strlen(data) + 1);
    strcpy(encrypt_data, data);

    //找到对应的下标并且初始化
    int index = 0;
    int position = -1;
    int length = strlen(data);
    while(index < length) {
        position = getchar_position(alpha_list, *(encrypt_data+ index)); 
        if(position != -1) {
            *(encrypt_data + index) = *(dictionary + position);
        }
        index++;
    }
    printf("alpha_list : %s\n", alpha_list);
    printf("dictionary : %s\n", dictionary);
    printf("origin_data :%s\n", data);
    printf("encrpty_data :%s\n", encrypt_data);
}

int getchar_position(char *key, char const char_num)
{
    int position = -1;

    int start = 0;
    for(start=0; start < strlen(key); start++) {
        if( *(key+start) == char_num ) {
            position = start;
            return position;
        } 
    }

    return position;
}

/**
 * 解密
 */
void decrypt(char * data, char const * key)
{
    char * alpha_list = get_alpha_list();
    char * dictionary = get_dictionary(key);

    //分配内存并初始化
    char * decrypt_data = malloc(strlen(data) + 1);
    strcpy(decrypt_data, data);

    //找到对应的下标并且初始化
    int index = 0;
    int position = -1;
    int length = strlen(data);
    while(index < length) {
        position = getchar_position(dictionary, *(decrypt_data+ index)); 
        if(position != -1) {
            *(decrypt_data + index) = *(alpha_list+ position);
        }
        index++;
    }

    printf("alpha_list : %s\n", alpha_list);
    printf("dictionary : %s\n", dictionary);
    printf("origin_data :%s\n", data);
    printf("decrpty_data :%s\n", decrypt_data);
}
