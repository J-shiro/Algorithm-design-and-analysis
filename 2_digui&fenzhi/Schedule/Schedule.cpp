#include<iostream>
#include<iomanip> //setw()
#define MAX 101
using namespace std;
/*
    n=2^k个选手循环赛，每个选手必须与n-1个选手各赛一次
    每个选手一天只能赛一次，循环赛n-1天内结束
    1-n,设计出一个n行n-1列的二维表,第i行、第j列表示和第i个选手在第j天比赛的选手
*/

/*                     左上角 右上角=左下角          左上角      右上角=左下角
    k=1  1: 2      k=2  1: 2  3  4            k=3 1: 2  3  4  5  6  7  8
         2: 1  -->      2: 1  4  3       -->      2: 2  4  3  6  5  8  7
                        3: 4  1  2                3: 4  1  2  7  8  5  6
                        4: 3  2  1                4: 3  2  1  8  7  6  5
       加2^(k-1)=2     左下角 右下角=左上角         5: 6  7  8  1  2  3  4
                                                  6: 5  8  7  2  1  4  3
                                   加2^(k-1)=4    7: 8  5  6  3  4  1  2
                                                  8: 7  6  5  4  3  2  1
                                                    左下角      右下角=左上角

*/

int k;  //求解结果表示、
int a[MAX][MAX];    //存放比赛日程表（行列下标为0的元素不用）

void Plan(int k){
    int i,j,n,t,temp;
    n=2;    //n从2^1=2开始
    a[1][1]=1;  a[1][2]=2;  //求解2个选手比赛日程，得到左上角元素
    a[2][1]=2;  a[2][2]=1;

    for(t=1;t<k;t++){   //迭代处理2^2(t=1)...,2^k(t=k-1)个选手
        temp=n; //temp=2^t
        n=n*2;  //n=2^(t+1)
        //左上角为2^(k-1)个选手的比赛日程
        
        for(i=temp+1;i<=n;i++)              //填左下角元素
            for(j=1;j<=temp;j++)
                a[i][j]=a[i-temp][j]+temp;
        
        for(i=1;i<=temp;i++)                //填右上角元素
            for(j=temp+1;j<=n;j++)
                a[i][j]=a[i+temp][(j+temp)%n];  //仔细理解，此处是通过加上temp%n后相当于循环回左下角的列
        
        for(i=temp+1;i<=n;i++)              //填右下角元素
            for(j=temp+1;j<=n;j++)
                a[i][j]=a[i-temp][j-temp];//左上角
    }
}

int main(){
    k=3;
    int n=1<<k; //n等于2的k次方 即n=2^k
    Plan(k);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<setw(4)<<a[i][j];
        }
        cout<<endl;
    }
    return 0;
}