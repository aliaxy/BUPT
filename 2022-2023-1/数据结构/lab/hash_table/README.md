# 动态查找算法实验

## 题目B：哈希表查找实验

### 【基本要求】

1. 完成哈希表的构造、销毁、插入、删除、查找操作。
2. 读取文件插入不少于100条数据记录。
3. 输入若干存在和不存在的关键字进行查询，输出查找时间和比较次数。
4. 可以使用开源代码实现，但需要阅读代码并添加一定数量的注释。

### 【扩展要求】

支持哈希表扩容。

# 实验报告

## 需求分析

1. 用哈希表实现动态查找，建立哈希表内部实现代码，完成插入、删除、查找等基本操作
2. 在`in.txt`文件中读取数据记录
3. 查找关键字时，输出是否存在、查找时间和比较次数

---

## 概要设计

### 主要模块流程

```mermaid
graph LR
	完成哈希表内部实现-->文件读入数据-->构建哈希表-->查找元素-->输出数据
```

### 主要数据结构及接口

#### `hash_table.h`

```c++
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
  node *new_node(const value_type &obj);
  /* 删除节点 */
  void delete_node(node *n);
  /* 获取比不小于当前值的 bukcet 大小*/
  inline unsigned long __next_prime(unsigned long n);
  /* 内部封装上述函数 */
  size_type next_size(size_type n);
  /* 初始化 buckets */
  void init_buckets(size_type n);

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
  ~hash_table();

 public:
  /* 返回当前 bucket 的数量 */
  size_type bucket_count();
  /* 返回最大 bukcet 大小*/
  size_type max_buckey_count();
  /* 返回 hashtable 有效元素个数 */
  size_type size();
  /* 返回指定 bucket 中元素个数 */
  size_type elem_in_bucket(size_type num);
  /* 查找元素 返回该节点和比较次数 */
  std::pair<node *, int> find(const key_type &key);
  /* 返回指定键值的元素个数 */
  size_type count(const key_type &key);
  /* 插入元素 允许键值重复 */
  void insert(const value_type &obj);
  /* 删除元素 */
  void erase(const value_type &obj);
  /* 清空 hashtable 但 buckets 仍保留大小 */
  void clear();

 private:
  /* 重设 buckets 大小 */
  void resize(size_type num_elements_hint);
  /* 内部插入函数 */
  void insert_noresize(const value_type &obj);

 public:
  /* 接受实值和大小 */
  size_type bkt_num(const value_type &obj, size_type n);
  /* 接受实值 */
  size_type bkt_num(const value_type &obj);
  /* 接受键值 */
  size_type bkt_num_key(const key_type &key);
  /* 接受键值和大小 */
  size_type bkt_num_key(const key_type &key, size_type n);

 private:
  /* 质数表 */
  static const int __num_primes = 28;
  constexpr static const unsigned long __prime_list[__num_primes] = {
    53,       97,        193,       389,       769,       1543,       3079,         6151,        12289,    24593,
    49157,    98317,     196613,    393241,    786433,    1572869,    3145739,      6291469,     12582917, 25165843,
    50331653, 100663319, 201326611, 402653189, 805306457, 1610612741, 3221225473ul, 4294967291ul};
};

#endif//HASH_TABLE__HASH_TABLE_H_
```

---

## 详细设计

### 采用与 c++ 内部 hash_table 相同的实现原理，参考其源码手动实现其类

#### ` inline unsigned long __next_prime(unsigned long n);`

```c++
/* 获取比不小于当前值的 bukcet 大小*/
inline unsigned long __next_prime(unsigned long n) {
  const unsigned long *first = __prime_list;
  const unsigned long *last = __prime_list + __num_primes;
  /* 内置查找函数 查找不小于 n 的数 返回 std::iterator */
  const unsigned long *pos = std::lower_bound(first, last, n);
  /* 特判边缘 */
  return pos == last ? *(last - 1) : *pos;
}
```

#### `size_type bucket_count();`

```c++
/* 返回当前 bucket 的数量 */
size_type bucket_count() {
  return buckets.size();
}
```

#### `size_type max_buckey_count();`

