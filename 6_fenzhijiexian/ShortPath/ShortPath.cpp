#include<iostream>
#include<queue>
#include<vector>
#include<memory.h>
#include<iomanip>
#define INF 0x3f3f3f    //表示∞
#define MAXN 51
using namespace std;
/*
    带权有向图G=(V,E),每条边的权是正整数--->队列式分支限界法求解
    给定V中一个顶点v为源点，计算从源点到其他所有顶点的最短路径长度

    dist数组存放源点v出发的最短路径长度，dist[i]表示源点v到顶点i的最短路径长度，初始时为∞
    previ数组存放最短路径，previ[i]表示源点v到顶点i的最短路径中i的前驱顶点
*/

struct NodeType{//队列结点类型声明
    int vno;    //顶点编号
    int length; //路径长度-->源点到vno对应的最短路径的长度
    bool operator<(const NodeType &node) const{
        return length>node.length;  //length越小越优先出队
    }
};
int n;  //图顶点个数
int a[MAXN][MAXN];   //图的邻接矩阵
int v;  //源点
//求解结果表示
int dist[MAXN]; //dist[i]表示：源点到顶点i的最短路径长度
int previ[MAXN]; //previ[i]表示：源点到j的最短路径中顶点j的前驱顶点

void prio_bfs(int v){    //采用队列式分支限界法求解
    NodeType e,e1;
    queue<NodeType> pqu;
    e.vno=v;    //建立源点结点e(根结点)
    e.length=0;
    pqu.push(e);//源点结点e进队
    dist[v]=0;
    while(!pqu.empty()){    //队列不为空，进入循环
        e=pqu.front();
        pqu.pop();  //出队列结点e
        for(int j=0;j<n;j++){
            if(a[e.vno][j]<INF && a[e.vno][j]+e.length<dist[j]){//最后一个不满足，不再入队，则队列为空
                //剪枝：e.vno到顶点j有边且路径长度更短             //跳出循环
                dist[j]=a[e.vno][j]+e.length;
                previ[j]=e.vno;
                e1.vno=j;       //建立相邻顶点j的结点e1
                e1.length=dist[j];
                pqu.push(e1);   //结点e1进队
            }
        }
    }
}

void bfs(int v){        //采用优先队列式分支限界法求解
    NodeType e,e1;
    priority_queue<NodeType> pqu;//定义优先队列
    e.vno=v;        //建立源点结点e
    e.length=0;
    pqu.push(e);    //源点结点e进队
    dist[v]=0;
    while(!pqu.empty()){    //队列不空循环
        e=pqu.top();        //出队列结点e
        pqu.pop();
        for(int j=0;j<n;j++){
            if(a[e.vno][j]<INF && e.length+a[e.vno][j]<dist[j]){
                //剪枝：e.vno到顶点j有边并且路径长度更短
                dist[j]=e.length+a[e.vno][j];
                previ[j]=e.vno;
                e1.vno=j;   //建立相邻顶点j的结点e1
                e1.length=dist[j];
                pqu.push(e1);   //结点e1进队
            }
        }
    }
}

int main(){
    n=6;
    v=0;
    int b[MAXN][MAXN]={{0,INF,10,INF,30,100},{INF,0,4,INF,INF,INF},
             {INF,INF,0,50,INF,INF},{INF,INF,INF,0,INF,10},
             {INF,INF,INF,20,0,60},{INF,INF,INF,INF,INF,0}};
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            a[i][j]=b[i][j];
        }
    }
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<setw(10)<<a[i][j];
    //     }
    //     cout<<endl;
    // }
    memset(dist,INF,sizeof(dist));
    // for(int i=0;i<n;i++){
    //     cout<<dist[i]<<" ";
    // }
    // cout<<endl;
    memset(previ,0,sizeof(previ));
    // for(int i=0;i<n;i++){
    //     cout<<previ[i]<<" ";
    // }
    // cout<<endl;
    bfs(v);
    for(int i=0;i<n;i++){
        cout<<dist[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<previ[i]<<" ";
    }
    return 0;
}