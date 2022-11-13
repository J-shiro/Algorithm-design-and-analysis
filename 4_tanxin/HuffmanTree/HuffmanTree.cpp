#include<iostream>
#include<vector>
#include<map>
#include<queue>
#define MAX 999
using namespace std;
/*
    要编码的字符集{d1,d2,..,dn},出现频率为{w1,w2,..,wn}
    1.给定的n个权值{w1,..,wn}构造n课只有一个叶子结点的二叉树
    2.找最小和次小权值叶子作为左右子树构建一颗新二叉树，权值相加-->小根堆实现
    3.重复建成哈夫曼树，总结点个数：2n-1    
        ht[0..2n-2]存放哈夫曼树 ht[0..n-1]存放叶子结点
                               ht[n..2n-2]存放n-1个分支结点
    map<char,string> htcode存放哈夫曼编码
*/

int n = 5;
struct HTreeNode//哈夫曼树结点类型
{
    char data;  //字符
    int weight; //权值
    int parent; //双亲位置
    int lchild; //左孩子位置
    int rchild; //右孩子位置
};
HTreeNode ht[MAX];          //存放哈夫曼树
map<char,string> htcode;    //存放哈夫曼编码

struct NodeType{            //优先队列结点类型
    int no;                 //对应哈夫曼树ht[]中的位置
    char data;              //字符
    int weight;             //权值
    bool operator < (const NodeType &s) const
    {                               //用于创建小根堆
        return s.weight < weight;//重载<运算符：权值越小的优先出队
    }
};

void CreateHTree(){ //构造哈夫曼树
    NodeType e,e1,e2;
    priority_queue<NodeType> qu;
    for(int k=0;k<2*n-1;k++){//设置所有结点的指针域
        ht[k].lchild=ht[k].parent=ht[k].rchild=-1;//初始化，双亲孩子都置为-1
    }
    for(int i=0;i<n;i++){//将n个结点进队qu
        e.no=i;
        e.data=ht[i].data;
        e.weight=ht[i].weight;
        qu.push(e);
    }
    for(int j=n;j<2*n-1;j++)    //构造哈夫曼树的n-1个非叶子结点
    {
        e1=qu.top();    
        qu.pop();   //出队权值最小的结点e1
        e2=qu.top();    
        qu.pop();   //出队权值次小的结点e2
        ht[j].weight=e1.weight+e2.weight;   //构造哈夫曼树的非叶子结点j
        ht[j].lchild=e1.no;
        ht[j].rchild=e2.no;
        ht[e1.no].parent=j; //e1.no的双亲为结点j
        ht[e2.no].parent=j; //e2.no的双亲为结点j
        e.no=j;             //构造队列结点e
        e.weight=e1.weight+e2.weight;
        qu.push(e);
    }
}

void CreateHCode()  //构造哈夫曼编码
{
    string code;
    code.reserve(MAX);//将容器中的桶数设置为最适合包含至少 n 个元素

    for(int i=0;i<n;i++){   //构造叶子结点i的哈夫曼编码
        code="";
        int curno=i;
        int f=ht[curno].parent;
        while(f!=-1){   //循环到根结点
            if(ht[f].lchild==curno) //curno为双亲f的左孩子
                code='1'+code;
            else                    //curno为双亲f的右孩子
                code='0'+code;
            curno=f;
            f=ht[curno].parent;
        }
        htcode[ht[i].data]=code;    //得到ht[i].data字符的哈夫曼编码
    }
}

int main(){
    char a[n]={'a','b','c','d','e'};
    int w[n]={4,2,1,7,3};
    for(int i=0;i<n;i++){
        ht[i].data=a[i];
        ht[i].weight=w[i];
    }
    CreateHTree();
    CreateHCode();
    for(int j=0;j<n;j++){
        cout<<ht[j].data<<":  "<<htcode[ht[j].data]<<endl;
    }
    return 0;
}

//算法设计分析：时间O(nlogn)
//初始化优先队列需要O(n)时间，最小堆的插入和取出运算均需要O(logn)时间
//n-1次的合并供需要O(nlogn)计算时间