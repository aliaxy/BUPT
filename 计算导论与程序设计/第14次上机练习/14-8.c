/*
14-8 实验11_7_学生信息管理系统

创建学生信息管理系统，具体要求如下：

学生信息包括：学号 姓名 数学成绩 英语成绩 计算机成绩
功能1：添加学生信息
执行1时，输入学号，姓名，三门科目成绩；如果添加学生成功则输出“Add success”，如果学生已存在则输出“Students already exist”
功能2：删除学生信息
执行2时，输入学号信息；如果学生不存在，输出“Students do not exist”，如果存在，则输出“Delete success”
功能3：更改学生成绩信息
执行3时，输入学号信息；如果学生不存在，输出“Students do not exist”，如果存在，输出“Update success”
功能4：显示学生平均分成绩
执行4时，输入学号信息；如果学生不存在，输出“Students do not exist”，如果存在，则输出学生信息，如下格式：
Student ID:2019989890
Name:Jerry
Average Score:89.3
其中平均分为三门科目相加除以3，保留一位小数，每行之间换行。

输入格式:
第一行为一个整数n(0<n<130)，后边共n行，每一行表示执行一种功能。其中1，2，3，4分别对应执行上面4种功能，具体格式见输入样例。
测试用例保证：学号和名字均为长度不超过10的字符串，各门课成绩为0到100之间的整数。

输出格式:
输入样例:
8
1 201817123 Tom 89 80 76
1 2019989890 Jerry 78 99 67
4 201817123
2 201817123
4 201817123
4 2019989890
3 2019989890 79 90 99
4 2019989890
输出样例:
Add success
Add success
Student ID:201817123
Name:Tom
Average Score:81.7
Delete success
Students do not exist
Student ID:2019989890
Name:Jerry
Average Score:81.3
Update success
Student ID:2019989890
Name:Jerry
Average Score:89.3
*/
#include <stdio.h>
#include <string.h>
struct infor
{
    char ID[11];
    char name[11];
    int math, English, computer;
};
typedef struct infor Stu;

int find(Stu *sample, Stu stu, int *count);
void add(Stu *stu, int *count);
void delete (Stu *stu, int *count);
void change(Stu *stu, int *count);
void show(Stu *stu, int *count);

int main(void)
{
    int n, i, num, count = 0;
    Stu stu[130] = {0};
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &num);
        switch (num)
        {
            case 1:
                add(stu, &count);
                break;
            case 2:
                delete (stu, &count);
                break;
            case 3:
                change(stu, &count);
                break;
            case 4:
                show(stu, &count);
                break;
        }
    }
    return 0;
}

int find(Stu *sample, Stu stu, int *count)
{
    int j, i = 0;
    while (i < (*count))
    {
        for (j = 0; sample[i].ID[j] == stu.ID[j] && stu.ID[j]; j++)
        {
            if (stu.ID[j + 1] == '\0')
            {
                return i;
            }
        }
        i++;
    }
    return -1;
}

void add(Stu *stu, int *count)
{
    Stu cop;
    scanf("%s", &cop.ID);
    scanf("%s", &cop.name);
    scanf("%d %d %d", &cop.math, &cop.English, &cop.computer);
    if (find(stu, cop, count) == -1)
    {
        stu[*count] = cop;
        printf("Add success\n");
        (*count)++;
    }
    else
        printf("Students already exist\n");
}
void delete (Stu *stu, int *count)
{
    Stu cop;
    int i, j;
    scanf("%s", &cop.ID);
    i = find(stu, cop, count);
    if (i != -1)
    {
        for (j = i; j < *count; j++)
            stu[j] = stu[j + 1];
        printf("Delete success\n");
        (*count)--;
    }
    else
        printf("Students do not exist\n");
}
void change(Stu *stu, int *count)
{
    Stu cop;
    int i;
    scanf("%s", &cop.ID);
    scanf("%d %d %d", &cop.math, &cop.English, &cop.computer);
    if (find(stu, cop, count) != -1)
    {
        i = find(stu, cop, count);
        stu[i].math = cop.math;
        stu[i].English = cop.English;
        stu[i].computer = cop.computer;
        printf("Update success\n");
    }
    else
        printf("Students do not exist\n");
}
void show(Stu *stu, int *count)
{
    Stu cop;
    int i;
    float average;
    scanf("%s", &cop.ID);
    if (find(stu, cop, count) == -1)
    {
        printf("Students do not exist\n");
    }
    else
    {
        i = find(stu, cop, count);
        printf("Student ID:%s\n", stu[i].ID);
        printf("Name:%s\n", stu[i].name);
        average = (float) (stu[i].math + stu[i].English + stu[i].computer) / 3;
        printf("Average Score:%.1f\n", average);
    }
}