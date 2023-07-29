# Session 3

## 3.58(*)

```c
long decode2(long x, long y, long z) {
  long t = y - z;
  return (t * x) ^ (t << 63 >> 63);
}
```

## 3.59(**)

```assembly
store_prod:
	movq		%rdx, %rax		; y 移入 %rax 中
	cqto									; 对 y 进行符号扩展，%rdx = y_h，%rax = y_l
	movq		%rsi, %rcx		; x 移入 %rcx 中
	sarq		$63, %rcx			; x 右移 63 位，相当于符号位扩展，%rcx = x_h，%rsi = x_l
	imulq		%rax, %rcx		; %rcx = y_l * x_h
	imulq		%rsi, %rdx		; %rdx = y_h * x_l
	addq		%rdx, %rcx		; %rcx = y_l * x_h + y_h * x_l
	mulq		%rsi					; 无符号乘法 ux * uy，%rdx 保存高位，%rax 保存低位
 	addq		%rcx, %rdx		; 将高位计算结果加到 %rdx
	movq		%rax, (%rdi)	; 保存结果的低64位
	movq		$rdx, 8(%rdi)	; 保存结果的高64位
	ret
```

## 3.60(**)

```c
/*
A.	%rdi -> x
		%esi -> n
		%rax -> result
		%rdx -> mask
B.	result = 0;
		mask = 1;
C.	mask != 0;
D.	mask <<= n & 0xFF;
E.	res |= mask & x;
*/
long loop(long x, int n) {
  long result = 0;
  long mask;
  for (mask = 1; mask != 0; mask = mask << (n & 0x3F)) {
    res |= mask & x;
  }
  return res;
}
```

## 3.61(**)

```c
long cread_alt(long *xp) {
  long t = 0;
  long *p = xp ? xp : &t;
  return *p;
}
```

```assembly
cread_alt:
	movq		$0, %rax
	testq		%rdi, %rdi
	cmovn		%(rdi), %rax
	ret
```

## 3.62(**)

```c
typedef num {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;

long switch3(long *p1, long *p2, mode_t action) {
  long result = 0;
  switch(action) {
    case MODE_A:
      result = *p2;
      action = *p1;
      *p2 = action;
      break;
    case MODE_B:
      result = *p1 + *p2;
      *p1 = result;
      break;
    case MODE_C:
      *p1 = 59;
      result = *p2;
      break;
    case MODE_D:
      result = *p2;
      *p1 = result;
      result = 27;
    case MODE_E:
      result = 27;
      break;
    default:
      result = 12;
  }
  return resulut;
}
```

## 3.63(**)

```c
long switch_prob(long x, long n) {
  long result = x;
  // 60->0
  switch(n) {
    case 60:
    case 62:
      result *= 8;
			break;
    case 63:
      result =>> 3;
      break;
    case 64:
      result = (result << 4) - x;
      x = result;
    case 65:
      x = x * x;
    default:
      result = x + 0x4b;
  }
  return result;
}
```

## 3.64(***)

### A.

> $\& D[i][j] = x_D + L(C \cdot i + j)$
>
> $\& A[i][j][k] = x_A + L(S \cdot T \cdot i + T \cdot j + k)$

### B.

> $L = 8$
>
> $res = (13j + 65i + k) \times 8$
>
> 因此，$T = 13,\ S = 5$
>
> 结合`sizeo(A) = 3640`，解得$R = 7$

## 3.65(*)

```c
void transpose(long A[M][M]) {
  long i, j;
  for (i = 0; i < M; i++) {
    for (j = 0; j < i; j++) {
      long t = A[i][j];
      A[i][j] = A[j][i];
      A[j][i] = t;
    }
  }
}
```

```assembly
; %rcx->t1	%rdx->t2	%rsi->t3	%rax->t4	%rdi->t5
.L6:
	movq		(%rdx), %rcx	; t1 = *t2
	movq		(%rax), %rsi	; t3 = *t4
	movq		%rsi, (%rdx)	; *t2 = t3
	movq		%rcx, (%rax)	; *t4 = t1
	addq		$8, %rdx			; t2 += 8
	addq		$120, %rax		; t4 += 120
	cmpq		%rdi, %rax		; t4 - t5
	jne			.L6						; if t4 - t5 != 0, goto .L6
```

### A.

> %rdx

### B.

> %rax

### C.

> $120 / 8 = 15$

## 3.66(*)

```c
long sum_col(long n, long A[NR(n)][NC(n)], long j) {
  long i;
  long result = 0;
  for (i = 0; i < NR(n); i++) {
    result += A[i][j];
  }
  return result;
}
```

