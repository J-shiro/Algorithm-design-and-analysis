#include <iostream>
using namespace std;
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<math.h>
#include<queue>

/*
    印刷电路板将布线区域划分为n*m个方格阵列，确定a到b的最短布线问题
    只能沿直线或直角布线，不允许穿过被封锁的方格，子集树
*/

//方格结构体
typedef struct
{
    int x;//x表示小方格所在行号
    int y;//y表示小方格所在列号
}Position;//表示结点的结构体

int grid[102][102];//用来表示电路板
//grid[i][j]=0表示可以布线，grid[i][j]=1表示不能布线
int n,m;//n表示电路板行数，m表示电路板的列数
bool FindPath(Position start,Position finish,int PathLen)
{
    //起点和目的点是同一个点，最短路径为0
    if(start.x==finish.x&&start.y==finish.y){
        PathLen=0;
        return true;
    }
    //设置方格围墙，扩充边界
    for(int j=0;j<=m+1;j++)
        grid[0][j]=1;//第0行全部置1
    for(int i=0;i<=n+1;i++)
        grid[i][0]=1;//第0列全部置1
    for(int j=0;j<=m+1;j++)
        grid[n+1][j]=1;//第n+1行全部置1
    for(int i=0;i<=n+1;i++)
        grid[i][m+1]=1;//第m+1列全部置1

    //初始化相对位移，上，下，左，右
    Position offset[4];//表示当前结点向上下左右扩展的相对位移
    offset[0].x=0;offset[0].y=1;//表示向右走一格
    offset[1].x=1;offset[1].y=0;//表示向下走一格
    offset[2].x=0;offset[2].y=-1;//表示向左走一格
    offset[3].x=-1;offset[3].y=0;//表示向上走一格
    int NumOfNbrs=4;//可扩展的点为四连通区域
    Position now,nerb;//now表示当前的活结点，nerb表示与活结点相邻的上下左右四个方格
    now=start;//给now赋初值，从初始节点开始，注意start不在活结点表里面
    grid[start.x][start.y]=0;//初始节点到初始节点的距离=0
    //构建活结点表的队列
    queue<Position>Q;//用来扩展活结点表，初始队列为空，将起始结点的四周的可扩展结点全部加入队列，不断循环
                     //求解最优值，直到队列为空为止，采用队列式分支限界法
    while(1){
        for(int i=0;i<NumOfNbrs;i++){
            nerb.x=now.x+offset[i].x;
            nerb.y=now.y+offset[i].y;
            if(grid[nerb.x][nerb.y]==0){//说明当前节点可以扩展，那么填充并加入活结点表
                grid[nerb.x][nerb.y]=grid[now.x][now.y]+1;
                //如果是目的节点，退出
                if(nerb.x==finish.x&&nerb.y==finish.y)
                    break;
                Q.push(nerb);//将新扩展的节点加入活节点表
            }
        }
        if(nerb.x==finish.x&&nerb.y==finish.y)
            break;//如果是目的节点，退出
        if(Q.empty())  return false;//当队列为空时，退出
        now=Q.front();//更新now的值，不然没法接着遍历新的活结点
        Q.pop();//将这个节点从活结点表中删除
    }
    return true;//返回
}
int main()
{
    cin>>n>>m;//输入电路板的行数，列数
    Position start,finish;//表征起始方格a，目的方格b
    cin>>start.x>>start.y;
    cin>>finish.x>>finish.y;
    //根据输入初始化电路板grid
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>grid[i][j];
        }
    }
    int Pathlen=1;//用来传递参数，当路径不为0时，不用Pathlen
    //执行FindPath函数，更新grid数组，并判断路径是否为0
    FindPath(start,finish,Pathlen);
    //输出结果
    if(Pathlen==0)
        cout<<0<<endl;
    else
        cout<<grid[finish.x][finish.y]<<endl;
    for(int i=0;i<=n+1;i++){
        for(int j=0;j<=n+1;j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
/*
输入：
7 7
3 2 row1,col1
4 6 row2,col2
0 0 1 0 0 0 0
0 0 1 1 0 0 0
0 0 0 0 1 0 0
0 0 0 1 1 0 0
1 0 0 0 1 0 0
1 1 1 0 0 0 0
1 1 1 0 0 0 0

输出：9
*/
//来自链接https://blog.csdn.net/practical_sharp/article/details/102760949