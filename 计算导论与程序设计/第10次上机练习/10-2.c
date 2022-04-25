/*
10-2 实验7_10_发子弹

在某次实弹射击训练中，班长让战士们围成一圈发子弹。首先，班长给每个人发若干发子弹，然后按如下方法将每个战士手中的子弹进行调整：
所有的战士检查自己手中的子弹数，如果子弹数为奇数，则向班长再要一颗。
然后每个战士再同时将自己手中的子弹分一半给下一个战士（最后一个战士将手中的子弹分一半给第1个战士)。
这种调整会一直进行下去，直到所有战士手中的子弹数相等为止。现请你写一个函数模拟这个调整的过程。

输入样例：
10
10 2 8 22 16 4 10 6 14 20
1
输出样例：
15 6 5 15 19 10 7 8 10 17
*/
#include <stdio.h>

#define LEN 100

void distribute(int *bullets, int size, int number)
{
    int a[LEN], i, j, flag = 0;
    for (i = 0; i < number && flag - size; i++)
    {
        for (j = 0; j < size; j++)
            a[j] = bullets[j] + bullets[j] % 2;

        for (j = 0; j < size; j++)
            bullets[j + 1] = (a[j] + a[j + 1]) / 2;
        bullets[0] = (a[0] + a[size - 1]) / 2;
        for (j = 0; j < size && flag; j++)
            if (bullets[0] == bullets[j])
                flag++;
    }
}

int main(void)
{
    int bullets[LEN];
    int n, m, i;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &bullets[i]);
    }
    scanf("%d", &m);
    distribute(bullets, n, m);
    for (i = 0; i < n - 1; i++)
    {
        printf("%d ", bullets[i]);
    }
    printf("%d\n", bullets[i]);

    return 0;
}