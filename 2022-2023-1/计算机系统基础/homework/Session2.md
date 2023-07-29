# 第二章

## 2.55

```c
#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%.2x", start[i]);
    }
    printf("\n");
}
int main(void) {
    int num = 0x12345;
    show_bytes((byte_pointer)&num, sizeof(int));
    return 0;
}
```

> `45230100`

## 2.56

```c
#include <stdio.h>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start,size_t len){
    for(size_t i = 0; i < len; i++){
        printf("%.2x",start[i]);
    }
    printf("\n");
}

int main(void) {
    int num = 114514;
    show_bytes((byte_pointer)&num,sizeof(int));
}
```

## 2.57

```c
#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%.2x", start[i]);
    }
    printf("\n");
}

void show_short(short x) {
    show_bytes((byte_pointer)&x, sizeof(short));
}

void show_long(long x) {
    show_bytes((byte_pointer)&x, sizeof(long));
}

void show_double(double x) {
    show_bytes((byte_pointer)&x, sizeof(double));
}

int main(void) {
    double num = 114514.1919810;
    short x = (short)num;
    long y = (long)num;
    show_short(x);
    show_long(y);
    show_double(num);
    return 0;
}
```

## 2.58

```c
#include <stdio.h>

typedef unsigned char *btye_pointer;

int is_little_endian() {
    int test = 0x11;
    btye_pointer p = (btye_pointer)&test;
    if (p[0] == 0x11)
        return 1;
    return 0;
}

int main(void) {
    if (is_little_endian()) {
        printf("The machine is little endian\n");
    } else {
        printf("The machine is big endian\n");
    }
    return 0;
}
```

## 2.59

```c
#include <stdio.h>

size_t numCombine(size_t x, size_t y) {
    size_t mask = 0xff;
    size_t res = (x & mask) | (y & ~mask);
    return res;
}

int main(void) {
    size_t x = 0x89ABCDEF;
    size_t y = 0x76543210;
    printf("%x\n", numCombine(x, y));
    return 0;
}
```

## 2.60

```c
#include <stdio.h>

size_t replace_byte(unsigned x, int i, unsigned char b) {
    size_t mask = ((unsigned)0xff) << (i << 3);
    return (x & ~mask) | ((unsigned)b << (i << 3));
}

int main(void) {
    printf("%x\n", replace_byte(0x12345678, 2, 0xAB));
    printf("%x\n", replace_byte(0x12345678, 0, 0xAB));
    return 0;
}
```

## 2.61

* ```c
  !~x
  ```

* ```c
  !x
  ```

* ```c
  !~(x | ~0xff)
  ```

* ```c
  !((x >> ((sizeof(int) - 1) << 3)) & 0xff)
  ```

## 2.62

```c
#include <stdio.h>

int int_shift_are_arithmetic() {
    int test = -1;
    return !(test ^ (test >> 1));
}

int main(void) {
    printf("%d\n", int_shift_are_arithmetic());
    return 0;
}
```

## 2.63

```c
#include <stdio.h>

unsigned srl(unsigned x, int k) {
    unsigned xsra = (int)x >> k;
    int w = sizeof(int) << 3;
    int mask = (int)-1 << (w - k);
    return xsra & ~mask;
}

int sra(int x, int k) {
    int xsrl = (unsigned)x >> k;
    int w = sizeof(int) << 3;
    int mask = (int)-1 << (w - k);
    int mmask = (int)-1 << (w - 1);
    mask = mask & (!(mmask & x) - 1);
    return xsrl | mask;
}

int main(void) {
    unsigned testu = 0x12345678;
    int testi = 0x12345678;
    printf("%x\n", srl(testu, 2));
    printf("%x\n", sra(testi, 2));

    return 0;
}
```

## 2.64

```c
#include <stdio.h>

int any_odd_one(unsigned x) {
    return x & 0xAAAAAAAA != 0;
}

int main(void) {
    unsigned test = 0xAA11;
    printf("%d\n", any_odd_one(test));

    return 0;
}
```

## 2.65

```c
#include <stdio.h>

int odd_ones(unsigned x) {
    x = x ^ (x >> 16);
    x = x ^ (x >> 8);
    x = x ^ (x >> 4);
    x = x ^ (x >> 2);
    x = x ^ (x >> 1);
    return x & 0x1;
}

int main(void) {
    unsigned test1 = 0x10100001;
    unsigned test2 = 0x00001010;
    printf("%d\n", odd_ones(test1));
    printf("%d\n", odd_ones(test2));

    return 0;
}
```

## 2.66

```c
#include <stdio.h>

int leftmost_one(unsigned x) {
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return (x >> 1) + (x && 1);
}

int main(void) {
    unsigned test = 0x6600;
    printf("%x\n", leftmost_one(test));

    return 0;
}
```

### P67

* ```
  32位机器最多只能移位31位，否则位“未定义”
  ```

* ```c
  #include <stdio.h>
  #include <assert.h>
  
  int int_size_is_32() {
      int set_mab = 1 << 31;
      int beyond_msb = set_mab << 1;
      return set_mab && !beyond_msb;
  }
  
  int int_size_is_32_for_16() {
      int set_mab = 1 << 15 << 15 << 1;
      int beyond_msb = set_mab << 1;
      return set_mab && !beyond_msb;
  }
  
  int main(void) {
      assert(int_size_is_32());
      assert(int_size_is_32_for_16());
      return 0;
  }
  ```

