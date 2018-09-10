#include <stdio.h>

typedef struct stu {
    int age;
    int sex;
}stu;

stu getit();

void main()
{
    stu me = getit();
    printf("%d\n", me.age);
}

stu getit()
{
    stu me = {
        29,
        1
    };
    return me;
}
