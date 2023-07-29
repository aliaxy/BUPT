#include "bitree.h"
#include <iostream>

void visitT(TElemType e) // 测试函数，打印整型
{
  std::cout << e << " ";
}

int main() {
  BiTree T;
  InitBiTree(T);
  printf("请先序输入二叉树(如:ABD0G000CE00F00)\n");

  CreateBiTree(T);

  int depth = BiTreeDepth(T);
  printf("二叉树的深度为：%d\n", depth); // 输出深度

  int countleaf = CountLeaf(T); // 计算叶子结点的数目
  printf("叶子结点的数目为：%d\n", countleaf);

  printf("先序递归遍历二叉树:\n");
  PreOrderTraverse(T, visitT);
  printf("\n");

  printf("中序递归遍历二叉树:\n");
  InOrderTraverse(T, visitT);
  printf("\n");

  printf("后序递归遍历二叉树:\n");
  PostOrderTraverse(T, visitT);
  printf("\n");

  printf("层次遍历二叉树:\n");
  LevelOrderTraverse(T, visitT);
  printf("\n");

  printf("先序非递归遍历二叉树:\n");
  PreOrderTraverseNoRecursive(T, visitT);
  printf("\n");

  printf("中序非递归遍历二叉树:\n");
  InOrderTraverseNoRecursive(T, visitT);
  printf("\n");

  printf("--------------------------\n");
  printf("左、右子树进行交换\n");
  printf("--------------------------\n");
  Exchange(T);

  printf("交换后先序递归遍历二叉树:\n");
  PreOrderTraverse(T, visitT);
  printf("\n");

  printf("交换后中序递归遍历二叉树:\n");
  InOrderTraverse(T, visitT);
  printf("\n");

  printf("交换后后序递归遍历二叉树:\n");
  PostOrderTraverse(T, visitT);
  printf("\n");

  DestroyBiTree(T);
  PressEnter;

  return 0;
}
