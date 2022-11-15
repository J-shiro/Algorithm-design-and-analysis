#include<stdio.h>

#define MAXN 99
/*
    n个集装箱，船重量为W，i的重量为wi，选出重量和≤W且尽可能大的若干装入船
    采用带剪枝的回溯法求解--->解空间树：子集树
*/

int w[]={0,5,2,6,4,3};  //各集装箱重量，不用下标0的元素
int n=5,W=10;

int maxw=0;     //存放最优解的总重量
int x[MAXN];    //存放最优解向量

/*
    左剪枝：仅扩展tw+w[i]≤W的左孩子结点--->已选择的加上第i个重量≤W
    右剪枝：仅扩展tw+rw-w[i]>maxw的右孩子结点--->已选择的加上剩余的减去要选择的i的重量>目前最大值
*/

void dfs(int i,int tw,int rw,int op[]){//i:考虑的集装箱i，tw：选择的集装箱重量和
                                       //rw:剩余集装箱重量和(初始为全部集装箱重量和)，op：临时解
    if(i>n){    //找到一个叶子结点
        if(tw>maxw){    //在剪枝的时候已经保证了<W,不需要添加小于W的条件
            maxw=tw;                //找到一个满足条件的更优解，保存它
            for(int j=1;j<=n;j++)   //复制最优解
                x[j]=op[j];
        }
    }
    else{       //尚未找完所有集装箱
        if(tw+w[i]<=W){ //左孩子结点剪枝
            op[i]=1;    //选取第i个集装箱
            dfs(i+1,tw+w[i],rw-w[i],op);
        }
        if(tw+rw-w[i]>maxw){    //右孩子结点剪枝
            op[i]=0;    //不选取第i个集装箱，回溯
            dfs(i+1,tw,rw-w[i],op);
        }
    }

}


int main(){
    int op[MAXN];
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=w[i];
    }
    dfs(1,0,sum,op);
    printf("maxw: %d\nchoose the boxes(choose is 1,no is 0):",maxw);
    for(int i=1;i<=n;i++){
        printf("%d ",x[i]);
    }
    return 0;
}

//O(2^n)