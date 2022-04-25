/*
4-4 实验3_4_质数统计

现有若干行正整数，请你写一段程序分别统计每一行中有多少个质数。

输入格式:
第一行为一个整数n(0<n<=10)，代表测试用例行数。后边是n行，每行为若干个用空格分隔的正整数。这些正整数的最后是-1，表示此行结束。

输出格式:
为n行，每行一个整数，对应于输入的每一行中质数的个数。

测试用例保证输入合法，且所有整数可以用int存储

输入样例:
2
37 54 18 92 39 45 8 84 75 15 33 83 85 54 81 33 89 -1
17 19 60 77 2 92 38 63 92 69 91 94 11 -1
输出样例:
3
4
*/
#include <stdio.h>

int main(void)
{
    int num, shu_ru;
    int i = 1, j = 1, count1 = 0, count2 = 0;
    scanf("%d", &num);

    while (i <= num)
    {
        scanf("%d", &shu_ru);
        while (shu_ru != -1)
        {
            while (j <= shu_ru)
            {
                if (shu_ru % j == 0)
                    count1++;
                j++;
            }
            if (count1 == 2)
                count2++;
            scanf("%d", &shu_ru);
            j = 1;
            count1 = 0;
        }
        printf("%d\n", count2);
        i++;
        j = 1;
        count1 = 0;
        count2 = 0;
    }

    return 0;
}