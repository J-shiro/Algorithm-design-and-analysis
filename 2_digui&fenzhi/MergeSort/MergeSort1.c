#include<stdio.h>
#include<stdlib.h>  //malloc free函数
/*  自底向上的二路归并排序：循环⌈logn⌉次，length依次取1,2,4...--->分治策略
    分解：将原序列分解成length长度的若干子序列
    合并：将相邻两个子序列调用Merge函数归并
*/
void Merge(int a[],int low,int mid,int high){
    int *tmpa;//开辟临时空间，临时数组
    int i=low,j=mid+1,k=0;
    tmpa = (int *)malloc((high-low+1)*sizeof(int));
    while(i<=mid&&j<=high){//分别扫描两个子序列
        if(a[i]<=a[j]){
            tmpa[k]=a[i];//小的放在tmpa中
            i++;
            k++;
        }
        else{
            tmpa[k]=a[j];
            j++;
            k++;
        }
    }
    while(i<=mid){//看哪个子序列未扫描完，将剩余的元素放入tmpa
        tmpa[k]=a[i];
        i++;
        k++;
    }
    while(j<=high){
        tmpa[k]=a[j];
        j++;
        k++;
    }
    for(k=0,i=low;i<=high;i++,k++){//将tmpa复制到a数组中
        a[i]=tmpa[k];
    }
    free(tmpa);//释放tmpa所占内存空间
}

void MergePass(int a[],int length,int n){//一趟二路归并排序
    int i;
    for(i=0;i+2*length-1<n;i=i+2*length){//归并length长的两个相邻子序列
        Merge(a,i,i+length-1,i+2*length-1);//包含了余下一个子序列的情况
    }
    if(i+length-1<n)              //讨论余下两个子序列，后者长度小于length
        Merge(a,i,i+length-1,n-1);//这是MergePass()将n作为参数的原因,归并两个子序列
}

void MergeSort(int a[],int n){//二路归并算法，此处未使用递归算法实现
    int length;               //所以分治法算法并非一定采用递归算法实现
    for(length=1;length<n;length=length*2){
        MergePass(a,length,n);
    }
}

int main(){
    int x[10] = {2,5,1,7,10,6,9,4,3,8};
    MergeSort(x,10);
    for(int i=0;i<10;i++){
        printf("%d ",x[i]);
    }
    printf("\n");
    return 0;
}