#include<iostream>
#include<cstdio>
#include<random>
using namespace std;

/*
    线性序集中n个元素和一个正数k，找第k小的元素(n中的元素不重复)
    a[p:r]中随机找一个数i划分为a[p:i],a[i+1:r]，递归满足条件数组
    直到p=r，数组被分割成只剩下1个元素，该元素就是第k小的元素
*/

int n,k,len;

void Swap(int &a,int &b){
    int temp;
    temp=a;
    a=b;
    b=temp;
}

int Random(int x,int y){
    return x+rand()%(y-x);//找x和y中随机一个数
}

int Partition(int a[], int p, int r)//排序  将数组首元素a[p]作为基准数将数组分割
{
    //i指向首元素，j指向尾元素的下一个元素
    int i = p, j = r + 1;
    //将首元素作为基准数
    int x = a[p];
    while (1)
    {
        //i从基准数右边的元素开始找，直到找到第一个大于等于基准数的元素
        while (a[++i] < x && i < r);
        //j从尾元素开始找，直到找到第一个小于等于基准数的元素
        while (a[--j] > x);
        //若i>=j，说明基准数的位置已找到，为j
        if (i >= j)
        {
            break;
        }
        //交换两个元素，使得基准数左边的数均不大于它，右边的数均不小于它
        Swap(a[i], a[j]);
    }
    //将基准数归位
    a[p] = a[j];
    a[j] = x;
    //返回基准数的位置
    return j;
}

int RandomizedPartition(int a[],int p,int r){//在数组中随机选择一个数将数组分割
    int i=Random(p,r);//在p和r中随机找一个随机数
    Swap(a[i],a[p]);
    return Partition(a,p,r);
}

int RandomizedSelect(int a[], int p, int r, int k)//a[p->r]
{//线性划分
    //数组被分割成只剩下一个元素，该元素就是第k小的元素
    if (p == r)
    {
        return a[p];
    }
    //在数组中随机找一个数将数组分割，分成小于等于该基准的数组和大于该基准的数组
    int i = RandomizedPartition(a, p, r);
    //求较小数数组的长度
    len = i - p + 1;
    //若较小数数组的长度小于等于k，说明第k小的元素在这个数组内，将其递归
    if (k <= len)
    {
        return RandomizedSelect(a, p, i, k);
    }
    //否则，说明第k小的元素在较大数数组，将其递归
    else
    {
        return RandomizedSelect(a, i + 1, r, k - len);
    }
}

int main()
{
    
    cin>>n;//输入数组长度n 6
    int *a = new int[n];
    for (int i = 0; i < n; ++i)//输入数组
    {
        cin>>a[i];      //2 5 1 9 3 10
    }
    cin>>k;//输入第k小  //3
    int res = RandomizedSelect(a, 0, n - 1, k);
    cout<<res<<endl;    //3
    delete []a;
    return 0; //找第k小并返回
}
//算法分析：best:O(n),worst:O(n^2),平均时间复杂度:O(n)