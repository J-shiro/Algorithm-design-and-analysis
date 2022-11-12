#include<stdio.h>
//整数划分问题
//正整数n的所有划分下，将最大加数n1不大于m的划分个数记为q(n,m)建立递归关系
/*
    1.q(n,m)=1                  n=1,m=1
    2.q(n,m)=q(n,n)             n<m
    3.q(n,n)=1+q(n,n-1)         n=m
    4.q(n,m)=q(n,m-1)+q(n-m,m)  n>m>1(有点难以理解)
    //由n1=m的划分和n1≤m-1的划分组成
*/

int q(int n,int m){//求解划分个数
    if((n<1)||(m<1))
        return 0;
    if((n==1)||(m==1))
        return 1;
    if(n<m)
        return q(n,n);
    if(n==m)
        return 1+q(n,m-1);
    return q(n,m-1)+q(n-m,m);
}

int main(){
    int x=q(6,6);
    printf("%d",x);
    return 0;
}