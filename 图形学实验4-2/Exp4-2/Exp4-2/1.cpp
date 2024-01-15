//////////////////////////////////////////////////////
// 程序名称：正等轴测投影图
// 功	能：实现预设三维物体的正等轴测投影图。
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-4-14

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <math.h>
using namespace std;

//和分割线之间的距离
const int gap = 50;
//预设三维体的点坐标
int X[33] = { 0,0,0,0,0,0,0,0,100,100,0,100,100,100,100,100,100,100,100,0,0,0,0,100,100,100,100,0,0,0,0,100,100 };
int Y[33] = { 0,0,250,250,200,150,0,0,0,0,0,0,150,200,250,250,0,0,150,150,0,150,200,200,150,200,250,250,200,250,250,250,250 };
int Z[33] = { 100,0,0,50,50,100,100,0,0,100,100,100,100,50,50,0,0,100,100,100,100,100,50,50,100,50,50,50,50,50,0,0,50 };
//顶点总数
const int num = 33;

//正等轴测图绘制
void fun() {
	POINT* p = new POINT[num];
	for (int i = 0; i < num; i++) {
		p[i].x = 0.7071 * X[i] - 0.7071 * Y[i] + 500;
		p[i].y = 0.4082 * X[i] + 0.4082 * Y[i] - 0.8165 * Z[i] + 350;
	}
	for (int i = 0; i < num - 1; i++) {
		setcolor(YELLOW);
		line(p[i].x, p[i].y, p[i + 1].x, p[i + 1].y);
	}
	free(p);
}

int main() {
	initgraph(1000, 700);
	//调用函数
	fun();
	_getch();
	closegraph();
	return 0;
}