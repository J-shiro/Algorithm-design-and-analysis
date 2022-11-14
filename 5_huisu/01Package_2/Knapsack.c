#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<stdlib.h>
#define MAXN 50
/*
    深度优先＋剪枝--->求解0/1背包问题--->使得所选的物品的总重量小于等于W
    左剪枝方式不变，
    右剪枝改为采用上界函数进行右剪枝：bound(i)=tv+r,r表示剩余物品的总价值
    假设当前求出最大价值maxv，若bound(i)≤maxv，则右剪枝，否则继续扩展
    显然r越小，bound(i)越小，剪枝越多，为构造更小的r，将所有物品以单位重量价值递减排列<-关键
*/

int n=4;//4种物品
int W=6;//限制重量为6
int w[]={0,5,3,2,1};    //4个物品重量，不用下标0元素
int v[]={0,4,4,3,1};    //4个物品价值，不用下标0元素

typedef struct wupin{
    int n;//编号
    int w;//重量
    int v;//价值
    int p;//单位重量价值
}wupin;

wupin A[MAXN];

void sortA(wupin* A, int l)//a为数组地址，l为数组长度。
{
    int i, j;
    wupin v;
    //排序主体
    for(i = 1; i <= l; i ++)
        for(j = i+1; j <= l; j ++)
        {
            if(A[i].p < A[j].p)//如前面的比后面的大，则交换。
            {
                v = A[i];
                A[i] = A[j];
                A[j] = v;
            }
        }
}

int x[MAXN];//存放最终解
int maxv;   //存放最优解的价值

int bound(int i,int tw,int tv){//求上界
    i++;                       //从i+1开始到叶子结点
    while(i<=n&&tw+A[i].w<=W){ //若序号为i的物品可以整个放入，满足重量限制
        tw+=A[i].w;
        tv+=A[i].v;
        i++;
    }
    if(i<=n)//在某一个非叶子结点停了下来
        return tv+(W-tw)*A[i].p;//若序号为i的物品不能整个放入
        //选择一部分装进去，剩下重量乘以单位重量价值
    else//到了叶子结点
        return tv;//直接返回tv
}

void dfs(int i,int tw,int tv,int op[]){
    if(i>n)             //找到一个叶子结点
    {
        maxv=tv;//不需要再比较，因为由于上界函数，解只能一直更优
        for(int j=1;j<=n;j++){
            x[j]=op[j];
        }
    }
    else{                   //尚未找完所有物品
        if(tw+A[i].w<=W){
            op[A[i].n]=1;
            dfs(i+1,tw+A[i].w,tv+A[i].v,op);
        }
        if(bound(i,tw,tv)>maxv){
            op[A[i].n]=0;
            dfs(i+1,tw,tv,op);
        }
    }
}

int main(){
    int op[MAXN]={0};
    for(int i=1;i<=n;i++){
        A[i].n=i;
        A[i].v=v[i];
        A[i].w=w[i];
        A[i].p=v[i]/w[i];
    }
    sortA(A,n);
    dfs(1,0,0,op);
    printf("the max value:%d\n",maxv);
    for(int i=1;i<=n;i++){
        printf("%d ",x[i]);
    }
    return 0;
}

//该算法不考虑剪枝时，解空间树有2^(n+1)-1个结点（剪枝的结点个数不确定），所以最坏情况
//算法时间复杂度为O(2^n)