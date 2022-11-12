#include<stdio.h>

//1,1,2,3,5,8,13,21,34,55,..
int fibonacci(int n){
    if(n<=1)
        return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main(){
    int x=fibonacci(7);
    printf("%d",x);
    return 0;
}