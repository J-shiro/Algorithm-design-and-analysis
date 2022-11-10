#include<iostream>
using namespace std;

//二分搜索
/*
    数组T，下标从l到r，输入x：x在T中输出下标，否则为-1
*/

int BinarySearch(int T[],int x,int n){
    int l=0,r=n-1;
    while(l<=r){
        int mid=(l+r)>>1;//等价于(l+r)/2
        if(x<T[mid]){
            r=mid-1;
        }else if(x>T[mid]){
            l=mid+1;
        }else{
            return mid;
        }
    }
    return -1;
}


int main(){
    int T[] = {1,2,3,4,5,6,7,8,9,12};//一定是一个有序数组
    int n = sizeof(T)/sizeof(int);//
    int x=4;
    cout<<"position: "<<BinarySearch(T,x,n)<<endl;
    return 0;
}