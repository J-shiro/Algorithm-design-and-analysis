#include<stdio.h>
#include<stdbool.h>
/*
    取一个值排在确定位置，左边为小于该值的数，右边为大于该值的数
    f(a,s,t) >不做任何事 当a[s..t]中长度<2时
    f(a,s,t) >i=Partition(a,s,t) [f(a,s,i-1),f(a,i,t)]  其他情况
*/

int Partition(int a[],int s,int t){//划分算法
    int i=s,j=t;
    int tmp = a[s];//用序列的第一个记录作为基准
    while(i!=j){//从序列两端交替向中间扫描，直到i=j为止
        while(j>i && a[j]>=tmp){    //从右向左扫描，找第一个关键字小于tmp的a[j]
            j--;                    //a[j]前移到a[i]位置
        }
        a[i]=a[j];
        while(i<j && a[i]<=tmp){    //从左向右扫描，找第一个关键字大于tmp的a[i]
            i++;                    //a[i]后移到a[j]位置
        }
        a[j]=a[i];
    }//跟书上的代码有所不同，此处tmp会交换，一直改变位置
    a[i]=tmp;
    return i;
}

int Partition2(int a[],int s,int t){//书中的方法
    int i=s,j=t+1;
    int x=a[s];
    while(true){
        while(a[++i]<x&&i<t);
        while(a[--j]>x);
        if(i>=j)
            break;
        int tmp=a[i];
        a[i]=a[j];
        a[j]=tmp;
    }
    a[s]=a[j];
    a[j]=x;
    return j;
}

void QuickSort(int a[],int s,int t){
    if(s<t){               //序列内至少存在2个元素的情况
        int i = Partition(a,s,t);
        QuickSort(a,s,i-1);//对左子序列递归排序
        QuickSort(a,i+1,t);//对右子序列递归排序
    }
}

int main(){
    int a[10] = {2,5,1,7,10,6,9,4,3,8};
    QuickSort(a,0,9);
    for(int i=0;i<10;i++){
        printf("%d ",a[i]);
    }
    return 0;
}

/*
   best:每次划分基准恰好为中值
        T(n)=O(1)           n≤1
        T(n)=2T(n/2)+O(n)   n>1 ---->T(n)=O(nlogn)
   worst:每次分别包含n-1个元素和1个元素
        T(n)=O(1)           n≤1
        T(n)=T(n-1)+O(n)    n>1 ---->T(n)=O(n^2)
*/