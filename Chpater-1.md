1. 在主程序中定义了矩阵A和B（比如C语言，A\[50\]\[67\]，B\[73\]\[49\]），请写一个通用程序完成矩阵相加，使得对于任何mxn的子矩阵A和子矩阵B相加都能调用该子程序，用C或Fortran语言（比如matradd(m,n,...A,...B,,C)）.

```C++
template <class T>
void matradd(size_t m, size_t n, T *A, T *B, T *C ){
  	for(size_t i = 0; i < m; ++i){
      for(size_t j = 0; j < n; ++j){
      		C[i][j] = A[i][j] + B[i][j]
    	}
    }
}
```

2. 设多项式$P_n(x) = a_nx^n+a_{n-1}x^{n-1}+...+a_1x+a_0$，请给出计算$P_n(x_0)$的方法并写出计算它的子程序。

```c++
template <class T>
T polynomialCaculate(size_t n, T x, T *a){
  T res = 0;
  for(int i = 0; i <= n; ++i){
    res += a[i] * pow(x,i);
  }
  return res;
}
```

3. 对任意给定的x和n，用算法1写一个程序计算$x^n$

```C++
double myPow(double x, int n){
    double res = 1.0;
    for(int i = n;i!=0;i/=2)	//贡献初始值为x
    {
        if(i % 2 == 1)			//如果N的二进制最低位为1，则需要计入贡献
        {
            res *= x;	
        }
        x *=x ;					//将贡献不断平方
    }
    return n < 0?1/res:res;
}
```

