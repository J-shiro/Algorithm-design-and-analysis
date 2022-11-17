s# 第一章

**程序设计=数据结构+算法**

算法：**若干条指令组成的有穷序列，有穷规则的集合**

性质：有限性、确定性、输入、输出

算法复杂性：算法运行时所需资源的量

**渐近上界记号O**：f(n)=O(g(n))≤g(n)

**渐近下界记号Ω**：f(n)=Ω(g(n))≥g(n)

**高阶记号o**：f(n)=o(g(n))<g(n)

**同阶记号θ**：f(n)=θ(g(n))=g(n)



P问题：问题规模为n，在n的多项式内解决

NP问题：在多项式时间内验证

# 第二章

求时间复杂度：递推迭代、主定理（用于分治法）

## 二分搜索

递推公式：T(n)=T(n/2)+1

==时间复杂度：O(logn)==

## 大整数乘法

$$
T(n)=
\begin{cases} 
3T(n/2)+kn\quad(n>1) \\
c\quad\quad\quad\quad\quad\quad\quad(n=1)
\end{cases}
$$

==时间复杂度O(n<sup>log3</sup>)==

## 矩阵乘法

$$
T(n)=
\begin{cases} 
7T(n/2)+an^2\quad(n>2) \\
b\quad\quad\quad\quad\quad\quad\quad(n≤2)
\end{cases}
$$

==时间复杂度O(n<sup>log7</sup>)==

## 棋盘覆盖

$$
T(n)=
\begin{cases} 
4T(n/2)+O(1)\quad(n>1) \\
O(1)\quad\quad\quad\quad\quad\quad\quad(n=1)
\end{cases}
$$

==时间复杂度：O(n<sup>2</sup>)==

## 合并排序

$$
T(n)=
\begin{cases} 
2T(n/2)+O(n)\quad(n>1) \\
O(1)\quad\quad\quad\quad\quad\quad\quad(n=1)
\end{cases}
$$

==时间复杂度：O(nlogn)==

==最好时间复杂度：O(nlogn)==

==最坏时间复杂度：O(nlogn)==

## 快速排序

最坏情况：T(n)=O(n<sup>2</sup>)  

$$
T(n)=
\begin{cases} 
T(n-1)+O(n)\quad(n>1) \\
O(1)\quad\quad\quad\quad\quad\quad\quad(n=1)
\end{cases}
$$
  
最好情况：T(n)=O(nlogn)  

$$
T(n)=
\begin{cases} 
2T(n/2)+O(n)\quad(n>1) \\
O(1)\quad\quad\quad\quad\quad\quad\quad(n=1)
\end{cases}
$$  

平均情况：O(nlogn)

## 线性时间选择

**一般选择问题可在O(n)时间内得到解决**

==时间复杂度：O(n)==

## 最接近点对

一维：  

$$
T(n)=
\begin{cases} 
2T(n/2)+O(n)\quad(n>4) \\
O(1)\quad\quad\quad\quad\quad\quad\quad(n=4)
\end{cases}
$$  

==时间复杂度：O(nlogn)==

二维：  
  
$$
T(n)=
\begin{cases} 
2T(n/2)+O(n)\quad(n>4) \\
O(1)\quad\quad\quad\quad\quad\quad\quad(n≤4)
\end{cases}
$$  
  
==时间复杂度：O(nlogn)==

# 第三章

动态规划：最优子结构性质、重叠子问题性质

最优子结构性质证明：反证法

## 矩阵连乘


$$
{m[i][j]}=
\begin{cases} 
0\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad(i=j) \\
\min\limits_{i<=k<j}\{m[i][k]+m[k+1][j]+p_{i-1}p_kp_j\}\quad\quad i≠j
\end{cases}
$$

==时间复杂度：O(n<sup>3</sup>)==

## 最长公共子序列

$$
{m[i][j]}=
\begin{cases} 
0\quad\quad\quad\quad\quad\quad\quad\quad\quad\quad(i=0,j=0) \\
c[i-1][j-1]+1\quad\quad\quad i,j>0;x_i=y_i \\
\max\{c[i][j-1],c[i-1][j]\}\quad\quad i≠j
\end{cases}
$$

==时间复杂度：O(m*n)==

## 最大字段和

b[j]=max{ b[j-1]+a[j] , a[j] }

==时间复杂度：O(n)==

## 凸多边形最优三角剖分

$$
{t[i][j]}=
\begin{cases}
0 \quad\quad\quad i=j\\
\min\limits_{i<=k<j}\{t[i][k]+t[k+1][j]+w(v_{i-1}v_kv_j)\}\quad i<j
\end{cases}
$$

==时间复杂度O(n<sup>3</sup>)==

## 流水作业调度

