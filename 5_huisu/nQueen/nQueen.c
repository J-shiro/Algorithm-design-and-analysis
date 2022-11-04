#include<stdio.h>
#include<stdbool.h>
#include<math.h>

int q[100] = {0};

bool placeOK(int n){
    int j = 1;
    if(n == 1)   return true;//the first row all can be placed.
    while(j<n){
        if(q[j]==q[n] || abs(j-n) == abs(q[j]-q[n]))//判断是否在同一列或在同一斜线上
            return false;
        j++;
    }
    return true;
}

void Queens(int n){
    
    int i = 1;
    q[i] = 0;
    while(i>=1){
        q[i]++;
        while(i<=n && !placeOK(i))
            q[i]++;
        if(q[i]<=n)
        {
            if(i == n){
                for(int j=1;j<=n;j++){
                    printf("%d",q[j]);
                }
                printf("\n");
            }
            else
            {
                i++;
                q[i] = 0;
            }
        }
        else
            i--;//回溯
    }
    
}

int main(){
    int n;
    printf("you should print a count:\n");
    scanf("%d",&n);
    Queens(n);
    return 0;
}
