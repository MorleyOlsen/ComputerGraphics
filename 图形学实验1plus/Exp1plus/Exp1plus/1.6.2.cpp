//////////////////////////////////////////////////////
// �������ƣ��п���߶ε����Ӵ�����
// ��	�ܣ���ƾ��п�ȵĻ����㷨���������������Ӵ�����ȱ�ڵ�����
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-3-10

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <cmath>
using namespace std;

void mineputpixel(int x, int y, int color) {
	putpixel(x, y, color);
	putpixel(x-1, y, color);
	putpixel(x+1, y, color);
	putpixel(x-1, y+1, color);
	putpixel(x, y+1, color);
	putpixel(x+1, y+1, color);
	putpixel(x, y-1, color);
	putpixel(x+1, y-1, color);
	putpixel(x-1, y-1, color);
}

void bresenham(int x0, int y0, int x1, int y1, int color) {
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int erro = (dx > dy ? dx : -dy) / 2;

	while (mineputpixel(x0, y0, color), x0 != x1 || y0 != y1) {
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
	//�û�������ز���
	int x0, y0, x1, y1, x2, y2, x3, y3;
	cout << "Please input the first starting point:" << endl;
	cin >> x0 >> y0;
	cout << "Please input the first ending point:" << endl;
	cin >> x1 >> y1;
	cout << "Please input the second starting point:" << endl;
	cin >> x2 >> y2;
	cout << "Please input the second ending point:" << endl;
	cin >> x3 >> y3;
	int mycolor[2] = { RED, YELLOW };

	//ͼ�ν���
	initgraph(640, 480);
	bresenham(x0, y0, x1, y1, mycolor[0]);
	bresenham(x2, y2, x3, y3, mycolor[1]);

	_getch();
	closegraph();
	return 0;
}