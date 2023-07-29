#include "SingleLinkedList.h"//**单链表**//

void visit(ElemType e) {//测试函数，打印整型
  std::cout << e << " ";
}

int main() {
  LinkList L;
  int i;
  ElemType e;

  std::cout << "函数 InitList_L 测试...\n";//函数InitList_L测试
  {
    std::cout << "初始化单链表 L ...\n";
    InitList_L(L);
    std::cout << std::endl;
  }
  PressEnter;

  std::cout << "函数 ListEmpty_L 测试...\n";//函数ListEmpty_L测试
  {
    ListEmpty_L(L) ? std::cout << " L 为空！！\n"
                   : std::cout << " L 不为空！\n";
    std::cout << "\n";
  }
  PressEnter;

  std::cout << "函数 ListInsert_L 测试...\n";//函数ListInsert_L测试
  {
    for (i = 1; i <= 6; i++) {
      std::cout << "在 L 第 " << i << " 个位置插入 " << 2 * i << " ...\n";
      ListInsert_L(L, i, 2 * i);
    }
    std::cout << "\n";
  }
  PressEnter;

  std::cout << "函数 ListTraverse_L 测试...\n";//函数ListTraverse_L测试
  {
    std::cout << " L 中的元素为：L = ";
    ListTraverse_L(L, visit);
    std::cout << "\n\n";
  }
  PressEnter;

  std::cout << "函数 ListLength_L 测试...\n";//函数ListLength_L测试
  {
    std::cout << " L 的长度为 " << ListLength_L(L) << " \n";
    std::cout << "\n";
  }
  PressEnter;

  std::cout << "函数 ListDelete_L 测试...\n";//函数ListDelete_L测试
  {
    ListDelete_L(L, 6, e);
    std::cout << "删除 L 中第 6 个元素 " << e << " ...\n";
    std::cout << " L 中的元素为：L = ";
    ListTraverse_L(L, visit);
    std::cout << "\n\n";
  }
  PressEnter;

  std::cout << "函数 GetElem_L 测试...\n";//函数GetElem_L测试
  {
    GetElem_L(L, 4, e);
    std::cout << " L 中第 4 个位置的元素为 " << e << " \n";
    std::cout << "\n";
  }
  PressEnter;

  std::cout << "函数 LocateElem_L 测试...\n";//函数LocateElem_L测试
  {
    LNode *p = LocateElem_L(L, 10);
    std::cout << " L 中第一个元素值等于 \"10\" 的元素为" << p->data << "  \n";
    std::cout << "\n";
  }
  PressEnter;

  std::cout << "函数 ClearList_L 测试...\n";//函数ClearList_L测试
  {
    std::cout << "清空 L 前：";
    ListEmpty_L(L) ? std::cout << " L 为空！！\n"
                   : std::cout << " L 不为空！\n";
    ClearList_L(L);
    std::cout << "清空 L 后：";
    ListEmpty_L(L) ? std::cout << " L 为空！！\n"
                   : std::cout << " L 不为空！\n";
    std::cout << "\n";
  }
  PressEnter;

  std::cout << "函数 DestroyList_L 测试...\n";//函数DestroyList_L测试
  {
    std::cout << "销毁 L 前：";
    L ? std::cout << " L 存在！\n" : std::cout << " L 不存在！！\n";
    DestroyList_L(L);
    std::cout << "销毁 L 后：";
    L ? std::cout << " L 存在！\n" : std::cout << " L 不存在！！\n";
    std::cout << "\n";
  }
  PressEnter;

  std::cout << "函数 CreateList_HL 测试...\n";//函数CreateList_HL测试
  {
    LinkList L;
    std::cout << "头插法建立单链表 L = ";
    CreateList_HL(L, 5);
    ListTraverse_L(L, visit);
    std::cout << "\n\n";
  }
  PressEnter;

  std::cout << "函数 CreateList_TL 测试...\n";//函数CreateList_TL测试
  {
    LinkList L;
    std::cout << "尾插法建立单链表 L = ";
    CreateList_TL(L, 5);
    ListTraverse_L(L, visit);
    std::cout << "\n\n";
  }
  PressEnter;

  LinkList A, B, C;
  InitList_L(A);
  InitList_L(B);
  InitList_L(C);
  ListInsert_L(A, 1, 2);
  ListInsert_L(A, 2, 4);
  ListInsert_L(A, 3, 5);
  ListInsert_L(A, 4, 10);
  ListInsert_L(A, 5, 15);
  ListInsert_L(B, 1, 1);
  ListInsert_L(B, 2, 6);
  ListInsert_L(B, 3, 8);
  ListInsert_L(B, 4, 12);
  std::cout << "单链表A的元素：";
  ListTraverse_L(A, visit);
  /* 依次对元素调用visit()，输出元素的值 为 2、4、5、10、15*/
  std::cout << "\n";
  std::cout << "单链表B的元素：";
  ListTraverse_L(B, visit);
  /* 依次对元素调用visit()，输出元素的值 为 1、6、8、12*/
  std::cout << "\n";

  PressEnter;
  Merge(A, B, C);
  std::cout << "合并后单链表C的元素：";
  ListTraverse_L(C, visit);
  /* 依次对元素调用visit()，输出元素的值 为 1、2、4、5、6、8、10、12、15*/
  std::cout << "\n";
  PressEnter;

  //将单链表C逆置
  Reverse(C);
  std::cout << "逆置后单链表C的元素：";
  ListTraverse_L(C, visit);
  /* 依次对元素调用visit()，输出元素的值 为 15、12、10、8、6、5、4、2、1、*/
  std::cout << "\n";
  PressEnter;

  DestroyList_L(A);
  DestroyList_L(B);
  DestroyList_L(C);
  PressEnter;

  return 0;
}
