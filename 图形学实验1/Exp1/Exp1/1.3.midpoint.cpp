//////////////////////////////////////////////////////
// �������ƣ��е㻭�ߣ���ǿ��
// ��	�ܣ����е㻭���㷨��������б�ʵ�����
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-3-3

#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <iostream>
using namespace std;

void MidPointLine(int x0, int y0, int x1, int y1, int color)
{
	int a, b, d1, d2, d, x, y; 
	float m; 
	if (x1 < x0) { 
		d = x0; 
		x0 = x1; 
		x1 = d;
		d = y0; 
		y0 = y1; 
		y1 = d;
	}
	a = y0 - y1; //y��ֵ
	b = x1 - x0; //x��ֵ
	if (b == 0) {
		m = -1 * a * 100;
	}
	else {
		m = (float) a / (x0 - x1);
	}
	x = x0;
	y = y0;
	putpixel(x, y, color);

	//б����0~1
	if (m >= 0 && m <= 1){
		d = 2 * a + b; 
		d1 = 2 * a;
		d2 = 2 * (a + b);
		while (x < x1) {
			if (d <= 0) {
				x++;
				y++;
				d += d2;
			}
			else {
				x++;
				d += d1;
			}
			putpixel(x, y, color);
		}
	}

	//б����-1~0
	else if (m <= 0 && m >= -1) {
		d = 2 * a - b; 
		d1 = 2 * a - 2 * b;
		d2 = 2 * a;
		while (x < x1) {
			if (d > 0) {
				x++;
				y--;
				d += d1;
			}
			else {
				x++;
				d += d2;
			}
			putpixel(x, y, color);
		}
	}

	//б����1~��
	else if (m > 1) {
		d = a + 2 * b; d1 = 2 * (a + b), d2 = 2 * b;
		while (y < y1) {
			if (d > 0) {
				x++;
				y++;
				d += d1;
			}
			else { 
				y++;
			    d += d2; 
			}
			putpixel(x, y, color);
		}
	}

	//б���ڡ�~-1
	else {
		d = a - 2 * b; d1 = -2 * b, d2 = 2 * (a - b);
		while (y > y1) {
			if (d <= 0) { 
				x++; 
				y--; 
				d += d2;
			}
			else { 
				y--; 
				d += d1;
			}
			putpixel(x, y, color);
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