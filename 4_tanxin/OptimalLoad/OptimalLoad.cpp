#include<iostream>
#include<math.h>
#include<vector>
#include<string.h>
#include<algorithm>
#define MAXN 30
using namespace std;
//n个集装箱装上重量为W的轮船集装箱i的重量为wi,选出尽可能多的集装箱装入且重量和<=W

int w[]={0,5,2,6,4,3};  //各个集装箱的重量，不用下标0的元素
int n=5,W=10;//集装箱个数，轮船重量

int maxw;   //存放最优解的总重量
int x[MAXN];//存放最优解向量，即存放哪些集装箱

void Loading(){//求解最优装载问题
    memset(x,0,sizeof(x));  //初始化解向量
    sort(w+1,w+n+1);//w[1...n]递增排序
    maxw=0;
    int restw=W;    //剩余重量
    for(int i=1;i<=n && w[i]<=restw;i++){
        x[i]=1;         //选择集装箱i
        restw-=w[i];    //减少剩余重量
        maxw+=w[i];     //累计装载总重量
    }
}

int main(){
    Loading();
    cout<<"best solve:"<<endl;
    for(int z=1;z<=n;z++){
        cout<<x[z];
    }
    cout<<endl;
    for(int z=1;z<=n;z++){
        cout<<w[z];
    }
    cout<<endl;
    cout<<"the whole Loading weight:"<<maxw<<endl;
    return 0;
}

//算法复杂度分析:O(nlogn)