```assembly
; %rdi->n	%rsi->A	%rdx->j
sum_col:
	leaq		1(, %rdi, 4), %r8				; %r8 = 1 + 4 * n 
	leap		(%rdi, %rdi, 2), %rax		; %rax = 3 * n
	movq		%rax, %rdi							; n = 3 * n
	testq		%rax, %rax							; test %rax
	jle			.L4											; if %rax <= 0, goto L4
	salq		$3, %r8									; %r8 <<= 3
	leaq		(%rsi, %rdx, 8), %rcx		; %rcx = A + 8 * j
	movl		$0, %eax								; %rax = 0
	movl		$0, %edx								; %rdx = 0
.L3:
	addq		(%rcx), %rax						; %rax += *%rcx
	addq		$1, %rdx								; %rdx++
	addq		%r8, %rcx								; %rcx += %r8
	cmpq		%rdi, %rdx							; cmp %rdx - %rdi
	jne			.L3											; if %rdx - %rdi != 0, goto .L3
	rep; ret
.L4:
	movl		$0, %eax								; %rax = 0
	ret
```

```c
NR(n) = 3 * n;
NC(n) = 1 + 4 * n;
```

## 3.67(**)

```c
typedef struct {
  long a[2];
  long *p;
} strA;

typedef struct {
  long u[2];
  long q;
} strB;

strB process(strA s) {
  strB r;
  r.u[0] = s.a[1];
  r.u[1] = s.a[0];
  r.q = *s.p;
  return r;
}

long eval(long x, long y, long z) {
  strA s;
  s.a[0] = x;
  s.a[1] = y;
  s.p = &z;
  strB r = process(s);
  return r.u[0] + r.u[1] + r.q;
}
```

```assembly
process:
	movq		%rdi, %rax
	movq		24(%rsp), %rdx
	movq		(%rdx), %rdx
	movq		16(%rsp), %rcx
	movq		%rcx, (%rdi)
	movq		8(%rsp), %rcx
	movq		%rcx, 8(%rdi)
	movq		%rdx, 16(%rdi)
	ret

; %rdi->x	%rsi->y	%rdx->z
eval:
	subq		$104, %rsp
	movq		%rdx, 24(%rsp)
	leap		24(%rsp), %rax
	movq		%rdi, (%rsp)
	movq		%rsi, 8(%rsp)
	movq		%rax, 16(%rsp)
	leaq		64(%rsp), %rdi
	call		process
	movq		72(%rsp), %rax
	addq		64(%rsp), %rax
	addq		80(%rsp), %rax
	addq		$104, %rsp
	ret
```

### A.

> |     栈      |      值      |
> | :---------: | :----------: |
> | `rsp + 104` |              |
> |     ...     |              |
> | `rsp + 64`  |              |
> |     ...     |              |
> | `rsp + 24`  |     `z`      |
> | `rsp + 16`  |  `s.p = &z`  |
> |  `rsp + 8`  | `s.a[1] = y` |
> |    `rsp`    | `s.a[0] = x` |

### B.

> `%rdi->*(%rsp + 64)`

### C.

> 通过 `%rsp +8, +16, +24`

### D.

> `%rdi = %rsp + 64`
>
> `%rsp +64, +72, +80`

### E.

>|            栈             |      值      |
>| :-----------------------: | :----------: |
>|        `rsp + 104`        |              |
>|            ...            |              |
>|        `rsp + 80`         |    `r.q`     |
>|        `rsp + 72`         |   `r.u[1]`   |
>|        `rsp + 64`         |   `r.u[0]`   |
>|            ...            |              |
>|        `rsp + 24`         |     `z`      |
>|        `rsp + 16`         |  `s.p = &z`  |
>|         `rsp + 8`         | `s.a[1] = y` |
>|           `rsp`           | `s.a[0] = x` |
>| `rsp - 8(rsp in process)` |              |
>

### F.

> 结构的值在栈中传递

## 3.68(***)

```c
typedef struct {
  int x[A][B];
  long y;
} str1;

typedef struct {
  char array[B];
  int t;
  short a[A];
  long u;
} str2;

void setVal(str1 *p, str2 *q) {
  long v1 = q->t;
  long v2 = q->u;
  p->y = v1 + v2;
}
```

```assembly
; %rdi->p	%rsi->q
setVal:
	movslq		8(%rsi), %rax			; t1 = q->t 符号拓展
	addq			32(%rsi), %rax		; t1 += q->u
	movq			%rax, 184(%rdi)		; p->y = t1
	ret
```

> 考虑到内存对齐，有如下不等式成立
> $$
> \begin{cases}
> 0 < B \leqslant 8 \\
> 24 < 8 + 4 + 2 \times A \leqslant 32 \\
> 176 < 4 \times A \times B \leqslant 184
> \end{cases}
> \Rightarrow
> \begin{cases}
> 0 < B \leqslant 8 \\
> 6 < A \leqslant 10 \\
> 44 < AB \leqslant 46
> \end{cases}
> \Rightarrow
> \begin{cases}
> A = 9 \\
> B = 5
> \end{cases}
> $$
> 

