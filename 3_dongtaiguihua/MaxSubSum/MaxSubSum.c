#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAXN 99
/*
    最大连续子序列和至少是0     bj=MAX{ai+a(i+1)+..+aj} 
    b(j-1)>0    bj=b(j-1)+aj
    b(j-1)≤0    放弃前面选取元素，从aj开始重新选起，bj=aj
    用动态规划数组dp[]存放b：
        dp[0]=0                     边界条件
        dp[j]=MAX{dp[j-1]+aj,aj}    1≤j≤n
    所以序列a的最大连续子序列和=dp[j]中的最大值
*/

int n=6;
int a[] = {0,-2,11,-4,13,-5,-2};    //a数组不用下标为0的元素
int dp[MAXN];   //求解的结果表示

void maxSubSum(){   //求dp数组
    dp[0] = 0;
    for(int j=1;j<=n;j++){
        dp[j]=fmax(dp[j-1]+a[j],a[j]);
    }
}

void dispmaxSum(){//输出结果
    int maxj=1;
    int k;
    for(int j=2;j<=n;j++)           //求dp中最大元素dp[maxj]
        if(dp[j]>dp[maxj])  maxj=j;
    printf("the max consistent sub array sum:%d\n",dp[maxj]);
    for(k=maxj;k>=1;k--){   //找前一个值小于等于0者
        if(dp[k]<=0) break;
    }
    printf("the sub array: ");
    for(int i=k+1;i<=maxj;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}

int main(){
    maxSubSum();
    dispmaxSum();
    return 0;
}

//算法时间复杂度为O(n)