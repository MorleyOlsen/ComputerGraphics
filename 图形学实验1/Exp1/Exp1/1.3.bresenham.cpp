//////////////////////////////////////////////////////
// 程序名称：bresenham画线：加强版
// 功	能：用bresenham画线算法绘制任意斜率的曲线
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-3-3

#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <iostream>
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
	initgraph(640, 480);
	ExMessage m;
	int x0, y0, x1, y1;
	while (true) {
		m = getmessage(EX_MOUSE | EX_KEY);
		switch (m.message) {
		case WM_LBUTTONDOWN:
			x0 = m.x;
			y0 = m.y;
			setfillcolor(GREEN);
			fillrectangle(m.x - 3, m.y - 3, m.x + 3, m.y + 3);
		case WM_RBUTTONDOWN:
			x1 = m.x;
			y1 = m.y;
			bresenham(x0, y0, x1, y1, WHITE);
			setfillcolor(GREEN);
			fillrectangle(m.x - 3, m.y - 3, m.x + 3, m.y + 3);
		case WM_KEYDOWN:
			if (m.vkcode == VK_ESCAPE)
				return 0;	// 按 ESC 键退出程序
		}
	}
	closegraph();
	return 0;
}