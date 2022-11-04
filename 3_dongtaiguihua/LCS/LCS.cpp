#include<iostream>
#include<math.h>
#include<vector>
using namespace std;

#define MAX 51  //序列中最多的字符个数

int m,n;
string a,b;
int dp[MAX][MAX];       //动态规划数组
vector<char> subs;      //存放LCS最长公共子序列
int count=0;            //subs中的字符数量

void LCSlength(){       //求dp动态规划数组  
    int i,j;
    for(i=0;i<=m;i++)   //边界条件
        dp[i][0]=0;
    for(j=0;j<=n;j++)   //边界条件
        dp[0][j]=0;
    for(i=1;i<=m;i++){  //由此,该函数时间复杂度为O(m×n)
        for(j=1;j<=n;j++){  //两重循环处理a,b所有字符
            if(a[i-1]==b[j-1])                         //情况1:a,b数组最后一个相同直接加一
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=max(dp[i][j-1],dp[i-1][j]);   //情况2,3:a,b数组最后一个不同情况下,
        }                                              //为左或上其中最大的一个
    }
}

void Buildsubs(){   //由dp数组反推构造subs:LCS最长公共子序列
    int k=dp[m][n]; //k为a和b最长公共子序列长度
    int i=m;
    int j=n;
    while(k>0){
        if(dp[i][j]==dp[i-1][j])
            i--;
        else if(dp[i][j]==dp[i][j-1])
            j--;
        else{
            subs.push_back(a[i-1]); //subs中添加a[i-1]字符
            count++;
            i--;
            j--;
            k--;
        }
    }
}

int main(){
    a="abcbdb";
    b="acbbabdbb";
    m=6;
    n=9;
    LCSlength();
    Buildsubs();
    for(int x=count-1;x>=0;x--){
        cout<<subs[x];
    }
    cout<<endl;
    return 0;
}

/*LCSlength算法中，使用了两重循环，对于长度分别为m和n的序列
时间复杂度为O(m×n),空间复杂度为O(m×n)
*/