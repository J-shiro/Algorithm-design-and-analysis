#include<iostream>
using namespace std;

//全排列问题
/*
    R={r1,r2,..,rn}要进行排列的n个元素，Ri=R-{ri}
    R的全排列：1.n=1,Perm(R)=(r)，r是R中唯一元素
              2.n>1,Perm(R)由(r1)Perm(R1),(r2)Perm(R2),..,(rn)Perm(Rn)构成
*/

void Swap(int &a,int &b){
    int temp=a;
    a=b;
    b=temp;
}

void Perm(int list[],int k,int m){      //产生list[k:m]的所有排列
    if(k==m){                           //只剩下1个元素
        for(int i=0;i<=m;i++)
            cout<<list[i]<<" ";
        cout<<endl;
    }
    else{
        for(int i=k;i<=m;i++){//每次把第i个交换到首部，对除首部外其他序列进行全排列
            Swap(list[k],list[i]);
            Perm(list,k+1,m);
            Swap(list[k],list[i]);//将首部调换回来，方便下次排序
        }
    }
}

int main(){
    int a[6] = {1,2,3,4,5,6};
    Perm(a,0,5);
    return 0;
}