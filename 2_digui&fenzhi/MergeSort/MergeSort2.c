#include<stdio.h>
#include<stdlib.h>

/*  自顶向下的二路归并排序算法--->递归方法  a[low...high]
    分解：a[]一分为二，mid=(low+high)/2,递归对a[low..mid]、a[mid+1..high]分解
         最终得到子序列长度为1
    合并：将已排序的两个子序列a[low..mid]和a[mid+1..high]归并
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

void MergeSort(int a[],int low,int high){//二路归并算法
    int mid;
    if(low<high){                   //子序列有两个或以上的元素
        mid=(low+high)/2;           //取中间位置
        MergeSort(a,low,mid);       //子序列排序
        MergeSort(a,mid+1,high);    //子序列排序
        Merge(a,low,mid,high);      //两子序列合并
    }
}

int main(){
    int x[10] = {2,5,1,7,10,6,9,4,3,8};
    MergeSort(x,0,9);
    for(int i=0;i<10;i++){
        printf("%d ",x[i]);
    }
    printf("\n");
    return 0;
}

/*  
    MergeSort()算法执行时间设为T(n),Merge()算法执行时间为O(n)
    T(n)=1              n=1
    T(n)=2T(n/2)+O(n)   n>1
    推出T(n)=O(nlogn)
*/