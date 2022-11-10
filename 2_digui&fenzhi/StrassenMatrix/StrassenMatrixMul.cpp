#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define SIZE 16
using namespace std;
/*
    A,B为n阶矩阵，n=2^k, C=AB -->通常：C中n^2元素，W(n)=O(n^3)  
    简单分治算法求解，矩阵分块，W(n)=8W(n/2)+cn^2,W(1)=1,推出仍为O(n^3)
    Strassen矩阵乘法：设计M1,M2,..,M7七个子问题
    M1=A11(B12-B22)
    M2=(A11+A12)B22
    M3=(A21+A22)B11
    M4=A22(B21-B11)
    M5=(A11+A22)(B11+B22)
    M6=(A12-A22)(B21+B22)
    M7=(A11-A21)(B11+B12)
    ---------
    C11=M5+M4-M2+M6
    C12=M1+M2
    C21=M3+M4
    C22=M5+M1-M3-M7------>W(n)=7W(n/2)+18(n/2)^2,W(1)=1-->W(n)=O(n^(log7))<O(n^3)
*/

void ReadMatrix(double A[][SIZE],int N){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            scanf("%lf",&A[i][j]);//输入A数组的内容
        }
    }
}

void WriteMatrix(double A[][SIZE],int N){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%.1f ",A[i][j]);//输入A数组的内容
        }
        printf("\n");
    }
}

void MatrixAdd(double A[][SIZE],double B[][SIZE],double Result[][SIZE],int N){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            Result[i][j]=A[i][j]+B[i][j];
        }
    }
}

void MatrixSubtrac(double A[][SIZE],double B[][SIZE],double Result[][SIZE],int N){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            Result[i][j]=A[i][j]-B[i][j];
        }
    }
}

void StrassenAlgorithm(double A[][SIZE],double B[][SIZE],double C[][SIZE],int N){
    if(N==1){
        C[0][0]=A[0][0]*B[0][0];//一维则直接对应元素相乘
        return;
    }
    else{
        int Divide = (int)(N/2);//分块，一个分为四个块
        
        double A11[SIZE][SIZE],A12[SIZE][SIZE],A21[SIZE][SIZE],A22[SIZE][SIZE];//用于定义每一个小块
        double B11[SIZE][SIZE],B12[SIZE][SIZE],B21[SIZE][SIZE],B22[SIZE][SIZE];
        double C11[SIZE][SIZE],C12[SIZE][SIZE],C21[SIZE][SIZE],C22[SIZE][SIZE];
        double P1[SIZE][SIZE],P2[SIZE][SIZE],P3[SIZE][SIZE],P4[SIZE][SIZE],P5[SIZE][SIZE],P6[SIZE][SIZE],P7[SIZE][SIZE];
        double AResult[SIZE][SIZE],BResult[SIZE][SIZE];

        int i,j;
        for(i=0;i<Divide;i++){//初始化分块出来的每个矩阵的四个小块
            for(j=0;j<Divide;j++){
                A11[i][j]=A[i][j];
                A12[i][j]=A[i][j+Divide];
                A21[i][j]=A[i+Divide][j];
                A22[i][j]=A[i+Divide][j+Divide];

                B11[i][j]=B[i][j];
                B12[i][j]=B[i][j+Divide];
                B21[i][j]=B[i+Divide][j];
                B22[i][j]=B[i+Divide][j+Divide];
            }
        }

        //计算P1 to P7
        MatrixAdd(A11,A22,AResult,Divide); //a11+a22
        MatrixAdd(B11,B22,BResult,Divide); //b11+b22
        StrassenAlgorithm(AResult,BResult,P1,Divide);   //p1=(a11+a22)*(b11+b22);

        MatrixAdd(A21,A22,AResult,Divide); //a21+a22
        StrassenAlgorithm(AResult,B11,P2,Divide);       //p2=(a21+a22)*(b11)
        
        MatrixSubtrac(B12,B22,BResult,Divide); //b12-b22
        StrassenAlgorithm(A11,BResult,P3,Divide);       //p3=(a11)*(b12-b22)

        MatrixSubtrac(B21,B11,BResult,Divide); //b21-b11
        StrassenAlgorithm(A22,BResult,P4,Divide);       //p4=(a22)*(b21-b11)

        MatrixAdd(A11,A12,AResult,Divide); //a11+a12
        StrassenAlgorithm(AResult,B22,P5,Divide);       //p5=(a11+a12)*(b22)

        MatrixSubtrac(A21,A11,AResult,Divide); //a21-a11
        MatrixAdd(B11,B12,BResult,Divide);     //b11+b12
        StrassenAlgorithm(AResult,BResult,P6,Divide);   //p6=(a21-a11)*(b11+b12)

        MatrixSubtrac(A12,A22,AResult,Divide); //a12-a22
        MatrixAdd(B21,B22,BResult,Divide);     //b21+b22
        StrassenAlgorithm(AResult,BResult,P7,Divide);   //p7=(a12-a22)*(b21+b22)
        
        //计算c21,c22,c11,c22
        MatrixAdd(P3,P5,C12,Divide);    //c12=p3+p5
        MatrixAdd(P2,P4,C21,Divide);    //c21=p2+p4
        MatrixAdd(P1,P4,AResult,Divide);    //p1+p4
        MatrixAdd(AResult,P7,BResult,Divide);   //p1+p4+p7
        MatrixSubtrac(BResult,P5,C11,Divide);   //c11=p1+p4-p5+p7
        MatrixAdd(P1,P3,AResult,Divide);    //p1+p3
        MatrixAdd(AResult,P6,BResult,Divide);   //p1+p3+p6
        MatrixSubtrac(BResult,P2,C22,Divide);   //c22=p1+p3-p2+p6

        for(i=0;i<Divide;i++){
            for(j=0;j<Divide;j++){
                C[i][j]=C11[i][j];
                C[i][j+Divide]=C12[i][j];
                C[i+Divide][j]=C21[i][j];
                C[i+Divide][j+Divide]=C22[i][j];
            }
        }
    }
}


int main(){
    double A[SIZE][SIZE],B[SIZE][SIZE],C[SIZE][SIZE];
    int i,j;
    int N,M,Count=0;

    printf("What Is the Dimention: ");//输入维度 2
    scanf("%d",&N);
    M=N;
    printf("Matrix A:\n");//1 1 1 0
    ReadMatrix(A,M);
    printf("Matrix B:\n");//1 1 1 0
    ReadMatrix(B,M);

    StrassenAlgorithm(A,B,C,N); //A,B,C矩阵的阶都是N
    
    printf("Matrix A:\n\n");
    WriteMatrix(A,M);
    printf("Matrix B:\n\n");
    WriteMatrix(B,M);
    printf("The product of the two Matrix:\n\n");
    WriteMatrix(C,M);//2 1 1 1

    return 0;
}