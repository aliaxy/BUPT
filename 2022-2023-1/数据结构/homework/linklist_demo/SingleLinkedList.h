/*******************************************
 *                                         *
 * 文件名: SingleLinkedList.h               *
 *                                         *
 * 内  容: 单链表相关操作列表                  *
 *                                         *
 *******************************************/

#ifndef LINKLIST_DEMO_SINGLELINKEDLIST_H
#define LINKLIST_DEMO_SINGLELINKEDLIST_H

#include "common.h"

/* 单链表类型定义 */
typedef int ElemType;

/* 单链表结构体 */
typedef struct LNode {
  ElemType data;
  struct LNode *next;
} LNode,
    *LinkList;//定义了两个类型，LNode为结构体类型，LinkList为指向单链表结点的指针类型

/* 单链表（带头结点）函数列表 */
Status InitList_L(LinkList &L);
/*━━━━━━━━━━┓
┃(01)初始化单链表L。 ┃
┗━━━━━━━━━━*/

Status ClearList_L(LinkList L);
/*━━━━━━━━━━━━━━━┓
┃(02)置空单链表L，头结点保留。 ┃
┗━━━━━━━━━━━━━━━*/

void DestroyList_L(LinkList &L);
/*━━━━━━━━━━━━━━━━━━━┓
┃(03)销毁单链表L，连同头结点一起销毁。 ┃
┗━━━━━━━━━━━━━━━━━━━*/

Status ListEmpty_L(LinkList L);
/*━━━━━━━━━━━━━━━┓
┃(04)判断单链表L是否为空。     ┃
┗━━━━━━━━━━━━━━━*/

int ListLength_L(LinkList L);
/*━━━━━━━━━━━━┓
┃(05)返回单链表L元素个数 ┃
┗━━━━━━━━━━━━*/

Status GetElem_L(LinkList L, int i, ElemType &e);
/*━━━━━━━━━━━━━━━━━━━┓
┃(06)用e接收单链表L中第i个元素┃
┗━━━━━━━━━━━━━━━━━━━*/

LNode *LocateElem_L(LinkList L, ElemType e);
/*━━━━━━━━━━━━━━━━━━━━━━ ┓
┃(07)返回单链表L中第一个与e满相等的元素结点指针。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━*/

Status ListInsert_L(LinkList L, int i, ElemType e);
/*━━━━━━━━━━━━━━━━ ┓
┃(08)在单链表L第i个位置之前插入e。┃
┗━━━━━━━━━━━━━━━━*/

Status ListDelete_L(LinkList L, int i, ElemType &e);
/*━━━━━━━━━━━━━━━━━━━━━┓
┃(09)删除单链表L第i个位置的值，并用e接收。 ┃
┗━━━━━━━━━━━━━━━━━━━━━*/

Status ListTraverse_L(LinkList L, void(Visit)(ElemType));
/*━━━━━━━━━━━━━━┓
┃(10)用Visit函数访问单链表L。┃
┗━━━━━━━━━━━━━━*/

Status CreateList_HL(LinkList &L, int n);
/*━━━━━━━━━━━━━━━━━━━━━━ ━━┓
┃(11)输入n个数据采用头插法建立单链表L(逆序输入)。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━*/

Status CreateList_TL(LinkList &L, int n);
/*━━━━━━━━━━━━━━━━━━━━━━━━ ┓
┃(12)输入n个数据采用尾插法建立单链表L(顺序输入)。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━*/

Status Merge(LinkList A, LinkList B, LinkList C);
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ ┓
┃(13)A、B是两个已排序递增的单链表A和B，将A、B合并成一个单链表C，
┃且不改变排序性，要不使用AB中的结点，而不创建新结点，合并后A/B的长度为0。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

Status Reverse(LinkList C);
/*━━━━━━━━━ ┓
┃(14)将单链表C逆置
┗━━━━━━━━━*/

#endif//LINKLIST_DEMO_SINGLELINKEDLIST_H
