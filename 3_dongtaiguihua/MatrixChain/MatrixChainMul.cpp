#include<iostream>
#include<iomanip>
using namespace std;
#define N 6
//p[i:j]=p[i]*p[i+1]*...*p[j]=Ai*A(i+1)*A(i+2)*...*Aj 矩阵连乘

void MatrixChain(int p[N+1],int n,int m[N+1][N+1],int s[N+1][N+1]){//自底向上计算出最优值数组
    for(int i=1;i<=n;i++)//n为N，矩阵数量此处为6，m矩阵一行一列不计算
        m[i][i]=0;//将对角线赋值为0:因为i=j的时候，只有一个矩阵，没有连乘，所以乘的次数为0
    //从矩阵左下往右上，左上往右下的方向求解m数组: m[i,j]=min{m[i,k]+m[k+1,j]+p[i-1]p[k]p[j]}----i<j时
    //m[1,2],m[2,3],m[3,4],m[4,5],m[5,6];m[1,3],m[2,4],m[3,5],m[4,6]
    //m[1,4],m[2,5],m[3,6];m[1,5],m[2,6];m[1,6]--->5次循环,2->3->4->5->6
    for(int r=2;r<=n;r++){// ↑解释↑此处为2到n(6)的五次循环
        for(int i=1;i<=n-r+1;i++){      //n-r+1即m数组的第一项范围
            int j=i+r-1;                //i+r-1即m数组的第二项范围
            m[i][j]=m[i+1][j]+p[i-1]*p[i]*p[j];//从i开始赋初值
            s[i][j]=i;  //以i为划分点作为初值
            for(int k=i+1;k<j;k++){
                int t = m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(t<m[i][j]){//有最小值，替换，更新最优解
                    m[i][j]=t;
                    s[i][j]=k;
                }
            }
        }             
    }
}

void Traceback(int i,int j,int s[N+1][N+1]){//输出最优解--矩阵的计算次序
//从s[i][j]得到的最优划分点回溯，递归进入分划出来的剩余数组,求最优的划分点
    if(i==j) return;//s[i][j]=0
    Traceback(i,s[i][j],s);
    Traceback(s[i][j]+1,j,s);//递归求解
    cout<<"A("<<i<<","<<s[i][j]<<")&A("<<s[i][j]+1<<","<<j<<")"<<endl;//输出
}

void Output(int n,int a[N+1][N+1]){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if((a[i][j]==0 && (i!=j))) 
                cout<<"      ";//左下角的值为0,填充为空,六个空格
            else 
                cout<<setw(6)<<a[i][j];//setw()设置字段宽度，在字前＋10格
        }
        cout<<endl;
    }
}

int main(){
    int p[N+1]={30,35,15,5,10,20,25};//N个矩阵相乘
    int m[N+1][N+1]={0};//存放i->j个矩阵相乘最小连乘数的最优值
    int s[N+1][N+1]={0};//存放划分点
    MatrixChain(p,N,m,s);
    Output(N,m);//输出m数组
    Output(N,s);//输出s数组
    Traceback(1,N,s);//此处调用1-6
    //结果应为：(A1(A2,A3))((A4,A5)A6)
    return 0;
}

/*复杂度分析：算法MatrixChain的主要计算量取决于算法中对r,i,k的三重循环,
  循环体内的计算量为O(1),而3重循环的总次数为O(n^3),所以算法计算时间上界为O(n^3),
  算法占用空间为O(n^2)
*/