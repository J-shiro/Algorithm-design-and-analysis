#include<iostream>
#include<queue>
using namespace std;

typedef struct QNode
{
    QNode *parent;	//指向父节点的指针 
    int lchild;		//左儿子标志 若lchild=0,则为父结点的右儿子，lchild=1，则为父结点的左儿子
    //右儿子结点一定可行 
    int weight;		//结点所对应的载重量 
}QNode;				

int n;//装载的物品数量5
int c;//不能超过的重量10
int bestw;
int w[100];
int bestx[100];

void InPut();
void OutPut();
void EnQueue(queue<QNode *> &q, int wt, int i, QNode *E, QNode *&bestE, int ch);
void MaxLoading();

int main()
{
    InPut();
    MaxLoading();
    OutPut();
}


void InPut()
{
	cout<<"n: ";
    cin>>n;
    cout<<"c: ";
    cin>>c;
    cout<<"weight: ";
    for(int i = 1; i <= n; ++i)
        cin>>w[i];//{5,2,6,4,3}
}

void MaxLoading()
{
    queue<QNode *>q;//定义队列的方法，定义队列q，QNode是结点结构体 
    q.push(0);		//同层结点尾部标志  
    int i = 1;		//当层扩展结点所处的层 
    int Ew = 0, 	//扩展结点所相应的载重量 
	r = 0;			//剩余集装箱的重量 
    bestw = 0;		//当前最优载重量 
    for(int j = 2; j <= n; ++j)
        r += w[j];
    QNode *E = new QNode; //E是指向QNode类型的指针，为当前扩展结点，E这里作为一个中间量，连接parent和child 
	QNode *bestE; 	//bestE是指向QNode类型的指针，为当前最优扩展结点 
					//bestE的作用是：结束while循环后，bestE指向最优解的叶子节点，然后通过bestE->parent找到装入了哪些物品
    E = 0;         	//赋0是因为树的根的值是0，while刚开始的时候其代表root
    
    while(true)		//检查左儿子结点是否为可行解，如果是则调用EnQueue将其加入到活结点队列中，
	//然后将右儿子结点加入活队列（右儿子结点一定是可行结点）两个儿子结点都产生后，当前扩展结点被舍弃，
	//活结点队列中的队首元素被取出作为当前扩展结点。当取出元素是-1时，判断队列是否为空，若非空，将队尾标记-1加入活结点队列 
    {
        int wt = Ew + w[i];
        if(wt <= c)			//wt=Ew+w[i],如果wt<=c，表明左儿子可以放入，所以EnQueue(wt,1) 
        {
            if(wt > bestw)	 
                bestw = wt;//更新最优值 
            EnQueue(q, wt, i, E, bestE, 1);//EnQueue(Q,wt,i,n,bestw,E,bestE,bestx,true) 
        }
        if(Ew + r >= bestw)//else wt>c，此时不考虑左儿子，考虑右儿子，当Ew+r>=bestw时，可能存在更好的bestw，故EnQueue(Ew,0) 
        {
            EnQueue(q, Ew, i, E, bestE, 0);//EnQueue(Q,Ew,i,n,bestw,E,bestE,bestx,false) 
        }
        E = q.front();//取下一扩展结点 
        q.pop();//删除父结点
        if(!E)///到达同层的最末，此时需要更新剩余装箱载重量/对应队列中的-1
        {
            if(q.empty())	//empty() 当队列为空时，返回true
                break;
            //若队列不为空
            q.push(0);		//push(x) 将x压入队列的末端，加入0，表示该层结束,(下一层尾部加标识-1)
            E = q.front();	//front()返回第一个元素(队顶元素)
            q.pop();		//pop()弹出队列的第一个元素(队顶元素)，注意此函数并不返回任何值 
            i++;			//进入下一层 
            r -= w[i];  	//更新剩余集装箱的重量 
        }
        Ew = E->weight; 	//更新最新节点对应的载重量 
    }

    for(int j = n - 1; j > 0; --j)
    {
        bestx[j] = bestE->lchild;
        bestE = bestE->parent;
    }
}

/*
    "-1"或"0"用于分割不同层的结点，活结点队列里存放状态结点对应的重量
*/


void EnQueue(queue<QNode *> &q, int wt, int i, QNode *E, QNode *&bestE, int ch)
//QNode *是个整体，表示变量类型是QNode类指针， &bestE中的&表明引用实参，即代表实参的一个别名。
//&在变量定义区，表示引用，要注意它的用法。&在变量操作区，表示取地址符。这里表示引用 
{	//将活结点加入到活结点队列中的算法EnQueue 
	//QNode *&bestE 引用为了赋值使用, 后边for循环中用到
    if(i == n)//i=n表明当前结点为活结点的叶子结点，叶子结点不扩展，不加入队列，检查该叶子结点的可行解是否优于最优解，优则更新 
    {
        if(wt == bestw)
        {
            bestE = E;
            bestx[n] = ch;//<---------------------------------|
            return;//                                         |
        }//                                                   |回溯找到最优解
    }//                                                       |
    QNode *b = new QNode;//创建一个新的QNode的类型的指针b       |
    b->weight = wt;//                                         |
    b->lchild = ch;//<----------------------------------------|
    b->parent = E;
    q.push(b);//push(b 将b压入队列的末端
}

void OutPut()
{
    cout<<"Bestweight "<<bestw<<endl;
    cout<<"Bestx: ";
    for(int i=1;i<=n;i++){
        cout<<bestx[i]<<" ";
    }
    cout<<endl;
    cout<<"Bestway: ";
    for(int i = 1; i <= n; ++i)
        if(bestx[i] == 1)
          cout<<i<<" ";
}

//链接来源：https://blog.csdn.net/weixin_43348682/article/details/103366712