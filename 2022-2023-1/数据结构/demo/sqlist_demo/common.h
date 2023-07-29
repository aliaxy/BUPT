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

#define LIST_INIT_SIZE 100 /* 线性表存储空间的初始分配量 */
#define LIST_INCREMENT 20 /* 线性表存储空间每次扩展的增量 */

typedef int Status;	 	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

#endif //SQLIST_DEMO_COMMON_H
