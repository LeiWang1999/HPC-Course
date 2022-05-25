1. 如果矩阵是按照列循环方式存放在处理机中的，请问是否可以设计一个并行计算Gauss-Seidal的方法。

记$s_i = \sum^{n}_{j=i+1} a_{ij}x_{j}^{(0)},  i = 1,...,n-1, s_n = 0$。

则有

```
k=0
i=myid
for j=1,n do
	recv(j, a[j][j]x[j][k+1])
	s[i] = s[i] + a[i][j]x[j]
end{for}
||x[k+1] - x[k]||_2 < e*||xxxxx
```

![image-20220524205945688](https://leiblog-imgbed.oss-cn-beijing.aliyuncs.com/img/image-20220524205945688.png)



2. 请用自己的理解，对三角矩阵方程组的并行求解方法进行描述和解释

https://blog.csdn.net/qq_45887327/article/details/105901459

