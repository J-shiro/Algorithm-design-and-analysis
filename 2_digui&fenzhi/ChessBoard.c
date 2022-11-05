#include<stdio.h>
#define MAX 1025

//2^k × 2^k 的棋盘，用L型骨牌覆盖除特殊方格外其他全部方格，方格数4^k
//每个L型骨牌对应3个方格，数目：(4^k-1)/3

int k;                  //棋盘大小
int x,y;                //特殊方格的位置
int board[MAX][MAX];    //存放填充结果
int tile=1;             //用title全局变量来表示L型骨牌的编号，从1开始

void ChessBoard(int tr,int tc,int dr,int dc,int size){//
            //tr:棋盘左上角方格行号，tc:棋盘左上角方格列号
            //dr:特殊方格行号，dc:特殊方格列号  size=2^k
    if(size==1) return;//递归出口
    int t=tile++;//取一个L型骨牌，牌号为tile
    int s=size/2;//分割棋盘
    
    //考虑左上角象限
    if(dr<tr+s && dc<tc+s)                  //特殊方格在此象限中
        ChessBoard(tr,tc,dr,dc,s);
    else{                                   //特殊方格不在此象限中
        board[tr+s-1][tc+s-1]=t;            //用t号L型骨牌覆盖右下角
        ChessBoard(tr,tc,tr+s-1,tc+s-1,s);  //将右下角作为特殊方格继续处理该象限
    }
    //考虑右上角象限
    if(dr<tr+s && dc>=tc+s)                 //特殊方格在此象限中
        ChessBoard(tr,tc+s,dr,dc,s);         
    else{                                   //特殊方格不在此象限中
        board[tr+s-1][tc+s]=t;              //用t号L型骨牌覆盖左下角
        ChessBoard(tr,tc+s,tr+s-1,tc+s,s);  //将左下角作为特殊方格继续处理该象限
    }
    //考虑左下角象限
    if(dr>=tr+s && dc<tc+s)                 //特殊方格在此象限中
        ChessBoard(tr+s,tc,dr,dc,s);         
    else{                                   //特殊方格不在此象限中
        board[tr+s][tc+s-1]=t;              //用t号L型骨牌覆盖右上角
        ChessBoard(tr+s,tc,tr+s,tc+s-1,s);  //将右上角作为特殊方格继续处理该象限
    }
    //考虑左下角象限
    if(dr>=tr+s && dc>=tc+s)                //特殊方格在此象限中
        ChessBoard(tr+s,tc+s,dr,dc,s);         
    else{                                   //特殊方格不在此象限中
        board[tr+s][tc+s]=t;                //用t号L型骨牌覆盖左上角
        ChessBoard(tr+s,tc+s,tr+s,tc+s,s);  //将左上角作为特殊方格继续处理该象限
    }
}

int main(){
    k=3;
    x=1;y=2;
    int size=1<<k;  //size=2^k
    ChessBoard(0,0,x,y,size);
    for(int i=0;i<size;i++){//输出覆盖方案
        for(int j=0;j<size;j++){
            printf("%4d",board[i][j]);
        }
        printf("\n");
    }
    return 0;
}

/*算法分析:T(k)表示2^k × 2^k的棋盘求解时间
T(k)=1          当k=0
T(k)=4T(k-1)    当k>0  ----> T(k)=O(4^k)
*/