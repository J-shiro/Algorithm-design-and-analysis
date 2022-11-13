#include<iostream>
#include<algorithm>
#include<vector>
#include<bits/stdc++.h>
#include<queue>
using namespace std;
#define MAXN 20
/*
    多机调度：n个独立作业，m台相同机器，每个机器可在任何一台机器上加工处理
    ，不可间断、拆分，尽可能时间短，贪心策略：最长处理时间作业优先
    m≥n,机器i的[0,ti]时间区域分配给作业i
    m<n,将n个作业处理时间从大到小排序，依次分配给空闲处理机
*/

/*
    1,2,3,4,5,6,7作业,  M1,M2,M3机器
    时间2,14,4,16,6,5,3
    M1:----------------
       4
    M2:-----------------
       2             7
    M3:-----------------
       5     6    3   1
*/

int n=7;//7个作业
int m=3;//3台机器

struct Job{
	int ID;
	int time;
};
struct MachineNode{
	int ID;
	int aval;//空闲时间点
};


bool operator<(MachineNode p1,MachineNode p2){
    return p1.aval>p2.aval;
}

bool compare(Job a,Job b){
    return a.time>b.time;
}

void Greedy(Job a[],int n,int m){
    if(n<=m){
        cout<<"every job can has a machine"<<endl;//作业数小于机器数
        return;
    }
    sort(a+1,a+n+1,compare);//升序排序
    //for(int i=1;i<=n;i++){cout<<a[i].time<<endl;} //验证升序排列

    MachineNode machine[m];
    for(int i=1;i<=m;i++){
        machine[i].aval=0;
        machine[i].ID=i;
    }
    priority_queue<MachineNode> tmp;
    for(int i=1;i<=m;i++){
        tmp.push(machine[i]);
    }
    for(int i=1;i<=n;i++){
        MachineNode x=tmp.top(); tmp.pop();
        cout<<"put the machine "<<x.ID<<" from "<<x.aval<<" to "
            <<(x.aval+a[i].time)<<" allocated to job "<<a[i].ID<<endl;
        x.aval+=a[i].time;
        tmp.push(x);
    }
}

int main(){
    int x[n+1]={0,2,14,4,16,6,5,3};//第一位不用
    Job a[n];
    for(int i=1;i<=n;i++){
        a[i].ID=i;
        a[i].time=x[i];
    }
    Greedy(a,n,m);
    return 0;
}

//n≤m,O(1)
//n>m,排序时间O(nlogn),初始化堆需要O(m),关于堆的抽出和插入耗时O(nlogn)
//时间：O(nlogn)