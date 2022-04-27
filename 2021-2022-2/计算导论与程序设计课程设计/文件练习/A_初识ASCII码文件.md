## 初识ASCII码文件

已知一个ASCII码文件，文件名为dict.dic，该文件中只包含ASCII码中的字符，即可对应整数0—127。我们将ASCII码中的字符分为4类，第一类为大写字母“A—Z”、第二类为小写字母“a—z”、第三类为数字字符“0—9”、第四类为其他字符“!@#$%^&*” 等等（不属于前三类的字符即为第四类）。 要求： 1.统计出这四类字符在该文件中的数量。 2.统计出该文件的行数、行最大长度、行最小长度。这里要注意，虽然文件的换行符确实为一个字符，ASCII码为10，但在统计行长度时，文件中的换行符并不统计在内。 3.输出具体的大小写字母的统计信息，每行一个字母。 4.处理完成后，关闭文件。 内容提示：在本题对文件的操作内容中，会用到三个新的C语言文件操作函数，一种新的打开文件的方式，如下： 1.FILE *fp=fopen("file.txt","r");//fp即为文件指针，"file.txt"为待打开的文件名，此时应与该程序在一个目录下，"r"为以只读方式打开ASCII码文件。 2.int ch=fgetc(fp);//从fp指向的文件中读取一个字节（字符），存入变量ch内。 3.fclose(fp);//关闭fp指向的文件。

#### Input

只可能1，2，3三个整数之一，其输出分别对应输出中的Task1，Task2，Task3。

#### Output

如果dict.dic文件内容如下： (文件每行都有换行符，且前边无空格)  abcdefghijklmnopqrstuvwxyz  ABCDEFGHIJKLMNOPQRSTUVWXYZ  ~!@#$%^&*()_+`1234567890- =][';/.,<>?":{}| 则三个任务的输出分别如下： （注意：Task1、2、3等也需要输出） Task1: capital: 26 lowercase: 26 digit: 10 others: 36

Task2: line: 3 43 characters in max line. 26 characters in min line.

Task3: CAPITAL: A:1 B:1 C:1 D:1 E:1 F:1 G:1 H:1 I:1 J:1 K:1 L:1 M:1 N:1 O:1 P:1 Q:1 R:1 S:1 T:1 U:1 V:1 W:1 X:1 Y:1 Z:1 LOWERCASE: a:1 b:1 c:1 d:1 e:1 f:1 g:1 h:1 i:1 j:1 k:1 l:1 m:1 n:1 o:1 p:1 q:1 r:1 s:1 t:1 u:1 v:1 w:1 x:1 y:1 z:1

#### Sample Input

```
1
```

#### Sample Output

```
Task1:
capital: 26
lowercase: 26
digit: 10
others: 36
```

#### Solution

```C
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>

void Task_1(FILE *pFile);
void Task_2(FILE *pFile);
void Task_3(FILE *pFile);

int main(void)
{
    FILE *pFile = fopen("dict.dic", "r");

    int f;
    scanf("%d", &f);
    switch (f)
    {
    case 1: Task_1(pFile); break;
    case 2: Task_2(pFile); break;
    case 3: Task_3(pFile); break;
    }

    fclose(pFile);

    return 0;
}

void Task_1(FILE *pFile)
{
    int caps = 0, lower = 0, digit = 0, others = 0;

    rewind(pFile);

    char ch = fgetc(pFile);
    while (!feof(pFile))
    {
        if (isdigit(ch))
            digit++;
        else if (isupper(ch))
            caps++;
        else if (islower(ch))
            lower++;
        else
            others++;
        ch = fgetc(pFile);
    }

    printf("Task1:\n");
    printf("capital: %d\n", caps);
    printf("lowercase: %d\n", lower);
    printf("digit: %d\n", digit);
    printf("others: %d\n", others);
}

void Task_2(FILE *pFile)
{
    int lines = 0, max = 0, min = 0x3f3f3f3f;

    rewind(pFile);

    int num = 0;

    while (!feof(pFile))
    {
        char ch = fgetc(pFile);
        bool flag = 0;
        while (ch != '\n' && !feof(pFile))
        {
            flag = 1;
            num++;
            ch = fgetc(pFile);
        }
        if (flag || ch == '\n')
        {
            lines++;
            max = max > num ? max : num;
            min = min < num ? min : num;
        }
        num = 0;
    }

    printf("Task2:\n");
    printf("line: %d\n", min == 0x3f3f3f3f ? 1 : lines);
    printf("%d characters in max line.\n", max);
    printf("%d characters in min line.\n", min == 0x3f3f3f3f ? 0 : min);
}

void Task_3(FILE *pFile)
{
    int caps[26] = {0}, lower[26] = {0};

    rewind(pFile);

    char ch = fgetc(pFile);
    while (!feof(pFile))
    {
        if (isupper(ch))
            caps[ch - 'A']++;
        else if (islower(ch))
            lower[ch - 'a']++;
        ch = fgetc(pFile);
    }

    printf("Task3:\n");
    printf("CAPITAL:\n");
    for (int i = 0; i < 26; i++)
        printf("%c:%d\n", 'A' + i, caps[i]);
    printf("LOWERCASE:\n");
    for (int i = 0; i < 26; i++)
        printf("%c:%d\n", 'a' + i, lower[i]);
}
```