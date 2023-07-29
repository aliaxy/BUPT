# 第一次作业

### P60

```c
unsigned replace_byte(unsigned x, int i, unsigned char b) {
    unsigned mask = ((unsigned)0xff) << (i << 3);
    mask = ~mask;
    return (x & mask) | ((unsigned)b << (i << 3));
}
```

> 1. 将掩码`mask=0xff`左移`8*i`位，这样得到对于要替换字节所对应的位置为1，其他字节处均为0
> 2. 对`mask`按位取反,使得对于要替换字节所对应的位置为0，其他字节处均为1
> 3. 将`x`与`mask`按位与，这样对于`x`的要替换字节处全为0，其余保持不变
> 4. 将`b`左移`8*i`位，使得要替换字节与`x`中的位置对齐
> 5. 3和4的结果按位或，即可完成替换

### P65

```c
int odd_ones(unsigned x) {
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 0x1;
}
```

> 使用$x_i$来代表`x`的第i位，对于`w=32`有
> $$
> \begin{flalign*}
> res & = x_0 \oplus x_1 \oplus x_2 \oplus \cdots \oplus x_{31} & \\
>     & = (x_0 \oplus x_{16}) \oplus (x_1 \oplus x_{17}) \oplus \cdots \oplus (x_{15} \oplus x_{31}) \ 将每项异或结果记为y_i &\\
>     & = y_0 \oplus y_1 \oplus y_2 \oplus \cdots \oplus y_{15} & \\
>     & = (y_0 \oplus y_8) \oplus (y_1 \oplus y_9) \oplus \cdots \oplus (y_7 \oplus y_{15}) \ 将每项异或结果记为z_i& \\
>     & = (z_0 \oplus z_4) \oplus (z_1 \oplus z_5) \oplus (z_2 \oplus z_6) \oplus (z_3 \oplus z_7) & \\
>     & = (a_0 \oplus a_2) \oplus (a_1 \oplus a_3) & \\
>     & = b_0 \oplus b_1 & \\
>     & = c_0
> \end{flalign*}
> $$
> 因此，每次对`x`的位进行折半异或，异或结果保存到低位，直至`x`的最后一位，将其与`0x00000001`进行按位与运算，即可得到结果
>
> 

### P67

* ```
  32位机器最多只能移位31位，否则位“未定义”
  ```

* ```c
  int int_size_is_32() {
      int set_mab = 1 << 31;
      int beyond_msb = set_mab << 1;
      return set_mab && !beyond_msb;
  }
  ```

  > 由于一次最多只能左移31位，所以可以让`beyond_msb`在`set_mab`的基础上再左移1位来实现

* ```c
  int int_size_is_32_for_16() {
      int set_mab = 1 << 15 << 15 << 1;
      int beyond_msb = set_mab << 1;
      return set_mab && !beyond_msb;
  }
  ```

  > 对于16位`int`，一次最多只能左移15位，可以分次移动，`1+15+15+1=31`，`beyond_mab`操作同上

### P68

```c
int lower_one_mask(int n) {
    int w = sizeof(int) << 3;
    return (int)((unsigned)~0 >> (w - n));
}
```

> 1. 生成n位掩码，需要将`0xfffffff`（不用机器稍有不同），也就是`-1`逻辑右移`w - n`位即可
> 2. 由于不能准确确定`int`的位数，因此采用`sizeof(int) << 3`的方式来获取，`-1`同理，将`0`按位取反得到，这样避免在不同机器上带来的麻烦