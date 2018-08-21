#include <stdio.h>
#include <stdlib.h>

#define LENGTH 1

typedef struct {
    union ProfessionValue {
        float score;
        char * class_name;
    } score_or_course;
    char * name;
    int num;
    char sex;
    char profession;
} table;

void title_print(char * content)
{
    printf("*****************************************************************************************");
    printf("\n%s\n", content);
    printf("*****************************************************************************************\n\n");
}

void main()
{
    title_print("请在依次输入相关信息");
    table list[LENGTH];    

    int start = 0;
    printf("\n请依次输入学生姓名, 学号, 性别(f/m), 职业(t/s)\n\n");
    for(start; start < LENGTH; start++) {
        title_print("开始录入...");
        scanf("%s %d   %c  %c", &list[start].name, &list[start].num, &list[start].sex, &list[start].profession);
        if(list[start].profession == 't') {
            printf("\n请输入%s教授的课程\n\n", &list[start].name);
            scanf("%s", &list[start].score_or_course.class_name);
        } else if(list[start].profession == 's') {
            printf("\n请输入%s的分数\n\n", &list[start].name);
            scanf("%f", &list[start].score_or_course.score);
        } else {
            printf("\n职业输入不正确, 请输入(t/s)\n\n");
            exit(EXIT_FAILURE);
        }
    }
   
    title_print("录入结果如下"); 
    printf("%20s %20s %20s %20s %20s\n\n", "Name", "Num", "Sex(f/m)", "Profession(t/s)", "Score/Course");
    for(start = 0; start < LENGTH; start++) {
        printf("\n%20s %20d %20c %20c", &list[start].name, list[start].num, list[start].sex, list[start].profession);
        if(list[start].profession == 't') {
            printf("%20s\n\n", &list[start].score_or_course.class_name);
        } else {
            printf("%20.2f\n\n", list[start].score_or_course.score);
        }
    }
}
