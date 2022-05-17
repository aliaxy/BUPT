# 离散数学 习题解答

对于非课本上习题，在此处给出题目

* [Solution 3](#solution3)
* [Solution 5](#solution5)
* [Solution 6](#solution6)

### Solution.3

* 求下列公式的析取范式和合取范式
  
   ![](http://latex.codecogs.com/svg.latex?((\lnot{A}\lor\lnot{B})\rightarrow(A\leftrightarrow{C})\rightarrow{B}))
  
* 通过求主合取范式的方法，判断下列各对公式是否等价

    ![](http://latex.codecogs.com/svg.latex?\lnot{A}\lor(A\land{B})\lor{C})

  ![](http://latex.codecogs.com/svg.latex?(\lnot{A}\lor{B})\land(B\lor{C})) 

* 通过求主析取范式，求出所有使下列公式为真的赋值

    ![](http://latex.codecogs.com/svg.latex?(A\lor{B})\land(A\rightarrow{C})\land(B\rightarrow{C}))

* P ， Q ， R ， S 四个字母，从中取两个字母，但要满足下述三个条件，问有几种取法，如何取？

  – 如果取 P，则 R 和 S 要取一个

  – Q，R 不能同时取

  – 取 R 则不能取 S

* 张先生手中有代号为 A 、 B 、 C 、 D 、 E 的五种股票，根据当前股市情况及张先生本人的经济需求，需要有若干个股票抛出，但又必须满足如下复杂的要求：

  - （ 1 ）若 A 抛出，则 B 也抛出；

  - （ 2 ） B 和 C 要留一种股票且只能留一种；

  - （ 3 ） C 和 D 要么全抛，要么都不抛；

  - （ 4 ） D 和 E 两种股票中必然有一种或两种要抛出；

  - （ 5 ）若 E 抛出，则 A 、 B 也抛出。

    上述五种条件全部满足，问有几种合理的方案供张先生选择。

### Solution.5

* 构造下面的证明：

  * 前提：![](http://latex.codecogs.com/svg.latex?p\rightarrow(q\rightarrow{r}),{p},{q})

    结论：![](http://latex.codecogs.com/svg.latex?r\lor{s})

  * 前提：![](http://latex.codecogs.com/svg.latex?p\rightarrow{q},\lnot(q\land{r}),r)

    结论：![](http://latex.codecogs.com/svg.latex?\lnot{p})

### Solution.6

* 构造下面推理的证明：

  * 前提：![](http://latex.codecogs.com/svg.latex?\exists{x}F(x)\rightarrow\forall{y}(F(y)\lor{G}(y)\rightarrow{R}(y),\exists{x}F(x)) 

    结论： ![](http://latex.codecogs.com/svg.latex?\exists{x}R(x))

  * 前提：![](http://latex.codecogs.com/svg.latex?\forall{x}{(F(x)\lor{G}(x)},\exists{x}\lnot{G}(x)\lor\lnot{R}(x)) ![](http://latex.codecogs.com/svg.latex?,\forall{x}R(x))

    结论：![](http://latex.codecogs.com/svg.latex?\forall{x}F(x))

  * 有些病人相信所有的医生，但病人都不相信一个骗子

    证明：医生都不是骗子

