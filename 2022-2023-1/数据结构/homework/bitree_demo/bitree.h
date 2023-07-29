//
// Created by wzl on 2022/4/20.
//

#ifndef BITREE_DEMO_BITREE_H
#define BITREE_DEMO_BITREE_H

#include "common.h"

typedef char TElemType;

/* 二叉树的二叉链表存储表示 */
typedef struct BiTNode {
  TElemType data;
  int DescNum;                     /* 子孙数目 */
  struct BiTNode *lchild, *rchild; /* 左右孩子指针 */
} BiTNode, *BiTree;

Status InitBiTree(BiTree &T);

void DestroyBiTree(BiTree &T);

/* 按先序次序输入二叉树中结点的值，构造二叉链表表示的二叉树T。变量Nil表示空（子）树。*/
Status CreateBiTree(BiTree &T);

/* 初始条件: 二叉树T存在 */
/* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
Status BiTreeEmpty(BiTree T);

/* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
int BiTreeDepth(BiTree T);

//求叶子结点数量
int CountLeaf(BiTree bt);

//交换所有结点的左右子树
void Exchange(BiTree T);

// 二叉树的每个结点的子孙数目并存入其DescNum域

/* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数。 */
/* 操作结果: 先序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
void PreOrderTraverse(BiTree T, void (*Visit)(TElemType));

/* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
/* 操作结果: 中序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
void InOrderTraverse(BiTree T, void (*Visit)(TElemType));

/* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
/* 操作结果: 后序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
void PostOrderTraverse(BiTree T, void (*Visit)(TElemType));

/* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
/* 操作结果: 层次遍历T,对每个结点调用函数Visit一次且仅一次 */
void LevelOrderTraverse(BiTree T, void (*Visit)(TElemType));

/* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
/* 操作结果: 先序非递归遍历T,对每个结点调用函数Visit一次且仅一次 */
void PreOrderTraverseNoRecursive(BiTree T, void (*Visit)(TElemType));

/* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
/* 操作结果: 中序非递归遍历T,对每个结点调用函数Visit一次且仅一次 */
void InOrderTraverseNoRecursive(BiTree T, void (*Visit)(TElemType));

#endif  // BITREE_DEMO_BITREE_H
