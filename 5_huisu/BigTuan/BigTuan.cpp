#include <iostream>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

/*
    最大团：从无向图的顶点集中选出k个并且
    k个顶点之间任意两点之间都相邻（完全图），最大的k是最大团
    -约束函数 顶点i到已选入的顶点集中每一个顶点都有边相连。
    -限界函数 有足够多的可选择顶点使得算法有可能在右子树中找到更大的团
    第一行输入图的顶点数n
    第二行到第n+1行输入图的邻接矩阵
*/

/*
    5
    0 1 0 1 1
    1 0 1 0 1
    0 1 0 0 1
    1 0 0 0 1
    1 1 1 1 0

    3
    {1,2,5}、{1,4,5}和{2,3,5}
*/

int n;                  //有n个结点
int m[100][100];        //邻接矩阵
int count=0;            //算最大团里的结点个数
int bestcount=0;        //最大团里的结点个数当前最优值
int x[100];             //x[i]=1选择第i结点
int bestx[100];         //最大团里的解向量
void dfs(int i)
{
    int j;
    if(i>n)//到叶子结点
    {
        bestcount=count;
        for(j=1;j<=n;j++)
        {
            bestx[j]=x[j];
        }
    }
    else
    {
        int ok=1;                       //ok=1则遍历左子树,选择i
        for(j=1;j<=n;j++)
        {
            if((x[j]==1)&&(m[i][j]==0)) //(x[j]==1)说明j被选择
            {                           //m[i][j]==0说明i，j两者不相连，则不能把i加入点集
                ok=0;
                break;
            }
        }
        if(ok==1)//说明第i个点可以被加进去,遍历左子树
        {
            x[i]=1;
            count++;
            dfs(i+1);
            count--;//回溯到原点
            x[i]=0;
        }
        else//说明第i个点不能被加进去,遍历右子树
        {
            x[i]=0;
            if(count+n-i>bestcount)         //剪枝若当前count不选择i加上剩余的结点数大于bestcount
            {                               //则有可能存在更优解，扩展
                dfs(i+1);
            }
        }
    }
 
}
int main()
{
    int i,j;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            cin>>m[i][j];//初始化邻接矩阵
        }
    }
        dfs(1);
        cout<<bestcount<<endl;//k
        for(i=1;i<=n;i++)
        {
            if(bestx[i]==1)
            {
                cout<<i<<" ";
            }
        }
        cout<<endl;
 
    return 0;
}