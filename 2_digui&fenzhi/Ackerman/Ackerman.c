#include<stdio.h>
//双递归函数举例

int Ackerman(int n,int m){
    if(n==1&&m==0)
        return 2;
    if(n==0)
        return 1;
    if(m==0)
        return n+2;
    return Ackerman(Ackerman(n-1,m),m-1);
}

int main(){
    int x = Ackerman(2,3);
    printf("%d",x);
    return 0;
}