//////////////////////////////////////////////////////
// 程序名称：有宽度线段的连接处处理
// 功	能：设计具有宽度的画线算法，并处理线条连接处出现缺口的问题
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-3-10

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <cmath>
using namespace std;

void bresenham(int x0, int y0, int x1, int y1, int color) {
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int erro = (dx > dy ? dx : -dy) / 2;

	while (putpixel(x0, y0, color), x0 != x1 || y0 != y1) {
		int e2 = erro;
		if (e2 > -dx) {
			erro -= dy;
			x0 += sx;
		}
		if (e2 < dy) {
			erro += dx;
			y0 += sy;
		}
	}
}


int main() {
	//用户定义相关参数
	int x0, y0, x1, y1, width, x2, y2, x3, y3;
	cout << "Please input the first starting point:" << endl;
	cin >> x0 >> y0;
	cout << "Please input the first ending point:" << endl;
	cin >> x1 >> y1;
	cout << "Please input the second starting point:" << endl;
	cin >> x2 >> y2;
	cout << "Please input the second ending point:" << endl;
	cin >> x3 >> y3;
	//cout << "Please input the half width of your lines:" << endl;
	//cin >> width;//输入半宽度
	int mycolor[2] = { RED, YELLOW };

	/*
	double flag1 = (double)(y1 - y0) / (x1 - x0);
	double flag2 = (double)(y3 - y2) / (x3 - x2);
	//flag1>1 or flag1<-1 斜率大于1 采用横向补点
	//flag1<1 and flag1>-1 斜率小于1 采用纵向补点
	//flag2同理可得
	*/

	//图形界面
	initgraph(640, 480);

	//线性加粗
	bresenham(x0, y0, x1, y1, mycolor[0]);
	//宽度确定为10像素
	for (int i = 0; i < 5; i++) {
		bresenham(x0 + i, y0, x1 + i, y1, mycolor[0]);
		bresenham(x0 - i, y0, x1 - i, y1, mycolor[0]);
	}
	for (int i = 0; i < 5; i++) {
		bresenham(x2 + i, y2, x3 + i, y3, mycolor[1]);
		bresenham(x2 - i, y2, x3 - i, y3, mycolor[1]);
	}

	//补充缺口


	_getch();
	closegraph();
	return 0;
}