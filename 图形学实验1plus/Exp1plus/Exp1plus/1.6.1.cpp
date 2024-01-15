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
	//�û�������ز���
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
	//cin >> width;//�������
	int mycolor[2] = { RED, YELLOW };

	/*
	double flag1 = (double)(y1 - y0) / (x1 - x0);
	double flag2 = (double)(y3 - y2) / (x3 - x2);
	//flag1>1 or flag1<-1 б�ʴ���1 ���ú��򲹵�
	//flag1<1 and flag1>-1 б��С��1 �������򲹵�
	//flag2ͬ��ɵ�
	*/

	//ͼ�ν���
	initgraph(640, 480);

	//���ԼӴ�
	bresenham(x0, y0, x1, y1, mycolor[0]);
	//���ȷ��Ϊ10����
	for (int i = 0; i < 5; i++) {
		bresenham(x0 + i, y0, x1 + i, y1, mycolor[0]);
		bresenham(x0 - i, y0, x1 - i, y1, mycolor[0]);
	}
	for (int i = 0; i < 5; i++) {
		bresenham(x2 + i, y2, x3 + i, y3, mycolor[1]);
		bresenham(x2 - i, y2, x3 - i, y3, mycolor[1]);
	}

	//����ȱ��


	_getch();
	closegraph();
	return 0;
}