//
// Created by aruve on 2022/12/15.
//

#ifndef HASH_TABLE__HASH_TABLE_H_
#define HASH_TABLE__HASH_TABLE_H_

#include "common.h"

/* hashtable 元素节点 */
template<class Value>
struct hash_table_node {
  hash_table_node *next;// 指向下一个节点
  Value val;            // 值域
  /* 构造函数 */
  hash_table_node(const Value &val) : val(val) {}
};

/* hashtable 类 */
/*
 * Value:       节点的实值类型
 * Key:         节点的键值类型
 * HashFun:     hash function 的函数类型
 * ExtractKey:  从节点中取出键值的方法
 * EqualKey:    判断键值是否相同的方法
 */
template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey>
class hash_table {
 public:
  typedef HashFun hasher;//
  typedef EqualKey key_equal;
  typedef size_t size_type;
  typedef Value value_type;// 实值类型
  typedef Key key_type;    // 键值类型

 private:
  hasher hash;       // hash function
  key_equal equals;  // 判断键值是否相同的方法
  ExtractKey get_key;// 从节点中取出键值的方法

  typedef hash_table_node<Value> node;// 节点

  size_type num_elements;     // hashtable 中有效元素个数
  std::vector<node *> buckets;// bukcets 桶

 private:
  /* 新建节点 */
  node *new_node(const value_type &obj) {
    node *n = new node(obj);
    return n;
  }
  /* 删除节点 */
  void delete_node(node *n) {
    delete n;
  }
  /* 获取比不小于当前值的 bukcet 大小*/
  inline unsigned long __next_prime(unsigned long n) {
    const unsigned long *first = __prime_list;
    const unsigned long *last = __prime_list + __num_primes;
    /* 内置查找函数 查找不小于 n 的数 返回 std::iterator */
    const unsigned long *pos = std::lower_bound(first, last, n);
    /* 特判边缘 */
    return pos == last ? *(last - 1) : *pos;
  }
  /* 内部封装上述函数 */
  size_type next_size(size_type n) {
    return __next_prime(n);
  }
  /* 初始化 buckets */
  void init_buckets(size_type n) {
    const size_type n_buckets = next_size(n);
    buckets.insert(buckets.end(), n_buckets, 0);
  }

 public:
  /* 构造函数 */
  hash_table(size_type n, const HashFun &hf, const EqualKey &eql)
      : hash(hf),
        equals(eql),
        get_key(ExtractKey()),
        num_elements(0) {
    init_buckets(n);
  }
  /* 析构函数 */
  ~hash_table() {
    clear();
  }

 public:
  /* 返回当前 bucket 的数量 */
  size_type bucket_count() {
    return buckets.size();
  }
  /* 返回最大 bukcet 大小*/
  size_type max_buckey_count() const {
    return __prime_list[__num_primes - 1];
  }
  /* 返回 hashtable 有效元素个数 */
  size_type size() const {
    return num_elements;
  }
  /* 返回指定 bucket 中元素个数 */
  size_type elem_in_bucket(size_type num) {
    size_type result = 0;
    for (node *cur = buckets[num]; cur; cur = cur->next) {
      result++;
    }
    return result;
  }
  /* 查找元素 返回该节点和比较次数 */
  std::pair<node *, int> find(const key_type &key) {
    size_type n = bkt_num(key);// 获取键值
    node *first;
    int cnt = 1;
    // 遍历每个结点
    for (first = buckets[n]; first && !equals(get_key(first->val), key); first = first->next) {
      cnt++;
    }
    return {first, cnt};
  }
  /* 返回指定键值的元素个数 */
  size_type count(const key_type &key) {
    size_type n = bkt_num(key);// 确定 key 在哪个 buckets 里
    size_type result = 0;
    // 遍历每个结点
    for (const node *cur = buckets[n]; cur; cur = cur->next) {
      if (equals(get_key(cur->val), key)) {// 值相等
        result++;
      }
    }
    return result;
  }
  /* 插入元素 允许键值重复 */
  void insert(const value_type &obj) {
    resize(num_elements + 1);// 更改大小
    insert_noresize(obj);    // 辅助函数
  }
  /* 删除元素 */
  void erase(const value_type &obj) {
    const size_type n = bkt_num(obj);// 确定 key 在哪个 buckets 里
    // 遍历每个结点
    for (node *cur = buckets[n], *pre = buckets[n]; cur; pre = cur, cur = cur->next) {
      if (equals(get_key(cur->val), get_key(obj))) {// 相等
        node *next = cur->next;
        pre->next = next;
        delete_node(cur);// 删除
        cur = next;
      }
    }
  }
  /* 清空 hashtable 但 buckets 仍保留大小 */
  void clear() {
    for (size_type i = 0; i < buckets.size(); i++) {
      node *cur = buckets[i];
      while (cur != nullptr) {
        node *next = cur->next;
        delete_node(cur);
        cur = next;
      }
      buckets[i] = nullptr;
    }
    num_elements = 0;
  }

 private:
  /* 重设 buckets 大小 */
  void resize(size_type num_elements_hint) {
    const size_type old_n = buckets.size();// 原来大小
    if (num_elements_hint > old_n) {       // 当前个数大于时更新
      // 找到下一个质数
      const size_type n = next_size(num_elements_hint);
      if (n > old_n) {
        std::vector<node *> tmp(n, (node *) 0);// 设立新的 buckets
        // 依次处理每一个
        for (size_type bucket = 0; bucket < old_n; bucket++) {
          node *first = buckets[bucket];
          // 遍历 list
          while (first) {
            size_type new_bucket = bkt_num(first->val, n);
            buckets[bucket] = first->next;
            first->next = tmp[new_bucket];
            tmp[new_bucket] = first;
            first = buckets[bucket];
          }
        }
        buckets.swap(tmp);// 交换新旧 buckets
      }                   // 离开时 tmp 被释放
    }
  }
  /* 内部插入函数 */
  void insert_noresize(const value_type &obj) {
    const size_type n = bkt_num(obj);// 计算哈希值
    node *first = buckets[n];
    for (node *cur = first; cur; cur = cur->next) {// 遍历链表
      if (equals(get_key(cur->val), get_key(obj))) {
        node *tmp = new_node(obj);// 连接
        tmp->next = cur->next;
        cur->next = tmp;
        num_elements++;// 元素加一
        return;
      }
    }
    // 若是改位置第一个元素
    node *tmp = new_node(obj);
    tmp->next = first;
    buckets[n] = tmp;
    num_elements++;// 元素个数加一
  }

 public:
  /* 接受实值和大小 */
  size_type bkt_num(const value_type &obj, size_type n) {
    return bkt_num_key(get_key(obj), n);
  }
  /* 接受实值 */
  size_type bkt_num(const value_type &obj) {
    return bkt_num_key(get_key(obj));
  }
  /* 接受键值 */
  size_type bkt_num_key(const key_type &key) {
    return bkt_num_key(key, buckets.size());
  }
  /* 接受键值和大小 */
  size_type bkt_num_key(const key_type &key, size_type n) {
    return hash(key) % n;
  }

 private:
  /* 质数表 */
  static const int __num_primes = 28;
  constexpr static const unsigned long __prime_list[__num_primes] = {
    53,       97,        193,       389,       769,       1543,       3079,         6151,        12289,    24593,
    49157,    98317,     196613,    393241,    786433,    1572869,    3145739,      6291469,     12582917, 25165843,
    50331653, 100663319, 201326611, 402653189, 805306457, 1610612741, 3221225473ul, 4294967291ul};
};

#endif//HASH_TABLE__HASH_TABLE_H_