## 3.69(***)

```c
typedef struct {
  int first;
  a_struct a[CNT];
  int last;
} b_struct;

void test(long i, b_sutrct *bp) {
  int n = bp->first + bp->last;
  a_struct *ap = &bp->a[i];
  ap->x[ap->idx] = n;
}
```

```assembly
; %rdi->i	$rsi->bp
0000000000000000 <test>:
	 0:		8b 8e 20 01 00 00		mov			0x120(%rsi), %ecx					; %ecx = *(rsi + 0x120)
	 6:		03 0e								add			(%rsi), %rcx							; %rcx += bp->first
	 8:		48 8d 04 bf					lea			(%rdi, %rdi, 4), %rax			; %rax = 5 * i
	 c:		48 8d 04 c6					lea			(%rsi, %rax, 8), %rax			; %rax = bp + 40 * i
	10:		48 8b 50 08					mov			0x8(%rax), %rdx						; %rdx = *(bp + 40 * i + 8)
	14:		48 63 c9						movslq	%rcx, %rcx								; %rcx 带符号扩展
	17:		48 89 4c d0 10			mov			%rcx, 0x10(%rax, %rdx, 8) ; *(%rax + 8%rdx + 16) = %rcx
	1c:		48 63 c9						retq
```

```c
// CNT = (288 - 8) / 40 = 7
typedef struct {
  long idx;
  long x[4];
} a_struct;
```

## 3.70(***)

```c
union ele {
  struct {
    long *p;
    long y;
  } e1;
  struct {
    long x;
    union ele *next;
  } e2;
}
```

### A.

```c
e1.p 0		e1.y 8
e2.x 0		e2.next 8
```

### B.

> 16 Bytes

### C.

```assembly
; %rdi->up
proc:
	movq		8(%rdi), %rax		; %rax = *(up + 8)
	movq		(%rax), %rdx		; %rdx = *%rax = *(up->e2.next)
	movq		(%rdx), %rdx		; %rdx = *%rdx = **(up->e2.next) = up->e2.next->e1->p;
	subq		8(%rax), %rdx		; %rdx -= *(%rax + 8) = up->e2.next->e1.y
	movq		%rdx, (%rdi)		; up->e2.x = %rdx
	ret
```

```c
void proc (union ele *up) {
  up->e2.x = *(up->e2.next->e1.p) - up->e2.next.e1.y;
}
```

## 3.71(*)

```c
#include <stdio.h>

#define BUFFERSIZE 15

void good_echo(void) {
  char buff[BUFFERSIZE];
  while (fgets(buff, BUFFERSIZE, stdin)) {
    fprintf(stdout, "%s", buff);
  }
}
int main(void) {
  good_echo();
  return 0;
}
```

## 3.72(**)

```c
#include <alloca.h>

long aframe(long n, long idx, long *q) {
  long i;
  long **p = alloca(n * sizeof(long *));
  p[0] = &i;
  for (i = 1; i < n; i++) {
    p[i] = q;
  }
  return *p[idx];
}
```

```assembly
; %rdi->n	%rsi->idx	%rdx->q
afram:
	pushq		%rbp
	movq		%rsp, %rbp
	subq		$16, %rsp							; allocate space for i
	leaq		30(, %rdi, 8), %rax		; %rax = 8 * n + 30
	andq		$-16, %rax						; %rax &= -16 (末4位置为0)
	subq		%rax, %rsp						; allocate space for array p
	leaq		15(%rsp), %r8					; %r8 = %rsp + 15
	andq		$-16. %r8							; set %r8 to &p[0]
```

### A.

> $s_1 = \%rsp - 16$
>
> $s_2 = s1 - ((30 + 8 \times n) - (30 + 8 \times n) \mod{16})$

### B.

> $p = (s_2 + 15) - ((s_2 + 15) \mod {16})$

### C.

