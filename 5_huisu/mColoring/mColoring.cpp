#include<iostream>
#include<memory.h>
#define MAXN 20 //图最多的顶点数
using namespace std;

/*
    给定无向连通图G和m种不同颜色，每个定点一种颜色，每条边两个点不同颜色
    输入格式：
        第一行3正整数n,k,m,表示图G: n个顶点，k条边，m种颜色，顶点编号为1,2,3..,n
        接下来k行：每行2个正整数u,v,表示图G的一条边(u,v)
    输出格式：
        计算出不同着色方案数输出，若不能着色，输出-1
*/
/*
    采用邻接矩阵a存储，a为一个二维数组（下标0不用），当顶点i和顶点j有边时，置a[i][j]=1
*/

int n,k,m;
int a[MAXN][MAXN];  //求解结果表示
int count=0;        //全局变量，累计解个数
int x[MAXN];        //全局变量，x[i]表示顶点i的着色

bool Same(int i){//找顶点i的相邻顶点
    for(int j=1;j<=n;j++){
        if(a[i][j]==1 && x[i]==x[j])//a[i][j]=1:有边-->a[i][i]为0导致排除了,x[i]==x[j]:颜色相同
            return false;//则方案不可行返回false
    }
    return true;
}

void dfs(int i){                //求解图的m着色问题--搜索算法
    if(i>n)                     //达到叶子结点
    {   //说明存在一个着色方案
        count++;                //着色方案数+1
        for(int i=1;i<=n;i++){
            cout<<x[i]<<" ";//输出每一种方案
        }
        cout<<endl;
    }
    else{
        for(int j=1;j<=m;j++)   //试探每一种着色
        {
            x[i]=j;             //试探着色j
            if(Same(i))         //可以着色j，进入下一个顶点着色
                dfs(i+1); 
            x[i]=0;             //回溯将每一个赋值好了的x数组重新还原为0
        }
    }
}

int main(){
    memset(a,0,sizeof(a));      //a初始化--->第一个参数为指针，指向数组a
    /*
        #include<string.h>
        void *memset(void *s, int c, unsigned long n);
        函数的功能是：将指针变量 s 所指向的前 n 字节的内存单元用一个“整数”int型c替换，
        s是void*型的指针变量，所以它可以为任何类型的数据进行初始化。
    */
    memset(x,0,sizeof(x));      //x初始化
    int x,y;
    cin>> n >> k >> m;          //输入n,k,m
    for(int j=1;j<=k;j++){
        cin>> x >> y;           //输入一条边的两个顶点
        a[x][y]=1;              //无向图的边对称
        a[y][x]=1;
    }
    cout<<"result:"<<endl;
    dfs(1);                     //从顶点1开始搜索
    if(count>0){
        cout<<count<<endl;
    }
    else{
        cout<<"-1"<<endl;
    }
    return 0;
}

//算法分析：每个顶点试探1-m种着色，共n个顶点，对应解空间树是一颗m叉树（子集树）
/*
    图m可着色问题解空间树中结点个数m^1+m^2+...m^(n-1)
    对于每一个内结点，最坏情况下用ok检查当前扩展结点每一个儿子所
    相应的颜色可用性耗时O(mn),因此总时间耗费：O(n*m^n)
*/