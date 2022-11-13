#include<iostream>
#include<bits/stdc++.h>
using namespace std;

/*
    凸多边形最优三角剖分：n边凸多边形P，将P分割成n-2个三角形，使各个三角形的权值之和最小
    以无向图表示，三角形的权值等于三条边权值相加
    输入凸多边形的边数n，(3<=n<=8)及顶点i到顶点j的弦的权值，输出最优权值和
    递推公式：t[i][j] = t[i][k] + t[k+1][j] + w(i-1,k,j)--->w(i-1,k,j)三边之和,t[i][j]表示多边形剖分最小权值和

*/

int array1[200][200];

//剖分三角形的周长 
int C_triangle(int i,int k,int j){
	return array1[i][k] + array1[k][j] + array1[i][j];
} 

int main(){
	
	int N;
	cin >> N;//输入凸多边形的边数n
	int m[200][200];
	
	//数组中存的是边长和弦长 
	for(int i = 0; i < N; i++){
		for(int j  = i; j < N; j++){
			cin >> array1[i][j];
		}
	}
/*
    输入：
    0 2 2 3 1 4 :1->1-6
    0 1 5 2 3   :2->2-6
    0 2 1 4     :3->3-6
    0 6 2       :4->4-6
    0 1         :5->5-6
    0           :6->6-6 到自己则权值都为0
*/


	for(int i = 0; i <= N; i++){
		m[i][i] = 0;//dp数组，动态规划，类似于矩阵连乘问题，先将对角线置为0
	}
		
	// //开始划分网格和更新
	// for(int i = N - 1; i >= 1; i--){//此处为N-1个循环，由于第一位以及被0占了，剩余N-1
    // //i=5,4,3,2,1
	// 	for(int j = i+1; j <= N - 1; j++){//这里j从i+1开始，因为从i开始每次m[i][i] = 0; 
    //     //5->5 4->5 3->5 2->5             //这里j <= N 表示的是这一行到最后比如m[i][N] 
	// 		//初始化二维数组 
	// 		m[i][j] = m[i][i] + m[i+1][j] + C_triangle(i-1,i,j);//初始化公式ij=ii+(i+1)j+f(i-1,i,j)
			
	// 		for(int k = i+1; k < j; k++){
	// 			int temp = m[i][k] + m[k+1][j] + C_triangle(i-1,k,j);
				
	// 			if(temp < m[i][j]){
	// 				 m[i][j] = temp;
	// 			} 
	// 		} 
	// 	}
	// }
    
    //按照教材中的方式来
    for(int r = 2; r <= N; r++){//此处为N-1个循环，由于第一位以及被0占了，剩余N-1
		for(int i = 1; i <= N-r+1; i++){//N-r+1为第一项的范围
			//初始化二维数组 
			int j=i+r-1;//i+r-1为第二项的范围
            m[i][j] = m[i][i] + m[i+1][j] + C_triangle(i-1,i,j);//初始化公式ij=ii+(i+1)j+f(i-1,i,j)
			
			for(int k = i+1; k < i+r-1; k++){//切分i+1到i+r-1之间找一个点进行剖分
				int temp = m[i][k] + m[k+1][j] + C_triangle(i-1,k,j);
				
				if(temp < m[i][j]){
					 m[i][j] = temp;
				} 
			} 
		}
	}

    for(int i=1;i<=N;i++){
        for(int j=0;j<N;j++){
            cout<<setw(3)<<m[i][j];
        }
        cout<<endl;
    }

	cout << m[1][N-1];
    return 0;
}

/*
    测试1：54
    6
    0 2 3 1 5 6
    0 3 4 8 6  
    0 10 13 7
    0 12 5
    0 3
    0
    测试2:24
    6
    0 2 2 3 1 4
    0 1 5 2 3
    0 2 1 4
    0 6 2
    0 1
    0
*/


//算法分析，耗时O(n^3)