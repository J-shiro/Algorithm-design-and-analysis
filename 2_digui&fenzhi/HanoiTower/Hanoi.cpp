#include<iostream>
using namespace std;

void move(char a,char b){
    cout<<a<<"-->"<<b<<endl;
}

void hanoi(int n,char a,char b,char c){//将a上n个盘借c移到b
    if(n==0) move(a,b);
    if(n>0){
        hanoi(n-1,a,c,b);
        move(a,b);//将a上为n的圆盘移到b
        hanoi(n-1,c,b,a);
    }
}

int main(){
    int n=3;
    char a='a',b='b',c='c';
    hanoi(n,a,b,c);
    return 0;
}

/*
    T(n)= 2T(n-1)+` n>1 --->两个n-1的递归加上移动一次
          1         n=1 --->直接移动一次
    O(n^2)
*/