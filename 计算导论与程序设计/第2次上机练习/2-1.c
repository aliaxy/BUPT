/*
2-1 三对三篮球赛

第4条：得分

4.1. 在圆弧线以内投篮命中得 1 分。

4.2. 在圆弧线以外投篮命中得 2 分

4.3. 罚篮命中得 1 分。

第5条：比赛时间/优胜者

5.1 一节 10
分钟（这个可以称为常规时间）。在死球状态下和罚球时应停表。再次开球时，当球权方与防守队一名球员完成一次传递球后（即一旦进攻队持球），计时器应继续计时。

5.2. 但是，在规定的比赛时间内（即在常规时间内），率先取得 21
分或以上的队伍获胜。

5.3.
如果在规定比赛时间（即在常规时间内）两队打平，则应进行加时赛。加时赛中率先取得 2
分的队伍获胜。

输入格式:
为用空格分隔的两个整数，依次代表A队得分和B队得分。测试用例保证合法。

输出格式:
上述得分为常规时间结束（包括先得21分及以上直接获胜的情况）时的比分，如果A队获胜，则输出A
win；如果B队获胜，则输出B win；如果两队打平，需要进行加时赛，则输出no
result；如果出现不可能的比分（比如 29 30），则输出error。

输入样例:
11 17
输出样例:
B win
*/
#include <stdio.h>

int main(void)
{
    int sc0, sc1;

    scanf("%d %d", &sc0, &sc1);

    if ((sc0 >= 21 && sc1 >= 21) || sc0 > 22 || sc1 > 22)
        printf("error");
    else if (sc0 > sc1)
        printf("A win");
    else if (sc0 < sc1)
        printf("B win");
    else
        printf("no result");

    return 0;
}