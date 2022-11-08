#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define MAXN 20
/*
    n个集装箱装入2重量分别为c1和c2的轮船，其中i重量wi，w1+w2+..+wn≤c1+c2
    1.尽可能多将集装箱装入1船，得到解向量x
    2.累计1船装完后剩余集装箱重量sum
    3.sum<=c2则表示2船可装完返回true，装不完返回false
*/

int w[]={0,10,40,40};   //各集装箱重量，不用下标0的元素
int n=3;
int c1=50,c2=50;
int maxw=0;     //存放第一艘轮船最优解的总重量
int x[MAXN];    //存放第一艘轮船最优解向量

void dfs(int i,int tw,int rw,int op[]){ //求第一艘轮船的最优解
    if(i>n){                            //找到一个叶子结点
        if(tw>maxw){
            maxw=tw;                    //找到一个满足条件的最优解
            for(int j=1;j<=n;j++){      //复制最优解
                x[j]=op[j];
            }
        }
    }
    else{                               //尚未找完所有集装箱
        if(tw+w[i]<=c1){                //左孩子结点剪枝
            op[i]=1;                    //选取第i个集装箱
            dfs(i+1,tw+w[i],rw-w[i],op);
        }
        if(tw+rw-w[i]>maxw){            //右孩子结点剪枝
            op[i]=0;                    //不选取第i个集装箱，回溯
            dfs(i+1,tw,rw-w[i],op);
        }
    }
}

bool solve(){   //求解复杂装载问题
    int sum=0;  //累计第一艘轮船装完后剩余的集装箱重量
    for(int j=1;j<=n;j++){
        if(x[j]==0)
            sum += w[j];
    }
    if(sum<=c2)
        return true;//第二艘轮船可以装完
    else
        return false;//第二艘轮船不能装完
}

int main(){
    int op[MAXN];   //存放临时解
    memset(op,0,sizeof(op));
    int rw=0;
    for(int i=1;i<=n;i++){
        rw+=w[i];
    }
    dfs(1,0,rw,op); //求解第一艘轮船的最优解
    printf("results: \n");
    if(solve()){
        printf("best solution: 1 for the c1,0 for the c2\n");
        for(int i=1;i<=n;i++){
            printf("%d ",x[i]);
        }
    }
    else{
        printf("there's no solution.");
    }
    return 0;
}