$$
T(S,t)=\min\limits_{1<=i<=n}\{a_i+T(S-\{i\},b_i+max\{t-a_i,0\}\}
$$

==时间复杂度：O(2<sup>n</sup>)==

**Johnson法则：min{b~i~ , a~j~} ≥ min{b~j~ , a~i~}**

**1.a<=b构成一个作业子集N1**

**2.a>b构成一个作业子集N2**

**3.N1按照ai升序排列得到N1'，N2按照bi降序排列得N2'**

**4.先N1'，后N2'**

==时间复杂度：O(nlogn)==

## 0-1背包

$$
m\left(i,j\right)=
\begin{cases}
max\{m(i+1,j),m(i+1,j-w_i)+v_i\} \quad\quad\quad j>=w_i\\
m(i+1,j)\quad 0<=j<w_i
\end{cases}
$$

==时间复杂度：O(nc)==

## TSP

$$
T(v_i,V)=\min\limits_{v_j∈V}(d_{ij}+T(v_j,V-\{v_j\}))
$$

==时间复杂度：O(n2<sup>n</sup>)==

# 第四章

贪心算法：贪心选择性质、最优子结构性质

最优子结构性质证明：

由问题T，和子问题T‘ ，根据问题和子问题最优值关系证明，

T和T’ 最优值递归关系：B(T)=B(T')+f(x)，通过反证法证出矛盾

## 活动安排

当 s<sub>i</sub> ≥ f<sub>j</sub> 或 s<sub>j</sub> ≥ f<sub>i</sub> 时，活动i与活动j相容，活动i占用[ s<sub>i</sub> , f<sub>i</sub> )，升序排列活

动完成时间

==时间复杂度：O(nlogn)==

交换论证法，证明活动安排问题

**1.贪心选择策略为：选择结束时间最早的活动**

**2.给出一个最优解A，第一个活动为k，A不一定用贪心法得到，有任意性**

**3.若k=1，A的第一个活动为贪心选择的第一个活动，同贪心选择相同，即A是一个以贪心选择开始的最优解**

**若k≠1，用贪心选择出的第一个活动交换A的第一个活动，得到B，B=A-{k}+{1}**

接着证明B不比A差，A最优则B也最优

 **3.1.证明B中活动相容（交换后新解符合约束）**

 **3.2.证明B中活动数不少于A（交换后新解最优值比较）B与A活动数相同**

## 一般背包

==时间复杂度：O(nlogn)==

## 最优装载

==时间复杂度：O(nlogn)==

## 哈夫曼编码

==时间复杂度：O(nlogn)==

## 多机调度

n≤m==时间复杂度：O(1)==

n>m==时间复杂度：O(nlogn)==

# 第五章

深度优先DFS

子集树:O(2<sup>n</sup>)

```c++
void backtrack(int t){
	if(t>n) output(x);
	else{
		for(int i=0;i<=n;i++){
			x[t]=i;
			if(legal(t))
				backtrack(t+1);
		}
	}
}
```

排列树:O(n!)

```c++
void backtrack(int t){
	if(t>n) output(x);
	else{
		for(int i=t;i<=n;i++){
			swap(x[t],x[i]);
			if(legal(t))
				backtrack(t+1);
			swap(x[t],x[i]);
		}
	}
}
```

算法框架：解向量、约束条件、解空间、状态空间树、目标函数与最优值

## n皇后

排列树

## 0-1背包

子集树

约束函数：cw+w[i]<=c (左分支)

上界函数bound：bound(i+1)>bestp (右分支)

bound:计算从物品i开始剩余物品总价值+当前价值（上界）**相关单位重量**

## 最大团

子集树

ok: 进入左子树，i与j相连

cn+n-i>bestn: 进入右子树

==时间复杂度：O(n2<sup>n</sup>)==

## m找色

m叉树，子集树特殊情况

==时间复杂度：O(nm<sup>n</sup>)==

## TSP

总路径数：对称情况=**(n-1)!/2**，非对称情况=**(n-1)!**

## 最优装载

子集树，完全二叉树

约束函数：cw+w[i]<=c (左剪枝)

​				   cw+r>bestw (右剪枝)

==时间复杂度：O(2<sup>n</sup>)==

## 批处理作业调度

排列树

`f1=f1+m[x[j]][1]`

`f2[i]=max(f2[i-1],f1)+m[x[j]][2]`

==时间复杂度：O(n!)==

# 第六章

队列式(FIFO)分支限界法：先进先出

优先队列式分支限界法：优先级

广度优先BFS

算法框架：解空间树、解向量、约束条件、解空间、状态空间树、搜索方式、目标函数与最优解、剪枝

## 0-1背包

 完全二叉树，n，结点个数：2<sup>n</sup>-1，叶子结点个数：2<sup>n-1</sup>

## 装载

约束函数：Ew+w[i]<=c

限界函数：Ew+r>bestw
