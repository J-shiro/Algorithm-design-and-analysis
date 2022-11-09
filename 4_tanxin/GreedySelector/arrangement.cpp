#include<iostream>
#include<stdbool.h>
#include<memory.h>
#include<algorithm>
#define MAX 100
using namespace std;
/*
    一个需要使用某一资源的n个活动所组成的集合S，S={1,..,n}，资源任何时候只能被一个活动占用，
    i活动开始时间bi，和结束时间ei，执行时间为ei-bi，最早活动执行时间为0
    若i和j有bi≥ej或bj≥ei，则称两活动兼容，使所有安排的活动个数最多

    一个活动用[bi,ei)表示，数组A存放所有活动A[i].b:活动起始时间，A[i].e:活动结束时间
*/

struct Action{//活动类型声明
    int b;  //活动起始时间
    int e;  //活动结束时间
    bool operator < (const Action &s) const{    //重载<关系函数
        return e <= s.e;    //用于按活动结束时间递增排序
    }
};
int n=11;
Action A[]={{0},{1,4},{3,5},{0,6},{5,7},{3,8},{5,9},{6,10},{8,11},
            {8,12},{2,13},{12,15}};     //下标0不用
bool flag[MAX]; //标记选择的活动
int Count = 0;  //选取的兼容活动个数

void solve(){                       //求解最大兼容活动子集
    memset(flag,0,sizeof(flag));    //初始化为false
    sort(A+1,A+n+1);                //A[1..n]按活动结束时间递增排序
    int preend=0;                   //前一个兼容活动的结束时间
    for(int i=1;i<=n;i++){
        if(A[i].b >= preend){       //找到一个兼容活动
            flag[i]=true;           //选择A[i]活动
            preend=A[i].e;          //更新preend位
        }
    }
}

int main(){
    solve();
    cout<<"result: ";
    for(int i=1;i<=n;i++){
        if(flag[i]==1){
            cout<< i << " ";
        }
    }
    return 0;
}


/*
    算法时间主要花费在排序上，排序时间为O(nlogn)，所以时间复杂度为O(nlogn)
*/