> 记数组结尾为$p_1$
>
> 如果$n = 2n_1$，那么
> $$
> \begin{align}
> s_2 & = s_1 - ((30 + 8 \times n) - (30 + 8 \times n) \mod{16}) \\
> 		& = s_1 - ((30 + 16 \times n_1) - 14) \\
> 		& = s_1 - 16 - 16 \times n_1 \\
> p	& = (s_2 + 15) - ((s_2 + 15) \mod{16}) \\
> 	& = (s_1 - 1 - 16 \times n_1) - (s_1 - 1) \mod{16} \\
> p_1 & = p + 8 \times n \\
> 		& = (s_1 - 1 - 16 \times n _1) - (s_1 - 1) \mod{16} + 16 \times n_1 \\
> 		& = (s_1 - 1) - (s_1 - 16) \mod{16}
> \end{align}
> $$
> 如果$n = 2n_1 + 1$，那么
> $$
> \begin{align}
> s_2 & = s_1 - ((30 + 8 \times n) - (30 + 8 \times n) \mod{16}) \\
> 		& = s_1 - ((30 + 16 \times n_1 + 8) - 6) \\
> 		& = s_1 - 32 - 16 \times n_1 \\
> p	& = (s_2 + 15) - ((s_2 + 15) \mod{16}) \\
> 	& = (s_1 - 17 - 16 \times n_1) - (s_1 - 1) \mod{16} \\
> p_1 & = p + 8 \times n \\
> 		& = (s_1 - 17 - 16 \times n _1) - (s_1 - 1) \mod{16} + 16 \times n_1 + 8 \\
> 		& = (s_1 - 1) - (s_1 - 16) \mod{16} - 8
> \end{align}
> $$
> 设
> $$
> s_1 = 1 + 16k + i,\ k \geqslant 0,\ 0 \leqslant i \leqslant 15
> $$
> 那么
> $$
> \begin{align}
> p_1 & = 16k + i - i \\
> 		& = 16k \\
> s_1 & = 1 + 16k + i \\
> e_1 & = i + 1 \in [1,16] \\ \\
> p_1 & = 16k + i - i - 8 \\
> 		& = 16k - 8 \\
> s_1 & = 1 + 16k + i \\
> e_1 & = i + 9 \in [9, 24]
> \end{align}
> $$
> 因此
>
> |      | $e_1$ |  $s_1$   |
> | :--: | :---: | :------: |
> | Max  |  $1$  | $16k+1$  |
> | Min  | $24$  | $16k+16$ |

### D.

> 保证了数组的起始位置都是 16 的倍数

## 3.73(*)

```c
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range_origin(float x) {
  range_t result;
  if (x < 0) {
    result = NEG;
  } else if (x == 0) {
    result = ZERO;
  } else if (x > 0) {
    result = POS;
  } else {
    result = OTHER;
  }
  return result;
}

range_t find_range(float x) {
  __asm__ volatile(
    "vxorps %xmm1, %xmm1, %xmm1\n\t"
    "vucomiss %xmm0, %xmm1\n\t"
    "ja .LA\n\t"
    "je .LB\n\t"
    "jb .LC\n\t"
    "jp .LD\n\t"
    ".LA:\n\t"
      "movl $0, %eax\n\t"
      "jmp .LE\n\t"
    ".LB:\n\t"
      "movl $1, %eax\n\t"
      "jmp .LE\n\t"
    ".LC:\n\t"
      "movl $2, %eax\n\t"
      "jmp .LE\n\t"
    ".LD:\n\t"
      "movl $3, %eax\n\t"
    ".LE:\n\t"
  );
}

void test() {
  for (short i = SHRT_MIN; i < SHRT_MAX; i++) {
    if (find_range_origin(i) != find_range(i)) {
      printf("Wrong Answer for %d!\n", i);
      return;
    }
  }
  printf("Accept!\n");
}

int main(void) {
  test();
  return 0;
}
```

## 3.74(**)

```c
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range_origin(float x) {
  range_t result;
  if (x < 0) {
    result = NEG;
  } else if (x == 0) {
    result = ZERO;
  } else if (x > 0) {
    result = POS;
  } else {
    result = OTHER;
  }
  return result;
}

range_t find_range(float x) {
  __asm__ volatile(
    "vxorps %xmm1, %xmm1, %xmm1\n\t"
    "movl $0, %eax\n\t"
    "movl $1, %edi\n\t"
    "movl $2, %esi\n\t"
    "movl $3, %edx\n\t"
    "vucomiss %xmm0, %xmm1\n\t"
    "cmovz %edi, %eax\n\t"
    "cmovb %esi, %eax\n\t"
    "cmovp %edx, %eax\n\t"
  );
}

void test() {
  for (short i = SHRT_MIN; i < SHRT_MAX; i++) {
    if (find_range_origin(i) != find_range(i)) {
      printf("Wrong Answer for %d!\n", i);
      return;
    }
  }
  printf("Accept!\n");
}

int main(void) {
  test();
  return 0;
}
```

## 3.75(*)

```c
#include <complex.h>

double c_imag(double complex x) {
  return cimag(x);
}

double c_real(double complex x) {
  return creal(x);
}

double complex c_sub(double complex x, double complex y) {
  return x - y;
}
```

```assembly
c_imag:
	movapd		%xmm1, %xmm0
	ret

c_real:
	rep; ret

c_sub:
	subsd		%xmm2, %xmm0
	subsd		%xmm3, %xmm1
	ret
```

### A.

> `%xmm0` 传送实部
>
> `%xmm1` 传送虚部

### B.

> 返回 `%xmm0, %xmm1`
