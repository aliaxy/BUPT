/*
10-6 实验7_14_二分查找

设计函数 int BinarySearch(int a[],int n,int key);
利用二分查找算法，在升序排列的数组a的前n个元素中查找值为key的数组元素的下标。
如果数组a中存在整数key，则返回下标；否则返回－1。假设数组a中的元素互不相同。

输入与输出要求：

首先输入两个整数n，m，分别代表数组a中元素的个数与需要查找的整数的个数，n（0<n<=2000000）与m(0<m<=100000)。然后分别输入n个整数和m个整数，分别代表存放在数组中的数以及要查找的数。

输出m个整数，分别为要查找的数在数组a中的下标，如果数组a中不存在某个数，则输出-1。数与数之间用空格分开，注意第n个数后没有空格而是换行符。

输入样例：
15
20
-293 -213 -23 0 1 5 11 23 56 67 87 273 999 2132 10000
-23 -99999 0 999 953 67 56 44 33 87 -293 23 11 273 -213 2132 10000 87654 1 5
输出样例：
2 -1 3 12 -1 9 8 -1 -1 10 0 7 6 11 1 13 14 -1 4 5
*/
#include <stdio.h>

int BinarySearch(int a[], int n, int key)
{
    int start = 0, mid, end = n - 1;
    while (start <= end)
    {
        mid = (start + end) / 2;
        if (a[mid] < key)
            start = mid + 1;
        else if (a[mid] > key)
            end = mid - 1;
        else
            return mid;
    }
    return -1;
}

int main(void)
{
    int num[2000000]; //这个数组比较大，如果在你的电脑中无法分配这么大的内存，请改小后测试。
    int n, m, i;
    int key;

    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++)
        scanf("%d", &num[i]);

    for (i = 0; i < m; i++)
    {
        scanf("%d", &key);
        printf("%d", BinarySearch(num, n, key));
        if (i != m - 1)
            printf(" ");
        else
            printf("\n");
    }
    return 0 ;
}