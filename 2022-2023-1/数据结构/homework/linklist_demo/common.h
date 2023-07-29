//
// Created by wzl on 2022/3/8.
//
#ifndef SQLIST_DEMO_COMMON_H
#define SQLIST_DEMO_COMMON_H

#include <iostream>
/* 函数结果状态代码 */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAXSIZE 20 /* 线性表存储空间的初始分配量 */

typedef int Status;	 	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

//摁Enter键继续
#define PressEnter\
 {\
	fflush(stdin);\
	printf("Press Enter...");\
	getchar();\
	fflush(stdin);\
 }

#endif //SQLIST_DEMO_COMMON_H
