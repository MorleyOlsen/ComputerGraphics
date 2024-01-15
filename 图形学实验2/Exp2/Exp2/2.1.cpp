//////////////////////////////////////////////////////
// 程序名称：CS裁剪
// 功	能：用Cohen-Sutherland算法实现直线段裁剪
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-3-17

#include <graphics.h>
#include <conio.h>
#include <iostream>
using namespace std;

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
int XL, XR, YB, YT;

int encode(float x, float y, int* code) {
	int c = 0;
	if (x < XL) {
		c = c | LEFT;
	}
	else if (x > XR) {
		c = c | RIGHT;
	}
	if (y < YB) {
		c = c | BOTTOM;;
	}
	else if (y > YT) {
		c = c | TOP;
	}
	*code = c;
	return 0;
}

int CSLineClip(float x1, float y1, float x2, float y2) {
	int code1, code2, code;
	float x, y;
	encode(x1, y1, &code1);
	encode(x2, y2, &code2);
	while (code1 != 0 || code2 != 0) {
		if ((code1 & code2) != 0) {
			return 0;
		}
		code = code1;
		if (code1 == 0) {
			code = code2;
		}
		//找交点，通过边界找坐标值
		if ((LEFT & code) != 0) {
			x = XL;
			y = y1 + (y2 - y1) * (XL - x1) / (x2 - x1);
		}
		else if ((RIGHT & code) != 0) {
			x = XR;
			y = y1 + (y2 - y1) * (XR - x1) / (x2 - x1);
		}
		else if ((BOTTOM & code) != 0) {
			y = YB;
			x = x1 + (x2 - x1) * (YB - y1) / (y2 - y1);
		}
		else if ((TOP & code) != 0) {
			y = YT;
			x = x1 + (x2 - x1) * (YT - y1) / (y2 - y1);
		}
		//更新范围内的交点
		if (code == code1) {
			x1 = x;
			y1 = y;
			encode(x, y, &code1);
		}
		else {
			x2 = x;
			y2 = y;
			encode(x, y, &code2);
		}
	}
	setlinecolor(WHITE);
	line(x1, y1, x2, y2);
	return 0;
}

int main() {
	//用户定义a、b坐标
	float xa, ya, xb, yb;
	cout << "please input the coordinate of A point:" << endl;
	cin >> xa >> ya;
	cout << "please input the coordinate of B point:" << endl;
	cin >> xb >> yb;
	int x0, y0, x1, y1;
	//0->left bottom; 1->right top;

	//图形界面
	initgraph(640, 480);
	ExMessage m;
	//勾勒AB线段：绿色
	setlinecolor(GREEN);
	line(xa, ya, xb, yb);
	while (true) {
		m = getmessage(EX_MOUSE | EX_KEY);
		switch (m.message) {
		case WM_LBUTTONDOWN:
			x0 = m.x;
			y0 = m.y;
			setlinecolor(WHITE);
			setfillcolor(GREEN);
			fillrectangle(m.x - 3, m.y - 3, m.x + 3, m.y + 3);
		case WM_RBUTTONDOWN:
			x1 = m.x;
			y1 = m.y;
			setlinecolor(WHITE);
			setfillcolor(GREEN);
			fillrectangle(m.x - 3, m.y - 3, m.x + 3, m.y + 3);
			//判断用户是左上~右下 / 左下~右上 / 右上~左下 / 右下~左上
			if ((x0 < x1) && (y0 > y1)) {
				XL = x0;
				XR = x1;
				YB = y1;
				YT = y0;
			}
			else if ((x0 < x1) && (y0 < y1)) {
				XL = x0;
				XR = x1;
				YB = y0;
				YT = y1;
			}
			else if ((x0 > x1) && (y0 > y1)) {
				XL = x1;
				XR = x0;
				YB = y1;
				YT = y0;
			}
			else if ((x0 > x1) && (y0 < y1)) {
				XL = x1;
				XR = x0;
				YB = y0;
				YT = y1;
			}
			//勾勒裁剪框
			setlinecolor(RED);
			line(XL, YT, XR, YT);
			line(XL, YB, XR, YB);
			line(XL, YT, XL, YB);
			line(XR, YT, XR, YB);
			//裁剪部分为白色
			CSLineClip(xa, ya, xb, yb);
		case WM_KEYDOWN:
			if (m.vkcode == VK_ESCAPE)
				return 0;	// 按 ESC 键退出程序
		}
	}
	closegraph();
	return 0;
}