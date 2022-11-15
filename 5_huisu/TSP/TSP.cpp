#include<iostream>
#include<vector>
#include<set>
#include<iomanip>
#define INF 100 //边的最大权值
#define MaxSize 10  //最大顶点数目
using namespace std;
/*
    拜访n个城市，每个城市只能拜访一次，最后要回到原来出发的城市
    要求路径为所有中最小的

    搜索过程：总路径数：对称情况：(n-1)!/2
                      非对称情况：(n-1)!

    f(V,i)求从i出发经过V(一个顶点集合)中各个顶点一次，回到出发点s的最短路径长度
    path：当前路径，pathlen：路径长度
    minpath：最短路径，minpathlen：最短路径长度
    V用set<int>容器表示，初始时V={1,2,3}
    剪枝规则：当一个结点当前路径长度>minpathlen,该结点变成死结点= 
*/

//邻接矩阵
typedef struct{
    int edges[MaxSize][MaxSize];    //边，int为权值类型
    int n,e;    //顶点和边数
}MGraph;    //图的邻接矩阵类型

typedef set<int> SET;   //采用set<int>表示顶点集合
/*set是STL中一种标准关联容器,集合,在set中元素都是唯一的，默认情况下会对元素自动进行升序排列
*/
int s;  //指定起点
MGraph g;   //图的邻接矩阵

int Count=1;//路径条数累计--->没有用到
vector<int> minpath;//保存最短路径
int minpathlen=INF;//保存最短路径长度，先设置为正无穷大

void TSP(SET V,int i,vector<int> path,int pathlen){//path和pathlen都是指当前的路径
    int prev=0;
    if(path.size()>0)       //path不为空，说明搜索过定点了
        prev=path.back();   //prev为路径上的最后一个顶点，会从这个顶点出发，往下搜索
    path.push_back(i);      //添加当前顶点i-->初始时，会添加0
    pathlen+=g.edges[prev][i];//累计路径长度

    if(V.size()==0){    //找到一个叶子结点
        if(g.edges[i][s]!=0 && g.edges[i][s]!=INF){//顶点i到起点s有边
            path.push_back(s);  //路径中加入起点0
            pathlen+=g.edges[i][s]; //累计路径长度
            for(vector<int>::iterator iter=path.begin();iter!=path.end();iter++){
                cout<<*iter<<" ";//输出一条路径
            }
            cout<<endl;
            if(pathlen<minpathlen){//比较求最短路径
                minpathlen=pathlen;
                minpath=path;
            }
        }
    }
    else{   //对于非叶子结点
        SET::iterator it;
        for(it=V.begin();it!=V.end();it++){
            SET tmpV=V;
            int j=*it;      //选择顶点j-->1,2,3
            tmpV.erase(j);  //从V中删除顶点j得到tmpV
            if(pathlen<minpathlen)  //剪枝
                TSP(tmpV,j,path,pathlen);   //递归调用
        }
    }
}

int main(){
    int A[][MaxSize]={//一个带权的有向图
        {0,8,5,36},{6,0,8,5},{8,9,0,5},{7,7,8,0}
    };
    int n=4,e=12;
    g.n=n; g.e=e;//初始化邻接矩阵g
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            g.edges[i][j]=A[i][j];
        }
    }
    s=0;    //起始顶点为0
    vector<int> path;
    int pathlen=0;
    SET V;
    for(int i=1;i<g.n;i++)//插入1,2,3顶点
        V.insert(i);
    TSP(V,0,path,pathlen);
    cout<<"result"<<endl;
    cout<<"shortest path: ";//最短路径
    for(int j=0;j<minpath.size();j++){
        cout<<setw(3)<<minpath[j];
    }
    cout<<endl<<"path length: "<<minpathlen;
    return 0;
}

/*
    深度优先+剪枝
    算法分析:对于图中n个顶点，需要对{1,2,...,n-1}的每个子集操作，时间复杂度为O(2^n)
*/