# 第三次作业

## 3.58

```assembly
; long decode2(long x, long y, long z)
; x in %rdi, y in %rsi, z in %rdx
decode2:
	subq	%rdx, %rsi	; %rsi -= %rdx
	imul	%rsi, %rdi	; %rdi *= %rsi
	movq	%rsi, %rax	; %rax = %rsi
	salq	$63, %rax	; %rax <<= 63
	sarq	$63, $rax	; %rax >>= 63
	xorq	%rdi, %rax	; %rax ^= %rdi
	ret
```

### 汇编调整

```c
long decode2(%rdi, %rsi, %rdx) {
  %rsi -= %rdx;
  %rdi *= %rsi;
  %rax = %rsi;
  %rax <<= 63;
  %rax >>= 63;
  %rax ^= %rdi;
  return %rax;
}
```

### 翻译为 C 语言

```c
long decode(long x, long y, long z) {
  long tmp = y - z;
  return (tmp * x) ^ (t << 63 >> 63);
}
```

## 3.60

```assembly
; long loop(long x, int n)
; x in %rdi, n in %esi
loop:
	movl	%esi, %ecx	; %ecx = %rsi
	movl	$1, %edx	; %edx = 1
	movl	$0, %eax	; %eax = 0
	jmp	.L2
.L3:
	movq	%rdi, %r8	; %r8 = %rdi
	andq	$rdx, %r8	; %r8 &= %rdx
	or	$r8, %rax	; %rax |= %r8
	salq	%cl, %rdx	; %rdx <<= %cl
.L2:
	testq	%rdx, %rdx	; 条件码 %rdx & %rdx
	jne	.L3		; if %rdx != 0, goto .L2
	rep; ret
```

### 汇编调整

```c
long loop(%rdi, %esi) {
  %ecx = %rsi;
  %edx = 1;
  %eax = 0;
  while (%rdx) {
    %r8 = %rdi;
    %r8 &= %rdx;
    %rax |= %r8;
    %rdx <<= %cl;
  }
}
```

### 因此，得到以下答案

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
    result |= mask & x;
  }
  return result;
}
```