```c++
/* 返回最大 bukcet 大小*/
size_type max_buckey_count() const {
  return __prime_list[__num_primes - 1];
}
```

#### `size_type size();`

```c++
/* 返回 hashtable 有效元素个数 */
size_type size() const {
  return num_elements;
}
```

#### `size_type bucket_count();`

```c++
/* 返回当前 bucket 的数量 */
size_type bucket_count() {
  return buckets.size();
}
```

#### `size_type elem_in_bucket(size_type num);`

```c++
/* 返回指定 bucket 中元素个数 */
size_type elem_in_bucket(size_type num) {
  size_type result = 0;
  for (node *cur = buckets[num]; cur; cur = cur->next) {
    result++;
  }
  return result;
}
```

#### `std::pair<node *, int> find(const key_type &key);`

```c++
/* 查找元素 返回该节点和比较次数 */
std::pair<node *, int> find(const key_type &key) {
  size_type n = bkt_num(key);// 获取键值
  node *first = buckets[n];
  int cnt = 1;
  // 遍历每个结点
  for (; first && !equals(get_key(first->val), key); first = first->next) {
    cnt++;
  }
  return {first, cnt};
}
```

#### `size_type count(const key_type &key);`

```c++
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
```

#### `void erase(const value_type &obj);`

```c++
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
```

#### `void clear();`

```c++
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
```

#### `void resize(size_type num_elements_hint);`

```c++
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
```

#### `size_type bucket_count();`

```c++
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
```

#### `size_type bkt_num(const value_type &obj, size_type n);`

```c++
/* 接受实值和大小 */
size_type bkt_num(const value_type &obj, size_type n) {
  return bkt_num_key(get_key(obj), n);
}
```

#### `size_type bkt_num(const value_type &obj);`

```c++
/* 接受实值 */
size_type bkt_num(const value_type &obj) {
  return bkt_num_key(get_key(obj));
}
```

#### `size_type bkt_num_key(const key_type &key);`

```c++
/* 接受键值 */
size_type bkt_num_key(const key_type &key) {
  return bkt_num_key(key, buckets.size());
}
```

#### `size_type bkt_num_key(const key_type &key, size_type n);`

```c++
/* 接受键值和大小 */
size_type bkt_num_key(const key_type &key, size_type n) {
  return hash(key) % n;
}
```

---

## 设计和调试分析

### 采用与 c++ 内部 hash_table 相同的实现原理，参考其源码手动实现其类

---

## 用户手册

1. `in.txt`是所需的数据记录，其中第一个元素是数据个数
2. 程序运行读取`in.txt`文件进行构建哈希表
3. 控制台输入要查询的元素，以`-1`结束。程序在控制台输出是否存在、比较次数和查找时间

---

## 测试结果

### `in.txt`

