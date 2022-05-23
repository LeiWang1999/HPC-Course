1. 假设若把mxn的矩阵A按照循环方式存放在pxq的处理机系统中，在每个处理机$P_{kl}$上所得到的矩阵为$A^{kl}$，请建立矩阵A与矩阵和$A^{kl}$的关系式。

利用矩阵卷帘存储方式，则对于$a_{ij} = a^{jl}_{st}$，有$k=i \% j, l = j \% q, s = i /\ p, t = j /\ q$

2. 假设矩阵A和向量b是按行分块的，请给出并行计算$x^+ = Ax+b$的方法。

矩阵A乘上矩阵x是矩阵与矩阵相乘，则可以使用行行的并行矩阵乘法，或者是行列的矩阵乘法，这里我们假设x也是按行分块的，则对于每一个处理器，都保存着一行x的数据，一行A的数据，一行b的数据，表示成伪代码如下：

```C
// myid 为本处理器号，mpl为后一个处理器号，mml为前一个处理器号
// p 为处理器个数
mpl = （myid + 1） mod p, mml = (myid - 1 + p) mod p 
For i = 0 to p - 1 do
	l = (i+myid) mod p
  tmp = temp + A_l * x
  if i != p - 1, send(x, mml), recv(x, mpl)
end
tmp = tmp + b
```

3. 请分析矩阵乘法的列列分块算法和Cannon算法的复杂性（假设传输长度为N的数据的复杂性为$\alpha+N\beta$,广播的方式按照树型方式进行）;

   列列分块算法的伪代码如下：

   ```c
   mpl = myid + 1 mod p, mm1 = myid - 1 mod p
   for i = 0 to p - 1 do
     l = i + myid mod p
     C = C + A * B_l
   	if i != p - 1, send(a, mm1), recv(A, mp1)
   end{for}
   ```

   其算法的数据交换量为$DTA=2*m*(k-\overline{k})$. 则其数据传输过程的复杂度为$\alpha+DTA*\beta$，单个核心的MAC运算算法复杂度为$\overline{m} * k * \overline{n}$。

   经典的Cannon算法的思想是在同一行中广播A，在同一列中滚动B，该算法的数据传输量为$DTA=m*2*n^2+(m-1)*2*n^2$，其数据传输的复杂度为$\alpha+DTA*\beta$，单个核心的MAC运算算法复杂度为$\overline{m} * k * \overline{n}$。

4. 请用自己的理解给出Cannon算法的描述。

   Cannon算法有两种具体做法，分别为经典Cannon算法和改良的Cannon算法。

   经典Cannon算法的思想如PPT中所示，计算过程为每阶段在同一行之中广播当前计算的A矩阵块，在同一列中循环滚动B矩阵块，两个操作同时进行。

   改良的Cannon算法在开始阶段需要特殊的数据分布操作，分布完成后，在同一行同一列间都是进行滚动操作，同一列间向上滚动B矩阵块。

   ![image-20220523155304214](https://leiblog-imgbed.oss-cn-beijing.aliyuncs.com/img/image-20220523155304214.png)