/*
7-5 实验1_5_数据类型

C语言为程序员提供了丰富的数据类型，常用到的数据类型有字符型(char型)、短整型(short型)、整型(int
型)、长整型(long型)、拓展长整型(longlong型)、单精度浮点型(float型)、双精度浮点型(double型)。
你的任务是在主程序中分别定义上述的所有类型变量，变量名按照上述顺序为a、b、c、d、e、f、g。按照上述顺序
读入这些不同类型的数据，并按照原顺序输出。最后再输出这些变量在你所用的操作系统中所占的字节数，这里
要用到计算变量占用内存字节数的运算符sizeof()。

输入格式:
为7行，每行对应一种类型数据的输入。

输出格式:
也是7行，每行对应一种类型的数据及其在内存在占用的字节数。如“The ‘int’ variable
is 2000000000, it takes 4 byte.”。

输入样例:
X
1234
2000000000
2000000000
500000000000000
1.2345
9.87654321
输出样例:
The 'char' variable is X, it takes 1 byte.
The 'short' variable is 1234, it takes 2 bytes.
The 'int' variable is 2000000000, it takes 4 bytes.
The 'long' variable is 2000000000, it takes 8 bytes.
The 'long long' variable is 500000000000000, it takes 8 bytes.
The 'float' variable is 1.234500, it takes 4 bytes.
The 'double' variable is 9.876543, it takes 8 bytes.
*/
#include <stdio.h>

int main(void)
{
    char a;
    short b;
    int c;
    long d;
    long long e;
    float f;
    double g;

    scanf("%c %hd %d %ld %lld %f %lf", &a, &b, &c, &d, &e, &f, &g);

    printf("The 'char' variable is %c, it takes %u byte.\n", a, sizeof(a));
    printf("The 'short' variable is %hd, it takes %u bytes.\n", b, sizeof(b));
    printf("The 'int' variable is %d, it takes %u bytes.\n", c, sizeof(c));
    printf("The 'long' variable is %ld, it takes %u bytes.\n", d, sizeof(d));
    printf("The 'long long' variable is %lld, it takes %u bytes.\n", e,
           sizeof(e));
    printf("The 'float' variable is %f, it takes %u bytes.\n", f, sizeof(f));
    printf("The 'double' variable is %lf, it takes %u bytes.", g, sizeof(g));

    return 0;
}