//
// Created by wzl on 2022/4/20.
//

#include "bitree.h"
#include <stack>
#include <queue>

Status InitBiTree(BiTree &T) { /* 操作结果: 构造空二叉树T */
  T = NULL;
  return OK;
}

void DestroyBiTree(
    BiTree &T) { /* 初始条件: 二叉树T存在。操作结果: 销毁线索二叉树T */
  if (T) /* 非空树 */
  {
    if (T->lchild)              /* 有左孩子 */
      DestroyBiTree(T->lchild); /* 销毁左孩子子树 */
    if (T->rchild)              /* 有右孩子 */
      DestroyBiTree(T->rchild); /* 销毁右孩子子树 */
    free(T);                    /* 释放根结点 */
    T = NULL;                   /* 空指针赋0 */
  }
}

Status CreateBiTree(
    BiTree &
        T) { /* 按先序次序输入二叉树中结点的值，构造二叉链表表示的二叉树T。变量Nil表示空（子）树。*/
  TElemType ch;
  scanf("%c", &ch);
  if (ch == Nil) /* 空 */
    T = NULL;
  else {
    T = (BiTNode *)malloc(sizeof(BiTNode));
    if (!T) exit(OVERFLOW);
    T->data = ch;            /* 生成根结点 */
    CreateBiTree(T->lchild); /* 构造左子树 */
    CreateBiTree(T->rchild); /* 构造右子树 */
  }
  return OK;
}

Status BiTreeEmpty(BiTree T) { /* 初始条件: 二叉树T存在 */
  /* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
  if (T)
    return FALSE;
  else
    return TRUE;
}

int BiTreeDepth(BiTree T) { /* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
  int i = 0, j = 0;
  if (!T) return 0;
  if (T->lchild) i = BiTreeDepth(T->lchild);

  if (T->rchild) j = BiTreeDepth(T->rchild);

  return i > j ? i + 1 : j + 1;
}

int CountLeaf(BiTree bt)  //求叶子结点数量
{
  if (bt == nullptr) {
    return 0;
  }
  if (bt->lchild == nullptr && bt->rchild == nullptr) {
    return 1;
  }
  return CountLeaf(bt->lchild) + CountLeaf(bt->rchild);
}

void PreOrderTraverse(
    BiTree T,
    void (*Visit)(
        TElemType)) { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数。 */
  /* 操作结果: 先序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
  if (T) /* T不空 */
  {
    Visit(T->data);                     /* 先访问根结点 */
    PreOrderTraverse(T->lchild, Visit); /* 再先序遍历左子树 */
    PreOrderTraverse(T->rchild, Visit); /* 最后先序遍历右子树 */
  }
}

void InOrderTraverse(
    BiTree T,
    void (*Visit)(
        TElemType)) { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
  /* 操作结果: 中序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
  if (T) {
    InOrderTraverse(T->lchild, Visit);
    Visit(T->data);
    InOrderTraverse(T->rchild, Visit);
  }
}

void PostOrderTraverse(
    BiTree T,
    void (*Visit)(
        TElemType)) { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
  /* 操作结果: 后序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
  if (T) {
    PostOrderTraverse(T->lchild, Visit);
    PostOrderTraverse(T->rchild, Visit);
    Visit(T->data);
  }
}

void LevelOrderTraverse(
    BiTree T,
    void (*Visit)(
        TElemType)) { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
  /* 操作结果: 层次遍历T,对每个结点调用函数Visit一次且仅一次 */
  if (T == nullptr) {
    return;
  }
  std::queue<BiTNode *> qu;
  qu.push(T);
  while (!qu.empty()) {
    BiTree cur = qu.front();
    qu.pop();
    Visit(cur->data);
    if (cur->lchild) {
      qu.push(cur->lchild);
    }
    if (cur->rchild) {
      qu.push(cur->rchild);
    }
  }
}

void PreOrderTraverseNoRecursive(
    BiTree T,
    void (*Visit)(
        TElemType)) { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
  /* 操作结果: 先序非递归遍历T,对每个结点调用函数Visit一次且仅一次 */
  std::stack<BiTNode *> stk;
  BiTNode *p = T;
  while (p || !stk.empty()) {
    if (p) {
      Visit(p->data);
      stk.push(p);
      p = p->lchild;
    } else {
      p = stk.top();
      stk.pop();
      p = p->rchild;
    }
  }
}

void InOrderTraverseNoRecursive(
    BiTree T,
    void (*Visit)(
        TElemType)) { /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
  /* 操作结果: 中序非递归遍历T,对每个结点调用函数Visit一次且仅一次 */
  std::stack<BiTNode *> stk;
  BiTNode *p = T;
  while (p || !stk.empty()) {
    if (p) {
      stk.push(p);
      p = p->lchild;
    } else {
      p = stk.top();
      stk.pop();
      Visit(p->data);
      p = p->rchild;
    }
  }
}

void Exchange(BiTree T)  //交换所有结点的左右子树
{
  if (T) {
    Exchange(T->lchild);
    Exchange((T->rchild));
    BiTree tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;
  }
}

int CountDesc(BiTree T) {
  if (T == nullptr) {
    return 0;
  }
  if (T->lchild) {
    T->DescNum++;
  }
  if (T->rchild) {
    T->DescNum++;
  }
  T->DescNum += CountDesc(T->lchild) + CountDesc(T->rchild);
  return T->DescNum;
}
