#include<stdio.h>
#include<math.h>
#define MAXN 50
#define INF 1000
/*
    n作业,M1和M2上加工，先M1后M2，M1上ai时间，M2上bi时间，求所需时间最少
    加工不允许中断，非优先调度
    输入：第一行作业数n，接下来n行，每行2非负整数，分别为ai,bi，输入0结束
    输出：采用最优调度总时间
    ---->解空间为排列树
*/

/*
    作业编号1~n，数组x[]解向量，x[i]表示第i步执行的作业编号，初始时数组x的元素分别为1~n
    最优解向量用bestx[]存储，最优解的最优调度时间用bestf表示
    x={x[1],x[2],...,x[i],...,x[n]}
    f1数组：f1[i]表示第i步执行的作业x[i]在M1上执行完的总时间
    f2数组：f2[i]表示第i步执行的作业x[i]在M2上执行完的总时间，求解最小的f2[n]
    --->第i步执行作业x[i]在M2上需要等待的条件：f2[i-1]>f1；否则不需要等待
    f2[i-1]>f1:需要等待————>f2[i]=f2[i-1]+b[x[i]]
    f2[i-1]≤f1:无需等待————>f2[i]=f1+b[x[i]]
    ∴
    f1 += a[x[i]];
    f2[i] = max(f1,f2[i-1]) + b[x[i]];
    剪枝：
        f2[i]≥bestf:则剪枝，没必要扩展
    进一步剪枝：
        x={x[1],..,x[i]}为已经选择的作业，b时间和为sum，则tot-sum表示所有
        未选择作业的b时间和，有：该调度方案时间和≥f2[i]+tot-sum--->时间下界bound(i)表示
        ∴仅扩展bound(i)<bestf的结点
*/

int n=4;                            //作业数
int f1=0,f2[MAXN]={0};
int bestf=INF;
int bestx[MAXN]={0};
int x[MAXN]={0,1,2,3,4};
int a[MAXN]={0,5,12,4,8};           //M1上的执行时间，不用下标0的元素
int b[MAXN]={0,6,2,14,7};           //M2上的执行时间，不用下标0的元素
int tot=0;

void swap(int *x, int *y) {//只有这种情况才能真正交换，由于未交换成功而导致一直错误
    int temp = *y;
    *y = *x;
    *x = temp;
}

int bound(int i)                    //求结点的下界值
{
    int sum=0;
    for(int j=1;j<=i;j++){          //扫描所有选择的作业
        sum+=b[x[j]];               //累计所有选择作业的b时间
    }
    return f2[i]+tot-sum;           //全部n个作业的b时间和为tot
}

void dfs(int i){                    //从第i层开始搜索
    if(i>n){                        //到达叶结点，产生一种调度方案
        if(f2[n]<bestf){            //找到最优解
            bestf=f2[n];            
            for(int j=1;j<=n;j++){
                bestx[j]=x[j];      //复制解向量
            }
        }
    }
    else{
        for(int j=i;j<=n;j++){      //没到达叶结点，考虑可能的作业
            swap(&x[i],&x[j]);        //全排列，讨论所有的情况
            f1 += a[x[i]];          //选择作业x[i],在M1上执行完的时间
            f2[i]=fmax(f1,f2[i-1])+b[x[i]];
            // printf("%d %d %d\n",i,j,f2[i]);用于检验
            // if(f2[i]<bestf)         //原本的剪枝
            //     dfs(i+1);
            if(bound(i)<bestf)         //改进的剪枝
                dfs(i+1);
            f1 -= a[x[i]];           //回溯
            swap(&x[i],&x[j]);//关键
        }
    }
}

int main(){
    for(int j=1;j<=n;j++){          //扫描所有选择的作业
        tot+=b[j];               //累计所有选择作业的b时间
    }
    dfs(1);
    printf("the best time:%d\n",bestf);
    for(int i=1;i<=n;i++){
        printf("%d ",bestx[i]);
    }
    return 0;
}

//算法分析：该算法解空间为高度为n的排列树，时间复杂度O(n!)