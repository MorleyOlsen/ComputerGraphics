//////////////////////////////////////////////////////
// 程序名称：Bezier曲线
// 功	能：绘制Bezier曲线，并采用自行设计输入和交互修改数据点的方式。
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-4-28

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <math.h>
using namespace std;

//特征多边形的特征
int n;
int px[100], py[100];

//初始化特征多边形
void initialize() {
	cout << "please input the number of your points (no more than 100)" << endl;
	cin >> n;
	cout << "please input each coordinate of your points in order" << endl;
	for (int i = 0; i < n; i++) {
		cin >> px[i] >> py[i];
	}
	cout << "successfully set" << endl;
}

//递归
int Factorial(int nn) {
	if (nn == 0 || nn == 1) return 1;
	else return nn * Factorial(nn - 1);
}

//绘制bezier曲线
void Bezier() {
	int nn = n - 1;
	//line(px[0], py[0], px[1], py[1]);
	double i = 0, n1, n2;
	n1 = Factorial(nn);
	moveto(px[0], py[0]);
	POINT point;

	//在[0,1]内循环
	for (; i <= 1; i += 0.01) {
		point.x = 0;
		point.y = 0;
		for (int j = 0; j <= nn; j++) {
			n2 = (n1 / (Factorial(j) * Factorial(nn - j))) * pow(i, j) * pow(1 - i, nn - j);
			point.x += n2 * px[j];
			point.y += n2 * py[j];
		}
		lineto(point.x, point.y);
	}
	lineto(px[n - 1], py[n - 1]);

	//描绘用户定义的点
	for (int ii = 0; ii < n; ii++) {
		setfillcolor(GREEN);
		fillcircle(px[ii], py[ii], 3);
	}
}

//主函数
int main() {
	//初始化
	initialize();
	initgraph(640, 480);
	ExMessage m;

	//绘制图像
	while (1) {
		m = getmessage(EX_MOUSE | EX_KEY);
		switch (m.message) {
			//右键修改坐标信息
		    case WM_RBUTTONDOWN:
				closegraph();
				int arr, newx, newy;
				//输入数组中的坐标，进行修改
				cout << "which point do you want to change? please input its array number" << endl;
				while (1) {
					cin >> arr;
					if (arr >= n) {
						cout << "input error, try again" << endl;
					}
					else {
						break;
					}
				}
				cout << "please input the reset coordinate" << endl;
				cin >> newx >> newy;
				px[arr] = newx;
				py[arr] = newy;
				cout << "successfully reset, please wait a second to see a new graph" << endl;
				initgraph(640, 480);
			//左键绘制
			case WM_LBUTTONDOWN:
				Bezier();
			//退出图形化界面
			case WM_KEYDOWN:
				if (m.vkcode == VK_ESCAPE) {
					return 0;
				}
		}
	}
	_getch();
	closegraph();
	return 0;
}