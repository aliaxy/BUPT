/*
14-7 实验11_3_结构排序

有n名学生，每个学生的属性包括姓名与总成绩。已知学生的姓名与总成绩，你的任务是将学生的信息按照以下方式排序：
首先比较总成绩，总成绩高的在前面，总成绩低的在后面，当总成绩相同时，
你要比较学生的姓名，姓名字典序小的同学在前面，姓名字典序大的同学在后面(ASCII码顺序)。
n的范围是1—100；学生的姓名中只能包含大小写字母，不会超过20个字符；总成绩为整数。

要求：在本题中，你要设计一个结构来存储学生的信息。在此结构中，需要有一个字符数组来存储姓名，一个整型变量存储总成绩。

输入格式:
首先输入一个正整数n，代表学生的数量，1<=n<=100；每名学生的信息按照姓名、总成绩的顺序输入（空格分开），每名学生信息占一行。具体格式见样例。

输出格式:
n名学生的信息，姓名占一行，总成绩占一行，输出顺序要按照题目的要求，每名同学的信息后都再输出一个空行。
注意：每名同学的信息后都再输出一个空行。

输入样例:
4
AlbertEinstein 1328
GeorgeWalkerBush 860
LiuMengmeng 1475
BillGates 1328
输出样例:
Name:LiuMengmeng
total:1475

Name:AlbertEinstein
total:1328

Name:BillGates
total:1328

Name:GeorgeWalkerBush
total:860

*/
#include <stdio.h>
#include <string.h>

struct student
{
    char name[30];
    int total;
};

int main(void)
{
    int n, i, j;
    char c;
    struct student stu[101];
    struct student temp;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        getchar();
        scanf("%c", &c);
        for (j = 0; c != ' '; j++)
        {
            stu[i].name[j] = c;
            scanf("%c", &c);
        }
        stu[i].name[j] = '\0';
        scanf("%d", &stu[i].total);
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (stu[j].total < stu[j + 1].total || (stu[j].total == stu[j + 1].total && strcmp(stu[j].name, stu[j + 1].name) > 0))
            {
                temp = stu[j];
                stu[j] = stu[j + 1];
                stu[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        printf("Name:");
        puts(stu[i].name);
        printf("total:%d\n\n", stu[i].total);
    }
}