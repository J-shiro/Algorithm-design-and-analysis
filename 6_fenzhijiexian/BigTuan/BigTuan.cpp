#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
#define MAXN 50
struct node{    //定义结构体结点
    int last;   //最后加入的点
    int num;    //顶点个数
    int v[MAXN];//标记数组，v[i]=1表示顶点i在集合中
    node(){//构造函数，初始化v数组和num
        memset(v,0,sizeof(v));
        num=0;
    }
};

int a[MAXN][MAXN]={
    {0,1,0,1,1},{1,0,1,0,1},
    {0,1,0,0,1},{1,0,0,0,1},
    {1,1,1,1,0}
};//邻接矩阵
int k,n=5;
queue<node*> qu;

void bfs(node *head)//分支限界法
{
    while(!qu.empty())qu.pop();
    qu.push(head);
    int j;
    while(!qu.empty()){
        node *tem = qu.front();//取对顶
        k=max(k,tem->num);
        if(k==n) break;//若k已经为n，则可以直接退出
        qu.pop();//出队
        int t=tem->last;
        for(int i=1;i<=n;i++){//搜索所有顶点
            if(i==t) continue;//若等于上一次的点，则跳过
            if(a[t][i]==1&&tem->v[i]==0)//若该点还未加入集合且两点间有连线
            {
                for(j=1;j<=n;j++){//判断该点是否与已加入集合中的每一个点由连线
                    if(tem->v[j]==1&&a[i][j]==0) break;
                }
                if(j>n){//若该点与该集合每一个点有连线，加入该点进入集合
                    node *nod=new node();
                    for(int z=1;z<=n;z++)//初始化temp
                    {
                        nod->v[z]=tem->v[z];
                    }
                    nod->last=i;
                    nod->v[i]=1;
                    nod->num=tem->num+1;
                    qu.push(nod);//新结点推入该队列
                }
            }
        }
        for(int x=1;x<=n;x++){
            cout<<tem->v[x]<<" ";
        }
        cout<<endl;
    }
}

int main(){
    int i,j;
    node *head = new node();
    head->last=0;
    k=0;
    bfs(head);
    cout<<"k: "<<k<<endl;
    return 0;
}
/*
0 1 0 1 1
1 0 1 0 1
0 1 0 0 1
1 0 0 0 1
1 1 1 1 0
*/