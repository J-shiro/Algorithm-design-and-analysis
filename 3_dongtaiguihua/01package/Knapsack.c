#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAXN 99
/*
    n个重量为{w1,w2,..,wn}物品，价值为{v1,v2,..,vn}
    容量为W的背包，每个物品要么选要么不选，选中物品可装入背包，
    重量和为W，具有最大价值
*/

/*
    2维动态规划数组dp，dp[i][r]表示背包剩余容量为r，已考虑物品1,2,..,i时背包装入物品的最优价值
    dp[i][0]=0  剩余容量为0，不能装入任何物品，总价值为0    dp[n][w]为最优解
    dp[0][r]=0  无任何物品装入，总价值为0
    dp[i][r]=dp[i-1][r]     当r<w[i]时，物品i放不下
    dp[i][r]=MAX{dp[i-1][r],dp[i-1][r-w[i]]+v[i]}   i物品可放入，在放入与不放入i间选最优解
    1.dp[i][r]=dp[i-1][r]:i不放入
    2.dp[i][r]!=dp[i-1][r]:i放入
*/

int n=5,W=10;             //5种物品，限制重量不超过10
int w[MAXN]={0,2,2,6,5,4};//下标0不用
int v[MAXN]={0,6,3,5,4,6};//下标0不用

int dp[MAXN][MAXN]; //动态规划数组
int x[MAXN];        //向量解
int maxv;           //存放最优解的总价值

void Knap(){
    int i,r;
    for(i=0;i<=n;i++)   //置边界条件=0
        dp[i][0]=0;
    for(r=0;r<=W;r++)   //置边界条件=0
        dp[0][r]=0;
    for(i=1;i<=n;i++){
        for(r=1;r<=W;r++){
            if(r<w[i])
                dp[i][r]=dp[i-1][r];
            else
                dp[i][r]=fmax(dp[i-1][r],dp[i-1][r-w[i]]+v[i]);
        }
    }
}

void Buildx()//回推求最优解
{
    int i=n,r=W;
    maxv=0;
    while(i>=0){//判断每个物品
        if(dp[i][r]!=dp[i-1][r])
        {
            x[i]=1;         //选取物品i
            maxv+=v[i];     //累计总价值
            r=r-w[i];       //剩余的容量
        }
        else{
            x[i]=0;         //不选取物品i
        }
        i--;
    }
}

int main(){
    Knap();
    printf("the dp array:\n");
    for(int i=0;i<=n;i++){
        for(int j=0;j<=W;j++){
            printf("%4d",dp[i][j]);
        }
        printf("\n");
    }
    Buildx();
    printf("the x vector: ");
    for(int i=1;i<=n;i++){
        printf("%d ",x[i]);
    }
    printf("\nthe max value is: %d",maxv);
    return 0;
}

/*
    Knap()算法含有两重for循环，时间复杂度O(n×W),空间复杂度为O(n×W)
    dp的空间大小为n×W
*/