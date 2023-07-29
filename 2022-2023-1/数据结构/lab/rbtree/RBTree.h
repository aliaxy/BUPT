//
// Created by aruve on 2022/12/6.
//

#ifndef REDBLACKTREE__RBTREE_H_
#define REDBLACKTREE__RBTREE_H_

#include "common.h"// 包含所需头文件

/* 颜色枚举类型 方便识别 */
enum Color { RED, BlACK };

/* 树节点结构 */
template<class V>
struct RBTNode {
  RBTNode<V> *left;  // 左儿子
  RBTNode<V> *right; // 右儿子
  RBTNode<V> *parent;// 父亲

  V val;  // 节点值
  int col;// 节点颜色

  RBTNode() = default;// 默认构造函数
};

/* 红黑树类 */
template<class V>
class RBTree {
  /* 成员变量 */
 private:
  RBTNode<V> *root;// 根节点
  RBTNode<V> *Nil; // 外部节点 表示空结点 为黑色

  /* 构造与析构 */
 public:
  /* 构造函数*/
  RBTree() {
    Nil = buyNode();
    root = Nil;
    Nil->col = BlACK;
  }
  /* 析构函数 */
  ~RBTree() {
    destory(this->root);
    delete this->Nil;
    this->Nil = nullptr;
  }
  /* 申请新节点 */
  RBTNode<V> *buyNode(const V &val = V()) {
    RBTNode<V> *curr = new RBTNode<V>();
    assert(curr != nullptr);
    curr->col = RED;
    curr->left = curr->right = curr->parent = Nil;
    curr->val = val;
    return curr;
  }
  /* 销毁红黑树 */
  void destory(RBTNode<V> *root) {
    if (root == Nil) {
      return;
    }
    if (root->left != Nil) {
      destory(root->left);
    }
    if (root->right != Nil) {
      destory(root->right);
    }
    delete root;
    root = nullptr;
  }

