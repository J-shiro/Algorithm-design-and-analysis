#include<iostream>
#include<string>
#include<math.h>
using namespace std;

/*
    X,Y：n位二进制数,n=2^k,求XY---->普通乘法O(n^2)

    X=A*2^(n/2)+B Y=C*2^(n/2)+D--->*2^(n/2):左移n/2位
    XY=AC*2^n+(AD+BC)*2^(n/2)+BD--->W(n)=4W(n/2)+O(n)==>W(n)=O(n^2)--->未发生改变

    AD+BC=(A-B)(D-C)+AC+BD-->W(n)=3W(n/2)+cn,W(1)=1--->由主定理：W(n)=O(n^(log3))
*/
int count=0;

void SameNumber();  //理想状态
void UnSameNumber();//非理想状态
int SIGN(long A);
long CalculateSame(long X,long Y,int n);
long CalculateUnSame(long X,long Y,int xn,int yn);

int main(){
    SameNumber();
    //UnSameNumber();
    return 0;
}

int SIGN(long A){
    return A > 0 ? 1 : -1;//判断A这个数是>0还是<0的
}

void SameNumber(){
    cout<<"ideal!"<<endl;   //理想状态用法:两个数长度相同
    cout<<"input 2 numbers:\nX=";//请输入两个大整数
    long X=0,Y=0;
    cin>>X;         //1234
    cout<<"Y=";
    cin>>Y;         //123
    cout<<"input length, n=";   //请输入两个大整数的长度：输入一个，默认两个相同
                                //输入偶数！因为之后需要/2，否则结果可能不对
    int n=0;
    cin>>n;         //4
    long sum=CalculateSame(X,Y,n);
    cout<<"normal X*Y="<<X<<"*"<<Y<<"="<<X*Y<<endl; //普通乘法
    cout<<"divide X*Y="<<X<<"*"<<Y<<"="<<sum<<endl; //分治算法
}

long CalculateSame(long X,long Y,int n){
    int sign = SIGN(X)*SIGN(Y);//符号得到
    X=abs(X);
    Y=abs(Y);
    if(X==0||Y==0)
        return 0;
    else if(n==1)
        return sign*X*Y;
    else{
        long A = (long)(X/pow(10,n/2));//X÷10^(n/2)左移n/2位，只剩下左半部分
        long B = (X%(long)pow(10,n/2));//取整，只剩下右半部分
        long C = (long)(Y/pow(10,n/2));
        long D = (Y%(long)pow(10,n/2));

        long AC = CalculateSame(A,C,n/2);//递归求解
        long BD = CalculateSame(B,D,n/2);
        long ABCD = CalculateSame((A-B),(D-C),n/2)+AC+BD;//--->AD+BC=(A-B)(D-C)+AC+BD

        cout<<"A="<<A<<" B="<<B<<" C="<<C<<" D="<<D<<endl;//打印一些结果
        return (long)(sign*(AC*pow(10,n)+ABCD*pow(10,n/2)+BD));//sign:符号
        //XY = AC*2^n+(AD+BC)*2^(n/2)+BD  ↑
    }
}

void UnSameNumber(){
    cout<<"\nno ideal"<<endl;   //非理想状态用法：两数长度不一样
    cout<<"input 2 numbers:\nX=";//请输入两个大整数
    long X=0,Y=0;
    cin>>X;         //1234
    cout<<"Y=";
    cin>>Y;         //123
    cout<<"length of x,xn=";   //请输入X的长度
    int xn=0,yn=0;
    cin>>xn;         //4
    cout<<"length of y,yn=";   //请输入y的长度
    cin>>yn;
    long sum=CalculateUnSame(X,Y,xn,yn);
    cout<<"normal X*Y="<<X<<"*"<<Y<<"="<<X*Y<<endl; //普通乘法
    cout<<"divide X*Y="<<X<<"*"<<Y<<"="<<sum<<endl; //分治算法
}

long CalculateUnSame(long X,long Y,int xn,int yn){
    if(X==0||Y==0)
        return 0;
    else if((xn==1&&yn==1)||xn==1||yn==1)
        return X*Y;
    else{
        //变化
        int xn0=xn/2,yn0=yn/2;
        int xn1=xn-xn0,yn1=yn-yn0;

        long A = (long)(X/pow(10,xn0));//X÷10^(n/2)左移n/2位，只剩下左半部分
        long B = (X%(long)pow(10,xn0));//取整，只剩下右半部分
        long C = (long)(Y/pow(10,yn0));
        long D = (Y%(long)pow(10,yn0));

        long AC = CalculateUnSame(A,C,xn1,yn1);//递归求解
        long BD = CalculateUnSame(B,D,xn0,yn0);
        long ABCD = CalculateUnSame((long)(A*pow(10,xn0)-B),(long)(D-C*pow(10,yn0)),xn1,yn1);
        //--->AD+BC=(A-B)(D-C)+AC+BD
        cout<<"A="<<A<<" B="<<B<<" C="<<C<<" D="<<D<<endl;//打印一些结果
        return (long)(2*AC*pow(10,(xn0+yn0))+ABCD+2*BD);
        //XY = AC*2^n+(AD+BC)*2^(n/2)+BD  ↑
    }
}