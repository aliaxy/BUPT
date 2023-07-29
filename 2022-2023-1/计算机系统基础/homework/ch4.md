# 第四次作业

## 3.63

```assembly
; long switch_prob(long x, long n)
; x in %rdi, n in %rsi
swithch_prob:
	400590:	48 83 ee 3c						sub		$0x3c, %rsi								; %rsi -= 0x3c 减去，使得从0开始寻址
	400594:	48 83 fe 05						cmp		$0x5, %rsi								; %rsi - 5
	400598: 77 29									ja		4005c3 <switch_prob+0x33> ; if %rsi > 5u, goto 4005c3
	40059a: ff 24 f5 f8 06 40 00	jmpq	*0x4006f8(, %rsi, 8)			; 跳转到表格进行下一步
	4005a1: 48 8d 04 fd 00 00 00	lea		0x0(, %rdi, 8), %rax			; %rax = %rdi * 8
	4005a8: 00
	4005a9:	c3										retq
	4005aa:	48 89 f8							mov		%rdi, %rax					; %rax = %rdi
	4005ad: 48 c1 f8 03						sar		$0x3, %rax					; %rax >>= 3
	4005b1:	c3										retq											; return
	4005b2:	48 89 f8							mov		%rdi, %rax					; %rax = %rdi
	4005b5:	48 c1 e0 04						shl		$0x4, %rax					; %rax <<= 4
	4005b9:	48 29 f8							sub		%rdi, %rax					; %rax -= %rdi
	4005bc:	48 89 c7							mov		%rax, %rdi					; %rdi = %rax
	4005bf:	48 0f af ff						imul	%rdi, %rdi					; %rdi *= %rdi
	4005c3:	48 8d 47 4b						lea		0x4b(%rdi), %rax		; %rax = %rdi + 0x4b
	4005c7:	c3										retq

0x4006f8:		0x00000000004005a1	0x00000000004005c3		; 0 1
0x400708:		0x00000000004005a1	0x00000000004005aa		; 2 3
0x400718:		0x00000000004005b2	0x00000000004005bf		; 4 5
```

> 根据跳转表格，写出`switch`语句的主要部分，且`case`需要加上60的偏移量
>
> ```c
> switch {
>   case 60:
>   case 62:
>     /* */
>   case 63:
>   	/* */
>   case 64:
>     /* */
>   case 65:
>     /* */
>   default:
>     /* */
> }
> ```
>
> 继续看汇编代码，
>
> * 对于0和2，跳转到`4005a1`处，执行一行语句返回
> * 对于1，跳转到`4005c3`处，执行一行语句返回
> * 对于3，跳转到`4005aa`处，执行两行返回
> * 对于5，跳转到`4005bf`处，其接下来执行了1所执行的语句，推测可能没有`break`语句
> * 对于4，跳转到`4005b2`处，发现其接下来执行了5所执行的语句，因此推出其没有`break`语句实现
> * 因此，对于1来说，因为与`switch`语句最后或者`default`的部分
>
> 结合上述，得到完整的函数体
>
> ```c
> long switch_prob(long x, long n) {
>   long result = x;
>   // 60->0
>   switch (n) {
>     case 60:
>     case 62:
>       result *= 8;
>       break;
>     case 63:
>       result >>= 3;
>       break;
>     case 64:
>       result = (result << 4) - x;
>       x = result; // 无 break 语句
>     case 65:
>       x = x * x;  // 无 break 语句
>     default:
>       result = x + 0x4b;
>   }
>   return result;
> }
> ```

## 3.64

```c
long A[R][S][T];

long store_ele(long i, long j, long k, long *dest) {
  *dest = A[i][j][k];
  return sizeof(A);
}
```

```assembly
; i in %rdi, j in %rsi, k in %rdx, dest in %rcx
store_ele:
	leaq		(%rsi, %rsi, 2), %rax		; %rax = %rsi + 2 * %rsi = 3 * %rsi
	leaq		(%rsi, %rax, 4), %rax		; %rax = %rax * 4 + %rsi = 13 * %rsi
	movq		%rdi, %rsi							; %rsi = %rdi
	salq		$6, %rsi								; %rsi <<= 6
	addq		%rsi, %rdi							; %rdi += %rsi
	addq		%rax, %rdi							; %rdi += %rax
	addq		%rdi, %rdx							; %rdx += %rdi
	movq		A(, %rdx, 8), %rax			; %rax = *(A + 8 * %rdx)
	movq		%rax, (%rcx)						; *(%rcx) = %rax
	movl		$3640, %eax							; %eax = 3640
	ret
```

### A.

> $$
> \& A[i][j][k] = x_A + L(S\cdot T \cdot i + T \cdot j + k)
> $$
>
### B.
> 对汇编代码进行解释后，发现在最后一行直接给返回值赋值了一个立即数`3640`，因此`sizeof(A) = 3640`，即
>
> `R * S * T = 3640`
>
> 最后得到的`A[i][j][k]`，是由`%rax = *(A + 8 * %rdx)`得到的，而经过分析，此时
>
> `%rdx = (%rdi << 6) + %rdi + 13 * %rsi + %rdx = 65 * i + 13 * j + k`
>
> 结合公式，有`T = 13, S = 5`
>
> 并且由`sizeof(A) = 3640`，得到`R = 3640 / 8 / 13 / 5 = 7`
>
> 因此，$S = 5,\ T = 13,\ R = 7$

## 3.66

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
; n in %rdi, A in	%rsi,	j in %rdx
sum_col:
	leaq		1(, %rdi, 4), %r8				; %r8 = 1 + 4 * %rdi
	leap		(%rdi, %rdi, 2), %rax		; %rax = 3 * %rdi
	movq		%rax, %rdi							; %rdi = %rax
	testq		%rax, %rax							; test %rax
	jle			.L4											; if %rax <= 0, goto L4
	salq		$3, %r8									; %r8 <<= 3
	leaq		(%rsi, %rdx, 8), %rcx		; %rcx = %rsi + 8 * %rdx
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

> 观察汇编代码，在`.L3`这个循环结构中,有
>
> `i in %rdx, ((1 + 4 * n) * 8) in %r8`，`%rcx`代表着需要加和元素的指针，
>
> 发现每次循环`i++`,而`%rcx += %r8`，因此得到每一行有`4 * n + 1`个元素，即`NC(n) = 4 * n + 1`
>
> 继续观察，循环的结束条件是`%rdx != %rdx`，汇编第三行得到`%rdi = 3 * n  `
>
> 故循环总共执行了`3 * n`次，这代表矩阵的行数，即`NR(n) = 3 * n`
>
> 综上，`NR(n) = 3 * n, NC(n) = 4 * n + 1`

## 3.69

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

### A.

> 在获取`bp->last`时，首地址增加了`0x120`，`int`对齐之后占8个字节,故这些空间`-8`应为`a_struct a[CNT]`所占用的空间，又因为在`a_struct a`内部的数组寻址，是`40 * i`，因此每个结构体的大小为`40`，故
>
> `CNT = (288 - 8) / 40 = 7`

### B.

> 汇编代码对`ap->x[ap->idx]`赋值的时候，`%rax + 8(%rdx + 2)`
>
> `idx`是`a[i]`第一个元素，占`8`个字节，`movslq`将`int`转成`long`，说明`x`是`long`数组x的个数为`(40 - 8 ) / 8 = 4`
>
> ```c
> typedef struct {
>   long idx;
>   long x[4];
> } a_struct;
> ```