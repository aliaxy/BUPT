//
// Created by wzl on 2022/3/15.
//

#include "SingleLinkedList.h"//**单链表**//

Status InitList_L(LinkList &L) {
  L = new LNode; //创建头结点，然后把头结点的地址存放到L中
  L->next = NULL;//头结点的next域为NULL
  return OK;
}

Status ClearList_L(LinkList L) {
  //清空链表，保留头结点
  LNode *p, *next;
  if (!L) return ERROR;

  p = L->next;//p指向第一个结点
  while (p) {
    next = p->next;
    delete p;//释放p指向的结点
    p = next;//p指向下一结点
  }

  L->next = NULL;//头结点的next域设置为NULL
  return OK;
}

void DestroyList_L(LinkList &L) {
  //销毁所有结点
  LNode *p, *next;
  p = L;//p指向头结点

  while (p) {//从头结点开始销毁
    next = p->next;
    delete p;
    p = next;//p指向下一结点
  }
  L = nullptr;
}

Status ListEmpty_L(LinkList L) {
  if (L != NULL && L->next == NULL)//链表存在且只有头结点
    return TRUE;
  else
    return FALSE;
}

int ListLength_L(LinkList L) {
  LNode *p;
  int i = 0;//计数器初始化为0

  if (L) {
    p = L->next;//p指向首元结点
    while (p) {
      i++;
      p = p->next;
    }
  }
  return i;
}

Status GetElem_L(LinkList L, int i, ElemType &e) {
  //在带头结点的单链表L中用e返回序号为i的元素的值
  LNode *p = L->next;
  int j = 1;

  while (p && j < i)//p不为空且还未到达i处
  {
    j++;
    p = p->next;
  }

  if (!p || j > i)//第i个元素不存在
    return ERROR;

  e = p->data;

  return OK;
}

LNode *LocateElem_L(LinkList L, ElemType e) {

  LNode *p = L->next;//p指向首元结点

  while (p && p->data != e) {
    p = p->next;
  }

  return p;
}

Status ListInsert_L(LinkList L, int i, ElemType e) {
  LinkList p, s;
  int j;

  p = L;
  j = 0;

  while (p && j < i - 1) {//寻找第i-1个结点
    p = p->next;
    ++j;
  }

  if (!p || j > i - 1) return ERROR;

  s = new LNode;
  s->data = e;
  s->next = p->next;
  p->next = s;

  return OK;
}

Status ListDelete_L(LinkList L, int i, ElemType &e) {
  LNode *p = L;
  for (int j = 0; j < i - 1; j++) {
    p = p->next;
  }

  LNode *q = p->next;
  p->next = q->next;
  delete q;

  return OK;
}

Status ListTraverse_L(LinkList L, void(Visit)(ElemType)) {
  LNode *p;

  if (!L) return ERROR;
  else
    p = L->next;

  while (p) {
    Visit(p->data);
    p = p->next;
  }

  return OK;
}

Status CreateList_HL(LinkList &L, int n) {
  //前插法创建单链表，逆位序输入n个元素的值，建立带头结点的单链表L
  int i;
  LNode *p;

  L = new LNode;//建立头结点
  L->next = NULL;

  for (i = 1; i <= n; ++i) {
    p = new LNode;
    std::cin >> p->data;//录入数据
    p->next = L->next;
    L->next = p;
  }
  return OK;
}

Status CreateList_TL(LinkList &L, int n) {
  //尾插法创建单链表，正序输入n个元素的值，建立带头结点的单链表L
  L = new LNode;//建立头结点
  L->next = NULL;

  LNode *p, *pLast;
  pLast = L;

  for (int i = 1; i <= n; i++) {
    p = new LNode;
    std::cin >> p->data;
    p->next = nullptr;
    pLast->next = p;
    pLast = p;
  }

  return OK;
}

Status Merge(LinkList A, LinkList B, LinkList C) {
  LNode *p, *q, *s;
  p = A->next, q = B->next;
  s = C;
  while (p && q) {
    s->next = new LNode;
    if (p->data <= q->data) {
      s->next->data = p->data;
      p = p->next;
    } else {
      s->next->data = q->data;
      q = q->next;
    }
    s->next->next = nullptr;
    s = s->next;
  }
  if (p == nullptr) {
    p = q;
  }
  while (p) {
    s->next = new LNode;
    s->next->data = p->data;
    p = p->next;
    s->next->next = nullptr;
    s = s->next;
  }
  return OK;
}

Status Reverse(LinkList C) {
  LNode *p, *s;
  p = C->next;
  C->next = nullptr;

  while (p) {
    s = p;
    p = p->next;
    s->next = C->next;
    C->next = s;
  }

  return OK;
}