> ```
> 1000
> 2162 3779 4425 2027 4747 4017 4243 2159 4004 539
> 1886 2530 1941 2191 4444 4056 1802 1021 4152 499
> 1628 4214 3105 426 1796 3983 4353 3153 4474 1325
> 159 2034 2209 992 972 3337 1740 2813 3251 49 
> 3886 4900 4344 960 3701 2950 2581 3002 1681 4718
> 4536 1947 1045 2154 2029 3061 900 1564 1075 1572 
> 1237 4455 1868 2977 1067 329 4464 812 3852 422 
> 517 2037 4502 196 1259 3926 4197 1419 1324 4651 
> 2955 3165 611 2068 2017 1696 3907 1865 4389 2931
> 4417 2268 3377 3841 1623 2718 2432 1323 3461 134 
> 2775 1088 688 2452 815 2472 254 4518 3619 2479
> 3948 3979 3834 3156 3996 4850 2503 285 1543 3579 
> 899 3027 568 2370 4897 2051 3802 869 3087 2742
> 3114 3305 3401 1 1104 2333 852 1927 818 3978 
> 952 671 3282 4815 2423 1353 1283 174 3621 3181
> 945 1316 2111 3933 2618 4898 2680 3307 3298 2623 
> 3732 2989 859 3069 4178 4717 2959 741 2845 4411
> 3302 4791 4370 2012 3905 1425 2093 544 1653 4794 
> 2459 4838 218 2896 4990 3054 4150 823 4128 4576
> 2358 4412 532 2750 4978 2760 4772 4913 2705 3557 
> 1450 985 2094 4956 4035 3759 203 3490 4167 1580
> 343 4358 300 2978 3653 69 2287 2932 714 3679 
> 1461 354 4790 1463 142 1707 2125 790 1690 390
> 1499 4268 1667 558 3824 2584 3693 2613 1430 4924 
> 488 2706 2048 2263 2298 2188 1729 3947 553 3017
> 917 2128 3404 16 4452 3154 1948 3336 4859 4784 
> 136 2187 2804 110 526 3394 392 1378 2487 3260
> 1498 3952 3341 1123 2961 743 1206 2669 2431 4649 
> 172 44 4480 2262 1153 1980 26 3107 1326 2132
> 991  4318 4308 2427 375 1857 1269 4596 4916 856 
> 3074 145 4003 4954 986 3204 2734 3843 1679 1195
> 113 648 1757 107 1216 2271 1162 3380 122 1231 
> 3395 4315 4062 221 2439 3500 3013 795 4264 3862
> 3321 1890 2999 1917 4375 2157 2671 3780 736 1845 
> 1304 2582 364 3276 2260 637 529 4965 1758 27
> 4463 1332 3550 845 3809 3038 2556 1168 3128 4237 
> 2019 4724 3723 396 723 4050 236 1345 1291 4618
> 3509 3664 2555 3096 1270 3515 188 2403 665 3992 
> 4162 1849 510 564 1592 3810 3001 783 4508 2397
> 1288 1315 4642 206 4534 1829 3993 3044 2438 1897 
> 3980 2357 2411 193 3152 2070 3747 3720 4829 3029
> 4733 4473 1146 2255 3755 4864 1028 4400 1073 2486 
> 4704 1818 2739 4964 4193 406 2837 3746 3205 3890
> 536 4972 3915 588 2583 1569 4896 1292 2401 4565 
> 4761 2170 547 2143 3252 304 4740 4010 1993 4211
> 1506 1598 489 3960 633 3338 2797 1661 3879 1756 
> 4461 3379 1915 2686 1791 2305 1256 4556 2338 565
> 2783 2526 4756 320 1321 4648 780 4107 4665 229 
> 3475 2478 3912 2944 4053 1375 266 3566 1348 1358
> 4685 1439 303 2521 1615 506 4942 2079 3149 4494 
> 3385 2303 1355 4060 3 4439 111 4775 1448 3071
> 1705 4275 505 3751 1255 2364 1199 888 3106 4134 
> 4684 112 2963 3180 2639 4857 1611 2259 4477 41
> 1664 3287 3382 2164 1001 4328 3963 3334 1545 2654 
> 1640 4967 4710 3567 2361 1820 3325 4123 567 3570
> 4679 3696 626 3953 707 612 4848 3739 1575 3254 
> 2145 1036 4363 2419 3482 2373 2968 750 4723 3504
> 177 4613 2780 3889 4998 3970 64 2120 2993 1884 
> 1830 4048 2519 283 2501 2596 1487 4814 3164 4273
> 445 4232 3502 2949 4760 4219 1933 4692 2474 4094 
> 361 1470 1096 3314 609 2314 2828 1685 35 1144
> 2166 1057 1071 2180 4398 4966 2748 3857 4722 286 
> 4222 3113 4195 4468 32 3278 2088 438 2575 4793
> 3684 550 3850 1632 1497 3715 2606 3201 983 3120 
> 2552 334 2129 4347 742 2960 1851 3783 4527 3786
> 459 605 2823 3445 4554 118 2107 4271 105 3432 
> 2497 4715 2551 2916 4847 4119 792 170 3497 332
> 873 3416 538 4866 1052 2702 484 1593 4839 2123 
> 3232 3773 222 3549 2440 1710 601 4469 1142 169
> 4605 1278 1813 271 2665 1556 993 4320 2156 4082 
> 755 2973 1891 498 3825 1607 2716 1525 416 725
> 3430 1558 449 2586 4804 3695 4537 3428 2319 1156 
> 4483 4023 696 3617 4780 3671 1453 1895 3518 569
> 4131 3049 2222 4 2007 4225 3116 2269 51 1133 
> 1139 4466 1030 3248 4330 12 3339 3079 2511 3620
> 3277 4386 4927 76 2496 3605 4173 1955 3064 779 
> 2997 1888 4207 1578 469 3174 3546 1382 1344 467
> 4569 3584 272 1381 2490 3893 641 238 4277 950 
> 3168 1004 2241 4459 1804 3471 1253 4944 1617 2840
> 3949 2084 407 2625 668 73 2291 2986 768 1601 
> 492 4635 2417 4662 1335 1013 1686 2795 3632 1179
> 4506 3560 2451 1172 3390 4354 3245 166 3493 2384 
> 2482 2006 4711 4204 417 3259 473 3800 821 4257
> 1145 2254 3363 36 210 702 4278 3169 2601 3710 
> 1546 4545 3436 2327 4027 1068 3286 2549 2588 3697
> 4806 1479 1795 4764 3099 2602 384 2179 4454 3345 
> 1127 4336 2172 4043 716 3112 901 4228 490 1599
> 3292 2729 4742 1415 2524 3712 4334 2116 1007 83 
> 2312 4096 3068 850 4030 1812 2921 757 2591 1138
> 3356 4140 335 4771 2964 1346 2201 3988 661 2825 
> 2917 1646 2755 2083 2147 1553 296 3218 3191 2082
> 4300 1296 187 4542 1215 3433 2349 1631 2740 4958 
> 4294 3185 346 3559 2343 95 2313 1204 2885 667
> 3940 2831 121 314 1423 3100 882 2759 3055 2023 
> 738 4065 208 3034 302 1411 4482 154 3519 4628
> 2410 1738 2847 3956 527 1636 2745 3854 2758 1649 
> 3867 776 1699 590 3172 954 2063 2073 964 4011
> 684 2382 4333 1424 3426 1208 2317 2367 2258 4727 
> 2252 3361 3902 3032 3317 1099 2495 2580 1471 3208
> 2099 4458 372 3699 3140 1486 2595 4813 3513 349
> ```

