# 第二次作业

## 2.75

### 分析

> $x' * y'= x * y + (x_{w - 1}*y + y_{w-1}*x)*2^w + x_{w-1}*y_{w-1}*2^{2w}$
>
> 要获取高$w$位，而带有$2^{2w}$的项不影响计算结果
>
> 在用库函数获取$x * y$后，只需要计算 $x_{w - 1}*y + y_{w-1}*x$，由于不能使用乘法
>
> 因此做如下化简
>
> $x_{w-1},\, y_{w-1}$只能为 $0$ 或 $1$，可以对$x,\, y$使用算数右移来得到 $0$ 或 $-1$
>
> 应用**按位与**运算，即可得出答案

### 代码

```c
#include <stdio.h>
#include <limits.h>
#include <stdint.h>

int signed_high_prod(int x, int y) {
	int w = sizeof(unsigned) << 3;
	int64_t mul = (int64_t)x * y;
	return mul >> w;
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
	int w = sizeof(unsigned) << 3;
	int sign_x = (int)x >> (w - 1);
	int sign_y = (int)y >> (w - 1);
	int signed_prod = signed_high_prod(x, y);
	return signed_prod + (sign_x & y) + (sign_y & x);
}

int main(void) {
	unsigned x = UINT_MAX, y = UINT_MAX;
	int w = sizeof(unsigned) << 3;
	uint64_t mul = (uint64_t)x * y;
	printf("%lx %x\n", (uint64_t)x * y, (unsigned)(mul >> w));
	printf("%x\n", unsigned_high_prod(x, y));
	return 0;
}
```

### 运算结果如下

```c++
0xfffffffe00000001 0xfffffffe
0xfffffffe
```

## 2.77

* ```c++
  17 = 16 + 1 : (x << 4) + x
  ```

* ```c++
  -7 = -8 + 1 : x - (x << 3)
  ```

* ```c++
  60 = 64 - 4 : (x << 6) - (x << 2)
  ```

* ```c++
  -112 = -128 + 16 : (x << 4) - (x << 7)
  ```

## 2.79

### 分析

> * #### 使用左移运算来计算乘法，`3=2+1`，因此 `x + x << 1` 即可得到`3*x`的值
>
> * #### 对于除法，负数会产生误差，需要加一个偏移量，为$2^w - 1$，在此处为`(1 << 2) - 1`
>
> * #### 对于正数，不采取此操作，因此取`x`的符号位，使用按位与来判断
>
> * #### 正数得到`000000`，按位与永远为0
>
> * #### 负数得到`111111`，按位与与后面的值相同

### 代码

```c++
#include <stdio.h>

int mul3div4(int x) {
	x += x << 1;
	int w = sizeof(int) << 3;
	int bias = (x >> (w - 1)) & ((1 << 2) - 1);
	return (x + bias) >> 2;
}

int main(void) {
	int x = INT_MAX, y = 17;
	printf("%d %d\n", mul3div4(x), 3 * x / 4);
	printf("%d %d\n", mul3div4(y), 3 * y / 4);
	return 0;
}
```

### 运算结果

```c++
536870911 536870911
12 12
```

## 2.82

```c++
(x < y) == (-x > -y);
```

> #### 否，当 `x = INT_MIN` 时，`-x = INT_MIN`，此时`-x`也是最小的数

```c++
((x + y) << 4) + y - x == 17 * y + 15 * x;
```

> #### 是，如下
>
> ```c++
>   (x + y) << 4 + y - x
> = (x + y) * 16 + y - x
> = 16 * x + 16 * y + y - x
> = 17 * y + 15 * x
> ```

```c++
~x + ~y + 1 == ~(x + y);
```

> #### 是，位级运算如下
>
> ```c++
> ~x + ~y + 1 = -x - 1 - y - 1 + 1 = -x - y - 1
> ~(x + y) = -x - y - 1
> ```

```c++
(ux - uy) == -(unsigned)(y - x);
```

> #### 是，由于数字都是用补码表示，进行运算时不考虑有符号无符号，只在最后转化时才体现有符号无符号，最后隐式强转为有符号数，因此永远为真

```c++
((x >> 2) << 2) <= x;
```

> #### 是，将`x`右移两位再左移两位后，由于左移补充的是`0`，有可能会损失低位的两个`1`，因此得到的值总小于等于原值