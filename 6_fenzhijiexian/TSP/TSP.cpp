#include<iostream>
#include<queue>
#include<vector>
#include<memory.h>
using namespace std;
#define MAXV 30
#define INF 9999
/*
    采用优先队列式分支限界法求解：
     STL中的priority_queue<NodeType>容器作为优先队列
*/

struct NodeType{            //队列结点类型
    int v;                  //当前的顶点
    int num;                //路径中的结点个数
    vector<int> path;       //当前路径
    int pathlen;            //当前路径长度
    int visited[MAXV];      //顶点访问标记
    bool operator < (const NodeType &s) const{
        return pathlen>s.pathlen;      //pathlen越小越优先出队
    }
};
int n=4;  //图
int s=0;  //指定起点
int g[MAXV][MAXV]={
    {0,8,5,36},{6,0,9,5},
    {8,9,0,5},{7,7,8,0}
};  //图的邻接矩阵

int Count=1;         //路径条数累计,用于所有解列出来,好像没有用到
vector<int> minpath;//保存最短路径
int minpathlen=INF; //保存最短路径长度

void TSP(){         //分支限界法求起点为s的TSP问题
    NodeType e,e1;
    priority_queue<NodeType> qu;    //定义优先队列qu
    e.v=0;                          //初始化e
    e.pathlen=0;
    e.path.push_back(0);
    e.num=1;
    memset(e.visited,0,sizeof(e.visited));
    e.visited[0]=1;
    qu.push(e);                     //根结点e进队
    while(!qu.empty())      //队不空则循环
    {
        e=qu.top(); qu.pop();   //出队结点e
        if(e.num==n){           //到达叶子结点
            if(g[e.v][s]!=0&&g[e.v][s]!=INF){
                //e.v到起点s有边
                e.path.push_back(s);    //路径中加入起点s
                e.pathlen+=g[e.v][s];//另外计入从e.v到起点s的路径长度
                cout<<"pathlen: "<<e.pathlen<<endl<<"path: ";
                for(int i=1;i<=n;i++){
                    cout<<e.path[i]<<" ";
                }
                cout<<endl;
                if(e.pathlen<minpathlen){   //比较求最短路径
                    minpathlen=e.pathlen;
                    minpath=e.path;
                }
            }
        }
        else{                       //非叶子结点
            for(int j=1;j<n;j++){   //j从顶点1到n-1循环
                if(g[e.v][j]!=0&&g[e.v][j]!=INF){
                    //当前顶点到顶点j有边
                    if(e.visited[j]==1)//跳过路径中重复的顶点j
                    {
                        continue;
                    }
                    e1.v=j;
                    e1.num=e.num+1;
                    e1.path=e.path;
                    e1.path.push_back(j);       //path添加顶点j
                    e1.pathlen=e.pathlen+g[e.v][j];
                    for(int i=0;i<n;i++){       //复制visited
                        e1.visited[i]=e.visited[i];
                    }
                    if(e1.pathlen<minpathlen){//剪枝
                        e1.visited[j]=1;
                        qu.push(e1);
                    }
                }
            }
        }
    }
}

int main(){
    TSP();
    cout<<"minpathlen: "<<minpathlen<<endl<<"minpath: ";
    for(int i=1;i<=n;i++){
        cout<<minpath[i]<<" ";
    }
    return 0;
}

//算法分析：时间复杂度O(2^n)