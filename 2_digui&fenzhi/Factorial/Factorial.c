#include<stdio.h>
//阶乘函数：n!

int factorial(int n){
    if(n==0)
        return 1;   //边界条件
    return n*factorial(n-1);
}

int main(){
    int x = factorial(4);
    printf("%d",x);
    return 0;
}
