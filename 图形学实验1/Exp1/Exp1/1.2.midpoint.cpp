//////////////////////////////////////////////////////
// �������ƣ��е㻭��
// ��	�ܣ����е㻭���㷨���Ʋ���б�ʵ�����
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-3-3

#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <iostream>
using namespace std;

void MidPointLine(int x0, int y0, int x1, int y1, int color) {
	int dx, dy, increE, increNE, d, x, y;
	dx = x1 - x0;
	dy = y1 - y0;
	d = dx - 2 * dy;
	increE = -2 * dy;
	increNE = 2 * (dx - dy);
	x = x0;
	y = y0;
	putpixel(x, y, color);
	//б��0~1
	while (x < x1) {
		if (d > 0) {
			d += increE;
			x++;
		}
		else {
			d += increNE;
			y++;
			x++;
		}
		putpixel(x, y, color);
	}
}

int main(){
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
			MidPointLine(x0, y0, x1, y1, WHITE);
			setfillcolor(GREEN);
			fillrectangle(m.x - 3, m.y - 3, m.x + 3, m.y + 3);
		case WM_KEYDOWN:
			if (m.vkcode == VK_ESCAPE)
				return 0;	// �� ESC ���˳�����
		}
	}
	closegraph();
	return 0;
}