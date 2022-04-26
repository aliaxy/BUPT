## 过滤注释

C语言的注释分为两种，第一种：在一行源代码中“//”后的内容为注释内容。第二种:“/\*”与“\*/”之间的内容为注释内容。第三种：程序中只出现了“/\*”，没有“\*/”与之对应，那么将“/\*”后的全部内容都要过滤掉。注意，只要是注释内容，那么注释内容中的字符应该全部忽略，即不起任何的作用。例如“/\*”与“\*/”之间如果再有“//”，那么“//”不应起作用；如果“//”再有“/\*”，那么“/\*”也不应起作用。
你的任务是先打开一个名字为dict.dic的文本文件，该文件中前5行每行为1个整数，从第6行开始为5段C语言的源代码。那5个数字代表这5段源代码结束的行数，比如如果第一行的整数为20，第二行的整数为60，则表示从第6行到第20为第一段代码，从第21行到第60为第二段代码。然后根据输入要求将源代码中所有注释过滤掉。
在本过滤注释系统中，你可以忽略源文件中双引号导致“//”、“/\*”、“\*/”失去作用的情况，即只要“//”、“/\*”、“\*/”不是注释内容，在任何情况下都起作用。

#### Input

只可能是1，2，3，4，5之一

#### Output

输入为1则输出第一段代码过滤后的结果，输入为2则输出第二段代码过滤后的结果，依此类推。

#### Sample Input

```
1
```

#### Sample Output

```C
如果第一段代码是这样：
/*
	@Author: BUPT
	@Date: 2010 8 26
*/

#include<stdio.h>

int main()
{
	int a = 10 , b = 2 , c ;
	c = a / b ; //I just want to test '/'
	printf("I love programming C.\n") ; //"printf" is a useful function /*
	printf("I hope you love it too!\n") ;
	/*
	//C is not always hard , if you love it , it will not treat you rough.
	*/
	return 0 ;
}

则输出是这样：


#include<stdio.h>

int main()
{
        int a = 10 , b = 2 , c ;
        c = a / b ;
        printf("I love programming C.\n") ;
        printf("I hope you love it too!\n") ;

        return 0 ;
}
```

#### Solution

```C
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

void GetTarget(FILE *pFile, int *num);
void DeleteComment(FILE *pFile, int start, int end);

int main(void)
{
    FILE *pFile = fopen("dict.dic", "r");
    int num[6] = {5};

    GetTarget(pFile, num);

    int gutter;
    scanf("%d", &gutter);

    DeleteComment(pFile, num[gutter - 1], num[gutter]);

    fclose(pFile);

    return 0;
}

void GetTarget(FILE *pFile, int *num)
{
    rewind(pFile);
    for (int i = 1; i <= 5; i++) fscanf(pFile, "%d", &num[i]);
    fgetc(pFile); // 消除'\n'
}

void DeleteComment(FILE *pFile, int start, int end)
{
    int now = 6;
    bool single = 0, multiple = 0;
    while (now <= start)
    {
        char ch = fgetc(pFile);
        if (ch == '\n') now++;
    }
    char cur = fgetc(pFile), next = fgetc(pFile);
    while (now <= end)
    {
        if (cur == '/' && next == '/' && !multiple)
            single = true;
        else if (cur == '/' && next == '*' && !single)
            multiple = true;
        else if (single && next == '\n')
        {
            single = false;
            cur = next;
            next = fgetc(pFile);
        }
        else if (multiple && cur == '*' && next == '/')
        {
            multiple = false;
            cur = next;
            next = fgetc(pFile);
            if (next == '\n') now++;
            cur = next;
            next = fgetc(pFile);
            if (next == '\n') now++;
        }
        if (!single && !multiple) putchar(cur);
        cur = next;
        next = fgetc(pFile);
        if (next == '\n')
            now++;
        else if (next == EOF)
        {
            if (!single && !multiple) putchar(cur);
            break;
        }
    }
    if (!single && !multiple && next == '\n') putchar(cur);
}
```