### `console input`

>```
>36 6 456 86 534 975 6586 80765 46 234 456 7568
>345 25 7696 4324 7689 43564 9780 658 3 4532 -1
>```

### `console output`

> ```
> 36 exists.
> Compare times: 1
> Use time: 0.00000019s
> 
> 6 not exists.
> Compare times: 2
> Use time: 0.00000012s
> 
> 456 not exists.
> Compare times: 1
> Use time: 0.00000009s
> 
> 86 not exists.
> Compare times: 3
> Use time: 0.00000019s
> 
> 534 not exists.
> Compare times: 2
> Use time: 0.00000008s
> 
> 975 not exists.
> Compare times: 1
> Use time: 0.00000006s
> 
> 6586 not exists.
> Compare times: 2
> Use time: 0.00000007s
> 
> 80765 not exists.
> Compare times: 2
> Use time: 0.00000005s
> 
> 46 not exists.
> Compare times: 1
> Use time: 0.00000006s
> 
> 234 not exists.
> Compare times: 1
> Use time: 0.00000006s
> 
> 456 not exists.
> Compare times: 1
> Use time: 0.00000005s
> 
> 7568 not exists.
> Compare times: 2
> Use time: 0.00000017s
> 
> 345 not exists.
> Compare times: 2
> Use time: 0.00000008s
> 
> 25 not exists.
> Compare times: 1
> Use time: 0.00000008s
> 
> 7696 not exists.
> Compare times: 1
> Use time: 0.00000006s
> 
> 4324 not exists.
> Compare times: 1
> Use time: 0.00000005s
> 
> 7689 not exists.
> Compare times: 1
> Use time: 0.00000006s
> 
> 43564 not exists.
> Compare times: 1
> Use time: 0.00000011s
> 
> 9780 not exists.
> Compare times: 1
> Use time: 0.00000005s
> 
> 658 not exists.
> Compare times: 2
> Use time: 0.00000010s
> 
> 3 exists.
> Compare times: 2
> Use time: 0.00000010s
> 
> 4532 not exists.
> Compare times: 2
> Use time: 0.00000008s
> ```

---

