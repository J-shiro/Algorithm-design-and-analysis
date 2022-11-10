#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
/* 
    平面点对问题：平面点集P中n个点，输出P中两个点，距离最小
    蛮力算法：C(n,2)个点对，计算--->O(n^2)
    分治策略：P化为大小相等的PL和PR，分别计算PL和PR中最近点对，-计算PL和PR中各一个点的最近点对
*/
/*
    分解：对所有的点按照x坐标、y坐标从小到大排序，据下标分解，使点集分为两个集合，递归寻找两个集合的最近点对，取它们最小值d
    合并：以中间点的x坐标mid划分一个[mid-d,mid+d]的区域，获取区域中所有的点，遍历这些点，看是否存在距离小于d的点对
*/

const double INF = 1e20;//一个点对的最大距离
const int N = 30001;//点数
struct Point {      //点的结构体定义
	double	x;
	double	y;
}
point[N];  //点数组
int n;     //实际输入的点数

Point result[2];  //结果数组

int tmpt[N];    //用于记录位于区域[mid-d,mid+d]的点

bool cmpxy(const Point &a, const Point &b) {    //按照x坐标、y坐标的顺序比较两个点的大小
	if ( a.x != b.x ) {                         //和sort函数一起使用
		return(a.x < b.x);
	}
	return(a.y < b.y);
}

bool cmpy(const int &a, const int &b) {         //按照y坐标比较两个点的大小
	return(point[a].y < point[b].y);
}

double min(double a, double b) {                //返回两个double值中的最小值
	return(a < b ? a : b);
}

double dis(int i, int j) {                      //输出两个位置的点的距离的平方
	double	dis_x = point[i].x - point[j].x;
	double	dis_y = point[i].y - point[j].y;
	return(dis_x * dis_x + dis_y * dis_y);
}
/**
 * 返回集合中的最小距离点对的距离
 * left：集合的左边界点位置，right：集合的右边界位置
 * 使用分治算法
 */
double Closest_Pair(int left, int right) {//left和right表示左右边界为第几个点/id号，并非x坐标
	
    double d = INF;//最小距离d,初始化为无穷大
	/* 如果只有一个点，直接返回最小距离d */
	if (left == right) {
		return d;
	}
	/* 如果只有两个点，直接返回两个点的距离 */
	if (left + 1 == right) {
		return dis(left, right);
	}

	/* 集合中间点的位置mid，根据mid将集合分成两部分 */
	int mid = (left + right) / 2;
	/* 返回左边集合的最小距离点对的距离 */
	double d1 = Closest_Pair(left, mid);
	/* 返回右边集合的最小距离点对的距离 */
	double d2 = Closest_Pair(mid + 1, right);
	/* 取两个最小距离的最小值 */
	d = min(d1, d2);

	int i, j, k = 0;
	/*关键点：---> 获取区域[mid-d,mid+d]的所有点 */
	for (i = left; i <= right; i++) {
		if (fabs(point[mid].x - point[i].x) <= d) {//fabs()对浮点数取绝对值，横坐标相减大于d则距离一定大于d
			tmpt[k++] = i;//k初始为0，将id号放入tmpt数组中记录
		}
	}
	/* 将区域中的点按照y坐标排序 */
	sort(tmpt, tmpt + k, cmpy);
	/* 遍历这个区域中的点，找到最小距离 */
	for (i = 0; i < k; i++) {
		/*
		 * 如果i点与j点的y坐标的距离大于d，那么i点与j点之后的点y坐标距离一定也大于d
		 * 两个点的y坐标距离大于d，那么两个点的距离一定大于d，可以提前结束遍历
		 */
		for (j = i + 1; j < k && point[tmpt[j]].y - point[tmpt[i]].y < d; j++) {
			double d3 = dis(tmpt[i], tmpt[j]);//tmpt[i]指的是i对应的那个点的id号
			if ( d > d3 ) {
				/*
				 * 如果有两个点对之间的距离小于d
				 * 那么得到新的最小距离
				 */
				d = d3;
                result[0].x=point[tmpt[i]].x;
                result[0].y=point[tmpt[i]].y;
                result[1].x=point[tmpt[j]].x;
                result[1].y=point[tmpt[j]].y;
			}
		}
	}
	return d;
}
int main() {
	//cin >> n;   //输入点数
    n = 8;
    double a[8][2]={{1,1},{2,2},{4,4},{8,8},{2,2.8},{5,6},{7,9},{11,11}};
	for (int i = 0; i < n; i++) {
		//cin >> point[i].x >> point[i].y;    //将点赋值
        point[i].x=a[i][0];
        point[i].y=a[i][1];
	}
	
	sort(point, point + n, cmpxy);          //根据点集的x坐标、y坐标将点集排序
	/* 输出最邻近点对距离的平方，并小数点后两位 */
	cout << fixed << setprecision(2) << Closest_Pair(0, n - 1)<<endl;
    cout<<setprecision(0)<<"("<<result[0].x<<","<<result[0].y<<") and ("<<result[1].x<<","<<result[1].y<<")";
	return(0);
}