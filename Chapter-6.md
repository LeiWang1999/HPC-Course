1. 令$n=2^m$,请写一个子程序计算$x^n=1$的所有根；

```python
input:n
output: results,n
for i = 0,n do
  results[i] = e^{\frac{2\pi i}{n}}
end{for}
```



2. 按照算法13给出的按位倒置排序，请写一个子程序对数组x进行重新排序。

```python
input: reversed_array,n
output: sorted_array,n
bitreverse(n, reversed_array)
sorted_array = reversed_array
```

