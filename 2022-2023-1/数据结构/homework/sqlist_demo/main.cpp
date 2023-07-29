#include "common.h"

typedef int ElemType;
typedef struct {
  ElemType *elem; /* 存储空间基址 */
  int length;     /* 当前长度 */
  int listsize;
} SqList;

/* ListTraverse()调用的函数(类型要一致) */
void visit(ElemType *c) {
  std::cout << *c << " ";
}

/* 初始化顺序表 */
Status InitList(SqList &L) {
  /* 操作结果：构造一个空的顺序线性表 */
  L.elem = (ElemType *) malloc(LIST_INIT_SIZE * sizeof(ElemType));
  if (!L.elem) {
    exit(OVERFLOW); /* 存储分配失败 */
  }
  L.length = 0;                /* 空表长度为0 */
  L.listsize = LIST_INIT_SIZE; /* 初始存储容量*/
  return OK;
}

Status DestroyList(SqList &L) {
  /* 初始条件：顺序线性表L已存在。操作结果：销毁顺序线性表L */
  delete L.elem;
  L.elem = nullptr;
  L.length = 0;
  L.listsize = 0;
  return OK;
}

Status ClearList(SqList &L) {
  /* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
  L.length = 0;
  return OK;
}

Status ListEmpty(SqList L) {
  /* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
  if (L.length == 0) return TRUE;
  else
    return FALSE;
}

int ListLength(SqList L) {
  /* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
  return L.length;
}

Status GetElem(SqList L, int i, ElemType &e) {
  /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
  /* 操作结果：用e返回L中第i个数据元素的值 */
  if (i < 1 || i > L.length) exit(ERROR);
  e = L.elem[i - 1];
  return OK;
}

int LocateElem(SqList L, ElemType e) {
  /* 初始条件：顺序线性表L已存在*/
  /* 操作结果：返回L中第1个与e相等的数据元素的位序。 */
  /*         若这样的数据元素不存在，则返回值为0。*/
  if (L.length == 0) {
    exit(ERROR);
  }

  for (int i = 0; i < L.length; i++) {
    if (L.elem[i] == e) {
      return i + 1;
    }
  }

  return 0;
}

Status PriorElem(SqList L, ElemType cur_e, ElemType &pre_e) {
  /* 初始条件：顺序线性表L已存在 */
  /* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
  /*         否则操作失败，pre_e无定义 */
  int i = 2;
  ElemType *p = L.elem + 1;
  while (i <= L.length && *p != cur_e) {
    p++;
    i++;
  }
  if (i > L.length) return INFEASIBLE;
  else {
    pre_e = *--p;
    return OK;
  }
}

Status NextElem(SqList L, ElemType cur_e, ElemType &next_e) {
  /* 初始条件：顺序线性表L已存在 */
  /* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
  /*           否则操作失败，next_e无定义 */
  int i = 1;
  ElemType *p = L.elem;
  while (i < L.length && *p != cur_e) {
    i++;
    p++;
  }
  if (i == L.length) return INFEASIBLE;
  else {
    next_e = *++p;
    return OK;
  }
}

/* 插入元素 */
Status ListInsert(SqList &L, int i, ElemType e) {
  /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)+1 */
  /* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
  ElemType *newbase, *q, *p;
  if (i < 1 || i > L.length + 1) /* i值不合法 */
    return ERROR;
  if (L.length >= L.listsize) { /* 当前存储空间已满,增加分配 */
    newbase = (ElemType *) realloc(
        L.elem, (L.listsize + LIST_INCREMENT) * sizeof(LIST_INCREMENT));
    if (!newbase) exit(OVERFLOW); /* 存储分配失败 */
    L.elem = newbase;
    L.listsize += LIST_INCREMENT;
  }
  q = L.elem + i - 1;                          /* q为插入位置 */
  for (p = L.elem + L.length - 1; p >= q; --p) /* 插入位置及之后的元素右移 */
    *(p + 1) = *p;
  *q = e;     /* 插入e */
  L.length++; /* 表长增1 */
  return OK;
}

/* 删除元素 */
Status ListDelete(SqList &L, int i, ElemType &e) {
  /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
  /* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
  if (L.length < 1 || i > ListLength(L)) {
    return ERROR;
  }

  e = L.elem[i - 1];
  for (int j = i; j < L.length; j++) {
    L.elem[j - 1] = L.elem[j];
  }
  L.length--;

  return OK;
}

Status ListTraverse(SqList L, void (*vi)(ElemType *)) {
  /* 初始条件：顺序线性表L已存在 */
  /* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
  /*          vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
  ElemType *p;
  int i;
  p = L.elem;
  for (i = 1; i <= L.length; i++) vi(p++);
  std::cout << std::endl;
  return OK;
}

Status Part(SqList &L) {
  /* 初始条件：顺序线性表L已存在 */
  /* 操作结果：将顺序表以a1为界进行划分，即比a1小的移动到a1前面，比a1大的移动到a1后面 */
  int i, j;
  ElemType x, y;
  x = L.elem[0];
  for (i = 1; i < L.length; i++) {
    if (x > L.elem[i]) {
      y = L.elem[i];
      for (j = i; j > 0; j--) {
        L.elem[j] = L.elem[j - 1];
      }
      L.elem[0] = y;
    }
  }

  return OK;
}