### P68

```c
#include <stdio.h>

int lower_one_mask(int n) {
    int w = sizeof(int) << 3;
    return (unsigned)-1 >> (w - n);
}

int main(void) {
    printf("%x\n", lower_one_mask(17));
    return 0;
}
```

### P69

```c
#include <stdio.h>

unsigned rotate_left(unsigned x, int n) {
    int w = sizeof(int) << 3;
    return (x << n) | (x >> (w - n - 1) >> 1);
}

int main(void) {
    printf("%x\n", rotate_left(0x12345678, 4));
    printf("%x\n", rotate_left(0x12345678 ,20));
    return 0;
}
```

### P70

```c
#include <stdio.h>

int fits_bits(int x, int n) {
    int t = x >> (n - 1);
    return !(t && ~t);
}

int main(void) {
    printf("%d\n", fits_bits(114514, 19));
    return 0;
}
```

### P71

* ```c
  不能从word中提取一个负值的byte
  ```
  
* ```c
  #include <stdio.h>
  
  typedef unsigned packed_t;
  
  int xbyte(packed_t word, int btyenum) {
      int w = sizeof(unsigned);
      int left = (w - btyenum - 1) << 3;
      int right = (w - 1) << 3;
      return (int)(word << left >> right);
  }
  
  int main(void) {
      printf("%d\n", xbyte(-1, 4));
      return 0;
  }
  ```

### P72

* ```c
  sizeof(val)为unsigned，与maxbytes(int)运算时将全部转换为unsigned类型进行运算，于是maxbytes-sizeof(val)>=0永真
  ```

* ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  void copy_int(int val, void *buf, int maxbytes) {
  	if (maxbytes - (int)sizeof(val) >= 0) {
  		memcpy(buf, (void *)&val, sizeof(val));
  	}
  }
  
  int main(void) {
      int maxbytes = 114, val = 514;
      void *buff = malloc(maxbytes);
      copy_int(val, buff, maxbytes);
      return 0;
  }
  ```

### P73

```c
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int saturating_add(int x, int y) {
    int sum = x + y;
    int mask = INT_MIN;
    bool pos_over = !(x & mask) && !(y & mask) && (sum & mask);
    bool neg_over = (x & mask) && (y & mask) && !(sum & mask);
    (pos_over && (sum = INT_MAX)) || (neg_over && (sum = INT_MIN));
    return sum;
}

int main(void) {
    printf("%x\n", saturating_add(INT_MAX, 2));
    printf("%x\n", saturating_add(INT_MIN, -2));
    return 0;
}
```

### P74

```c
#include <stdio.h>
#include <limits.h>

int tsub_ok(int x, int y) {
    int sub = x - y;
    int pos_ober = x >= 0 && y <= 0 && sub <= 0;
    int neg_over = x < 0 && y > 0 && sub >= 0;
    return !(pos_ober || neg_over);
}

int main(void) {
    printf("%d\n", tsub_ok(114, 514));
    printf("%d\n", tsub_ok(INT_MAX, INT_MIN));
    printf("%d\n", tsub_ok(INT_MIN, INT_MAX));

    return 0;
}
```

### P75

```c
#include <stdio.h>                                                                     #include <inttypes.h>

int signed_high_prod(int x, int y) {
    int64_t mul = (int64_t)x * y;
    return mul >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
    int sign_x = x >> 31;
    int sign_x= y >> 31;
    int signed_prod = signed_high_prod(x, y);
    return signed_prod + x * sign_y + y * sign_x;
}

unsigned test(unsigned x, unsigned y) {
    uint64_t mul = (uint64_t)x * y;
    return mul >> 32;
}

int main(void) {
    printf("%d\n", test(114514, 1919810));
    printf("%d\n", unsigned_high_prod(114514, 1919810));
    return 0;
}
```

### P76

```c
#include <stdlib.h>

void *calloc(size_t nmemb, size_t size) {
    if (nmemb == 0 || size == 0) {
        return NULL;
    }
    size_t target = nmemb * size;
    if (nmemb != target / size) {
        return NULL;
    }
    void *p = malloc(target);
    if (p == NULL) {
        return NULL;
    }
    memset(p, 0, target);
    return p;
}

int main(void) {
    printf("%p\n", calloc(INT_MAX, INT_MAX));
    printf("%p\n", calloc INT_MAX
    return 0;
}
```

### P77

* ```c
  17 : (x << 4) + x
  ```

* ```c
  -7 : x - (x << 3)
  ```
* ```c
  60 : (x << 6) - (x << 2)
  ```
* ```c
  -112 : (x << 4) - (x << 7)
  ```

### P78

```c
#include <stdio.h>                                                         

int divide_power2(int x, int k) {
    int w = sizeof(int) << 3;
    int bias = (x >> (w - 1)) & ((1 << k) - 1);
    x += bias;
    return x >> k;
}

int main(void) {
    printf("%d\n", divide_power2(124, 5));
    return 0;
}
```

