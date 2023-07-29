//
// Created by wzl on 2022/4/20.
//

#ifndef BITREE_DEMO_COMMON_H
#define BITREE_DEMO_COMMON_H

#include <iostream>
/* 函数结果状态代码 */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define Nil '0' /* 字符型以0为空 */

typedef int Status;	 	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

//摁Enter键继续
#define PressEnter\
 {\
	fflush(stdin);\
	printf("Press Enter...");\
	getchar();\
	fflush(stdin);\
 }

#endif //BITREE_DEMO_COMMON_H