Status Merge(SqList A, SqList B, SqList &C) {
  /* 初始条件：顺序线性表A/B/C已存在，AB元素均从小到大 */
  /* 操作结果：将AB中的元素合并插入到C中，并保持从小到大有序 */
  ElemType *pA = A.elem;
  ElemType *pB = B.elem;
  ElemType *pC;

  C.listsize = C.length = A.length + B.length;
  pC = C.elem = (ElemType *) malloc(C.listsize * sizeof(ElemType));
  if (C.elem == nullptr) {
    exit(OVERFLOW);
  }
  ElemType *pA_last = A.elem + A.length - 1;
  ElemType *pB_last = B.elem + B.length - 1;

  while (pA <= pA_last && pB <= pB_last) {
    if (*pA <= *pB) {
      *pC++ = *pA++;
    } else {
      *pC++ = *pB++;
    }
  }
  while (pA <= pA_last) {
    *pC++ = *pA++;
  }
  while (pB <= pB_last) {
    *pC++ = *pB++;
  }

  return OK;
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
  SqList L;
  ElemType e, e0;
  Status res;
  int i, j;

  InitList(L);
  std::cout << "初始化L后：L.elem=" << L.elem << ", L.length=" << L.length
            << std::endl;

  for (i = 1; i <= 5; i++) {
    ListInsert(L, 1, i);
  }
  std::cout << "在L的表头依次插入1〜5后：";
  ListTraverse(L, visit); /* 依次对元素调用visit()，输出元素的值 */
  std::cout << "L.elem=" << L.elem << ", L.length=" << L.length << std::endl;
  res = ListEmpty(L);
  std::cout << "L是否空：res=" << res << " (1:是 0:否)" << std::endl
            << std::endl;

  ClearList(L);
  std::cout << "清空L后：L.elem=" << L.elem << ", L.length=" << L.length
            << std::endl;
  res = ListEmpty(L);
  std::cout << "L是否空：res=" << res << " (1:是 0:否)" << std::endl
            << std::endl;

  for (i = 1; i <= 10; i++) {
    ListInsert(L, i, i);
  }
  std::cout << "在L的表尾依次插入1〜10后：";
  ListTraverse(L, visit); /* 依次对元素调用visit()，输出元素的值 */
  std::cout << "L.elem=" << L.elem << ", L.length=" << L.length << std::endl
            << std::endl;

  ListInsert(L, 1, 0);
  std::cout << "在L的表头插入0后：";
  ListTraverse(L, visit); /* 依次对元素调用visit()，输出元素的值 */
  std::cout << "L.elem=" << L.elem << ", L.length=" << L.length << "(改变)"
            << std::endl
            << std::endl;

  GetElem(L, 5, e);
  std::cout << "第5个元素的值为：" << e << std::endl << std::endl;

  i = 8;
  j = LocateElem(L, i); /* 查找值为i的元素 */
  if (j > 0) std::cout << "第" << j << "个元素的值为" << i << std::endl;
  else
    std::cout << "没有值为" << i << "的元素" << std::endl;

  for (i = 1; i <= 2; i++) /* 测试求头两个数据的前驱 */
  {
    GetElem(L, i, e0);       /* 把第j个数据赋给e0 */
    j = PriorElem(L, e0, e); /* 求e0的前驱 */
    if (j == INFEASIBLE) std::cout << "元素" << e0 << "无前驱" << std::endl;
    else
      std::cout << "元素" << e0 << "的前驱为：" << e << std::endl;
  }
  std::cout << std::endl;

  i = 8;
  res = ListDelete(L, i, e); /* 删除第i个数据 */
  if (res == ERROR) std::cout << "删除第" << res << "个数据失败" << std::endl;
  else
    std::cout << "删除的元素值为" << e << std::endl;

  std::cout << "依次输出L的元素：";
  ListTraverse(L, visit); /* 依次对元素调用visit()，输出元素的值 */
  std::cout << std::endl;

  ClearList(L);              /*再次清空*/
  for (i = 1; i <= 7; i++) { /* 在L的表头依次插入2、4、6、8、10、12、14*/
    ListInsert(L, 1, 2 * i);
  }
  ListInsert(L, 1, 9); /* 在L的表头插入9*/
  std::cout << "划分前L的元素：";
  ListTraverse(
      L,
      visit); /* 依次对元素调用visit()，输出元素的值 为 9、14、12、10、8、6、4、2*/
  Part(L);    /*调用划分函数*/
  std::cout << "划分后L的元素：";
  ListTraverse(
      L,
      visit); /* 依次对元素调用visit()，输出元素的值 为 9、14、12、10、8、6、4、2*/
  DestroyList(L);
  std::cout << "销毁L后：L.elem=" << L.elem << " L.length=" << L.length
            << std::endl;

  std::cout << std::endl << "******************" << std::endl;
  SqList A, B, C; /*定义三个顺序表*/
  /*初始化三个顺序表,并向A、B插入数据*/
  InitList(A);
  InitList(B);
  InitList(C);
  ListInsert(A, 1, 2);
  ListInsert(A, 2, 4);
  ListInsert(A, 3, 5);
  ListInsert(A, 4, 10);
  ListInsert(A, 5, 15);
  ListInsert(B, 1, 1);
  ListInsert(B, 2, 6);
  ListInsert(B, 3, 8);
  ListInsert(B, 4, 12);
  std::cout << "顺序表A的元素：";
  ListTraverse(
      A, visit); /* 依次对元素调用visit()，输出元素的值 为 2、4、5、10、15*/
  std::cout << "顺序表B的元素：";
  ListTraverse(B,
               visit); /* 依次对元素调用visit()，输出元素的值 为 1、6、8、12*/

  Merge(A, B, C);
  std::cout << "合并后顺序表C的元素：";
  ListTraverse(C,
               visit); /* 依次对元素调用visit()，输出元素的值 为 1、6、8、12*/

  /*销毁三个顺序表*/
  DestroyList(A);
  DestroyList(B);
  DestroyList(C);

  return 0;
}
