#include<stdio.h>
#include<stdbool.h>
#include<math.h>

/*
    按枚举法，有n!种情况
*/

int q[100] = {0};//q[i]表示第i个皇后的列号，第i个皇后位置为(i,q[i])

bool placeOK(int n){//测试第i行的q[i]列上可否放皇后
    int j = 1;
    if(n == 1)   return true;//第一行都可以放
    while(j<n){
        if(q[j]==q[n] || abs(j-n) == abs(q[j]-q[n]))//判断是否在同一列或在同一斜线上
            return false;
        j++;
    }
    return true;
}

void Queens(int n){
    
    int i = 1;//i表示当前行，表示放置第i个皇后
    q[i] = 0;//q[i]表示当前列
    while(i>=1){//还没回溯到头3
        q[i]++;//皇后后移动一列
        while(i<=n && !placeOK(i))//试探位置(i,q[i])
            q[i]++;//能放则+1
        if(q[i]<=n)//为第i个皇后找到了一个合适位置
        {
            if(i == n){//若放置了所有的皇后，输出一个解
                for(int j=1;j<=n;j++){
                    printf("%d",q[j]);
                }
                printf("\n");
            }
            else//皇后未放置完
            {
                i++;//下一行，下一皇后放置
                q[i] = 0;//新考虑的皇后初始位置置为0列
            }
        }
        else//未找到合适位置
            i--;//回溯
    }
    
}

int main(){
    int n;//n存放实际皇后个数
    printf("you should print a count:\n");
    scanf("%d",&n);
    Queens(n);
    return 0;
}

/*算法分析：每个皇后要试探n列，共n个皇后，
解空间是一个子集树，每个结点可能有n棵子树，
算法时间复杂度为O(n^n)*/