  /* 用户 API */
 public:
  /* 中序遍历输出 */
  void inOrderPrint() {
    inOrderTraversal(this->root);
  }
  /* 插入结点 */
  void insert(const V &val) {
    RBTNode<V> *pr = this->Nil;
    RBTNode<V> *curr = this->root;
    // 查找该节点应该插入的位置
    while (curr != this->Nil) {
      if (val == curr->val) {
        return;
      }
      pr = curr;
      if (val < curr->val) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    curr = buyNode(val);// 申请节点
    if (pr == Nil) {    // 根节点
      root = curr;
      root->parent = pr;
    } else {
      if (val < pr->val) {
        pr->left = curr;
      } else {
        pr->right = curr;
      }
      curr->parent = pr;
    }
    insertFix(curr);// 调用插入修正函数
  }
  /* 查找结点*/
  std::pair<RBTNode<int> *, int> find(const V &val) {
    std::pair<RBTNode<int> *, int> curr = _find(this->root, val, 0);
    if (curr.first == Nil) {
      curr.first = nullptr;
    }
    return curr;
  }
  /* 删除结点 */
  void erase(const V &val) {
    std::pair<RBTNode<int> *, int> curr = _find(this->root, val);
    if (curr.first != Nil) {
      _erase(curr.first);
    }
  }
  /* 返回每条到叶子节点路径中黑色结点的个数 */
  int blackNodeNum() {
    return _calPathBlackNode(this->root, 0);
  }

  /* 辅助函数 */
 private:
  /* 中序遍历 */
  void inOrderTraversal(RBTNode<V> *root) {
    static int cnt = 0;
    if (root != this->Nil) {
      inOrderTraversal(root->left);
      std::cout << root->val << ' ';
      cnt++;
      if (cnt == 20) {
        std::cout << '\n';
        cnt = 0;
      }
      inOrderTraversal(root->right);
    }
  }
  /* 插入元素修正 */
  void insertFix(RBTNode<V> *curr) {
    RBTNode<V> *uncle;// 叔结点
    while (curr->parent->col == RED) {
      /* 父亲是左孩子 */
      if (curr->parent == curr->parent->parent->left) {
        uncle = curr->parent->parent->right;
        if (uncle->col == BlACK) {// 不存在叔节点
          if (curr == curr->parent->right) {
            curr = curr->parent;// 先置为父结点 再左旋
            rotateL(curr);
          }
          // 将 curr 的父节点变为黑色 祖父的结点变为红色
          curr->parent->col = BlACK;
          curr->parent->parent->col = RED;
          // 祖父进行右旋
          rotateR(curr->parent->parent);
        } else {
          // 父结点和叔结点都变为黑色
          curr->parent->col = BlACK;
          uncle->col = BlACK;
          // 祖父结点变为红色
          curr->parent->parent->col = RED;
          // 指向下一节点
          curr = curr->parent->parent;
        }
      } else {// 父亲是右孩子
        uncle = curr->parent->parent->left;
        if (uncle->col == BlACK) {
          /* 右接左 先右旋*/
          if (curr == curr->parent->left) {
            curr = curr->parent;
            rotateR(curr);
          }
          // 将 curr 的父节点变为黑色 祖父的结点变为红色
          curr->parent->col = BlACK;
          curr->parent->parent->col = RED;
          // 祖父进行左旋
          rotateL(curr->parent->parent);
        } else {
          // 父结点和叔结点都变为黑色
          curr->parent->col = BlACK;
          uncle->col = BlACK;
          // 祖父结点变为红色
          curr->parent->parent->col = RED;
          // 指向下一节点
          curr = curr->parent->parent;
        }
      }
    }
    // 根节点为黑色
    root->col = BlACK;
  }
  /* 左旋操作 */
  void rotateL(RBTNode<V> *curr) {
    RBTNode<V> *R = curr->right;
    curr->right = R->left;
    if (R->left != Nil) {
      R->left->parent = curr;
    }
    R->parent = curr->parent;
    if (this->root == curr) {
      this->root = R;
    } else if (curr == curr->parent->left) {
      curr->parent->left = R;
    } else {
      curr->parent->right = R;
    }
    R->left = curr;
    curr->parent = R;
  }
  /* 右旋操作 */
  void rotateR(RBTNode<V> *curr) {
    RBTNode<V> *L = curr->left;
    curr->left = L->right;
    if (L->right != Nil) {
      L->right->parent = curr;
    }
    L->parent = curr->parent;
    if (this->root == curr) {
      this->root = L;
    } else if (curr == curr->parent->left) {
      curr->parent->left = L;
    } else {
      curr->parent->right = L;
    }
    L->right = curr;
    curr->parent = L;
  }
  /* 查找函数内部 */
  std::pair<RBTNode<int> *, int> _find(RBTNode<V> *root, const V &val, int cnt) {
    if (root == Nil) {// 不存在
      return {Nil, cnt + 1};
    }
    if (val == root->val) {// 找到
      return {root, cnt + 1};
    }
    if (val < root->val) {// 当前值小 遍历左子树
      return _find(root->left, val, cnt + 1);
    } else {// 当前值大 遍历右子树
      return _find(root->right, val, cnt + 1);
    }
  }
  /* 返回值最小的结点 */
  RBTNode<V> *minTNode(RBTNode<V> *root) {
    if (root->left == Nil) {
      return root;
    }
    return minTNode(root->left);
  }
  /* 删除函数内部 */
  void _erase(RBTNode<V> *curr) {
    RBTNode<V> *y = curr;// 替换z的节点
    RBTNode<V> *x = Nil; // y节点的孩子
    if (curr->left == Nil) {
      x = curr->right;
    } else if (curr->right == Nil) {
      x = curr->left;
    } else {                    // 该节点有两个孩子
      y = minTNode(curr->right);// 找到有孩子的最小值
      if (y->left != Nil) {
        x = y->left;
      } else {
        x = y->right;
      }
    }
    // 正好为根节点 相当于只有这一个结点
    if (y == this->root) {
      root = x;
      x->parent = x->left = x->right = Nil;
      x->col = BlACK;
      return;
    }

    curr->val = y->val;
    // 记录 y 的颜色
    Color col = y->col;

    // 进行连接
    if (y == y->parent->left) {
      y->parent->left = x;
    } else {
      y->parent->right = x;
    }
    x->parent = y->parent;
    delete y;
    y = nullptr;

    // 删除的颜色为黑色时才进行修正
    if (col == BlACK) {
      eraseFix(x);
    }
  }
  /* 删除元素修正 */
  void eraseFix(RBTNode<V> *curr) {
    // 当结点 curr 不为根并且它的颜色不是黑色
    while (curr != this->root && curr->col == BlACK) {
      // curr 在左子树
      if (curr == curr->parent->left) {
        RBTNode<V> *w = curr->parent->right;
        if (w->col == RED) {
          // 变为黑色 父结点变为红色
          w->col = BlACK;
          curr->parent->col = RED;
          rotateL(curr->parent);// 左旋
          w = curr->parent->right;
        }
        if (w->left->col == BlACK && w->right->col == BlACK) {
          w->col = RED;
          curr = curr->parent;
        } else {
          if (w->right->col == BlACK) {
            w->col = RED;
            w->left->col = BlACK;
            rotateR(w);// 右旋
            w = curr->parent->right;
          }
          // 颜色替换
          w->col = w->parent->col;
          // 都变为黑色
          w->parent->col = BlACK;
          w->right->col = BlACK;
          // 父亲进行左旋
          rotateL(curr->parent);
          // 变为根结点
          curr = root;
        }
      } else {
        RBTNode<V> *w = curr->parent->left;
        if (w->col == RED) {
          w->parent->col = RED;
          w->col = BlACK;
          rotateR(curr->parent);// 右旋
          w = curr->parent->left;
        }
        if (w->right->col == BlACK && w->right->col == BlACK) {
          w->col = RED;
          curr = curr->parent;
        } else {
          if (w->left->col == BlACK) {
            w->right->col = BlACK;
            w->col = RED;
            rotateL(w);// 左旋
            w = curr->parent->left;
          }
          // 颜色替换
          w->col = curr->parent->col;
          // 都变为黑色
          curr->parent->col = BlACK;
          w->left->col = BlACK;
          // 父亲进行右旋
          rotateR(curr->parent);
          // 变为根结点
          curr = root;
        }
      }
    }
    // 根节点为黑色
    curr->col = BlACK;
  }
  /* 计算路径黑色节点数 */
  int _calPathBlackNode(RBTNode<V> *root, int num) {
    if (root == Nil) {
      return num + 1;
    }
    if (root->col == BlACK) {
      num++;
    }
    _calPathBlackNode(root->left, num);
  }
};

#endif//REDBLACKTREE__RBTREE_H_
