//
// Created by aruve on 2022/11/13.
//

#ifndef HUFFMANEDITOR__HUFFMAN_H_
#define HUFFMANEDITOR__HUFFMAN_H_

#include "common.h"

// 定义树的结点
typedef struct TNode {
  int w;              // 权值
  unsigned char ch;   // 代表字符 仅对叶子节点有效
  TNode *left, *right;// 左右子树

  TNode() : w(0), ch(0), left(nullptr), right(nullptr){};
  TNode(int w, unsigned char ch) : w(w), ch(ch), left(nullptr), right(nullptr){};
  TNode(TNode *x, TNode *y) : w(x->w + y->w), ch(0), left(x), right(y){};// 便于树的合并
} * huffTree;

// 优先队列比较函数 小根堆
struct cmp {
  bool operator()(TNode *a, TNode *b) {
    return a->w > b->w;
  }
};

// 定义哈夫曼类
class huffman {
 public:     // 公有成员 对外可见
  huffman(); // 构造函数
  ~huffman();// 析构函数

  void createTree(const std::unordered_map<unsigned char, int> &);// 创建哈夫曼树
  void createCode();                                              // 创建哈夫曼编码表
  void saveCodeHex(std::string);            // 存储哈夫曼编码表 源码以十六进制数表示
  void saveCodeChar(std::string);           // 存储哈夫曼编码表 源码以字符表示
  void encodeBmp(std::string, std::string); // 对二进制文件进行编码
  void encodeText(std::string, std::string);// 对文本文件进行编码
  void decode(std::string, std::string);    // 对某文件进行译码
  void showTree();                          // 凹入表输出哈夫曼树

 private:                                   // 公有成员 对外不可见
  huffTree root;                            // 哈夫曼树根节点
  std::map<unsigned char, std::string> keys;// 编码表

  void _createCode(TNode *, std::string);// 创建哈夫曼编码表 内部处理接口
  void _showTree(TNode *, int);          // 凹入表输出哈夫曼树 内部处理接口
};

#endif//HUFFMANEDITOR__HUFFMAN_H_
