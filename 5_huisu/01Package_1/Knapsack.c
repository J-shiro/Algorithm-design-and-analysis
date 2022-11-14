#include<stdio.h>
#define MAXN 50
/*
    深度优先＋剪枝--->求解0/1背包问题--->必须使得所选的物品的总重量恰好为W
    w[1..n]重量，v[1..n]价值，x[1..n]数组存放最优解，每个元素取0或1
    解空间是一个子集树
    对第i层上某个分枝结点：tw:当前总重量,tv:当前总价值,op:记录一个临时解向量
    i:                            dfs(i,,tw,tv,op)
                选择第i个物品                          不选择第i个物品
                op[i]=1,                              op[i]=0,        
                tw=tw+w[i],                           tw不变,
                tv=tv+v[i],                           tv不变,   

    i+1:        dfs(i+1,tw,tv,op)                     dfs(i+1,tw,tv,op)

    到了叶子结点表示已经对n个物品做出了决策，对所有叶子结点比较求出满足tw==W的最大maxv，对应的最优解op存放在x中
*/

int n=4;//4种物品
int W=6;//限制重量为6
int w[]={0,5,3,2,1};    //4个物品重量，不用下标0元素
int v[]={0,4,4,3,1};    //4个物品价值，不用下标0元素

int x[MAXN];//存放最终解
int maxv;   //存放最优解的价值

void dfs(int i,int tw,int tv,int op[]){         //未剪枝的情况
    if(i>n)             //找到一个叶子结点
    {
        if(tw==W&&tv>maxv){
            maxv=tv;
            for(int j=1;j<=n;j++){
                x[j]=op[j];
            }
        }
    }
    else{                   //尚未找完所有物品
        op[i]=1;            //选取第i个物品
        dfs(i+1,tw+w[i],tv+v[i],op);
        op[i]=0;            //不选取第i个物品，回溯
        dfs(i+1,tw,tv,op);
    }
}

void dfs_gai(int i,int tw,int tv,int rw,int op[]){         //剪枝情况，rw初始为所有物品重量和
    int j;
    if(i>n)             //找到一个叶子结点
    {
        if(tw==W&&tv>maxv){
            maxv=tv;
            for(j=1;j<=n;j++){
                x[j]=op[j];
            }
        }
    }
    else{                   //尚未找完所有物品
        //若加入物品后重量比总重量还要大，不满足条件则可以不扩展这样的结点
        if(tw+w[i]<=W){         //左孩子结点剪枝
            op[i]=1;            //选取第i个物品
            dfs_gai(i+1,tw+w[i],tv+v[i],rw-w[i],op);
        }
        //若tw+rw-w[i]<W,说明即使将所有后面物品选择重量也不能达到W所以可以不扩展这样的结点
        if(tw+rw-w[i]>=W){      //右孩子结点剪枝                    
            op[i]=0;            //不选取第i个物品，回溯
            dfs_gai(i+1,tw,tv,rw-w[i],op);
        }
    }
}

int main(){
    int op[MAXN]={0};
    int rw=0;
    for(int i=1;i<=n;i++){
        rw += w[i];
    }
    dfs_gai(1,0,0,rw,op);
    printf("the max value:%d\n",maxv);
    for(int i=1;i<=n;i++){
        printf("%d ",x[i]);
    }
    return 0;
}

//该算法不考虑剪枝时，解空间树有2^(n+1)-1个结点（剪枝的结点个数不确定），所以最坏情况
//算法时间复杂度为O(2^n)