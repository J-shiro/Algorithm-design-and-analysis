#include<iostream>
#include<algorithm>
#include<string.h>
#define N 6
using namespace std;

/*
    n个作业{1,2,...,n}在2台机器M1和M2上加工，先M1后M2；M1和M2加工作业i所需时间为ai和bi
    M1  -----i---j
    M2        -----i---j    求最小的加工所需时间-->排序
    M1  ---j-----i
    M2      ---j  -----i    先j后i和先i后j

    若i和j满足min{bi,aj}≥min{bj,ai}，则称ij满足Johnson不等式，最优
    具体：
    令N1={i|ai<bi}，N2={i|ai≥bi};将N1中作业依ai非减序排序，N2中作业依bi非增序排序
    ai中最小的放在最前面，bi中最小的放在最后面
    N1中作业接N2中作业构成满足Johnson法则的最优调度

*/

class Jobtype{
public:
    int key;    //执行时间
    int index;  //作业序号
    bool job;   //1第一组，0第二组
    int operator <= (Jobtype a) const{//重载<=号
        return (key <= a.key);
    };
};

bool compare(Jobtype a,Jobtype b){  //类排序
    return a.key<b.key;
};

int FlowShop(int n,int a[],int b[],int c[]){
    Jobtype *d = new Jobtype[n];    //定义一个类变量，申请一个类数组
    for(int i=0;i<n;i++){//划分
        d[i].key=a[i]>b[i]?b[i]:a[i];   //ai＞bi-->bi(N2);  ai≤bi-->ai(N1)
        d[i].job=a[i]<b[i]; //按照1或0分为N1(ai<bi)和N2(ai≥bi)
        d[i].index=i;
    }
    sort(d,d+n,compare);    //按d增序
    int j=0,k=n-1;
    for(int i=0;i<n;i++){       //初始化c数组，其中为最优解的作业序号顺序
        if(d[i].job)
            c[j++]=d[i].index;
        else
            c[k--]=d[i].index;
    }
    j=a[c[0]];
    k=j+b[c[0]];    //一个作业完成
    for(int i=1;i<n;i++){       //求解最小的时间
        j+=a[c[i]];
        k=j<k ? k+b[c[i]] : j+b[c[i]];  //比较k和j谁先结束
    }
    delete d;
    return k;
}

int main(){
    int a[N]={3,12,5,2,8,11};       //ai时间
    int b[N]={7,10,9,6,4,1};        //bi时间
    int c[N]={0};
    cout<<"the best solution: "<<FlowShop(N,a,b,c)<<endl;
    cout<<"the sequence: ";
    for(int i=0;i<N;i++){
        cout<<c[i]+1<<" ";
    }
    cout<<endl;
    return 0;
}

//复杂度分析：计算时间在对作业集的排序，最坏情况下O(nlogn)，所需空间O(n)