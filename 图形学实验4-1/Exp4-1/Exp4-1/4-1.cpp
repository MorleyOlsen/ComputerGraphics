//////////////////////////////////////////////////////
// �������ƣ�ʵ��4-1
// ��	�ܣ�ʵ��Ԥ��ͼ�������ͼ��ʾ
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-4-8

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <math.h>
using namespace std;

//�ͷָ���֮��ľ���
const int gap = 50;
//Ԥ����ά��ĵ�����
int X[33] = { 0,0,0,0,0,0,0,0,100,100,0,100,100,100,100,100,100,100,100,0,0,0,0,100,100,100,100,0,0,0,0,100,100 };
int Y[33] = { 0,0,250,250,200,150,0,0,0,0,0,0,150,200,250,250,0,0,150,150,0,150,200,200,150,200,250,250,200,250,250,250,250 };
int Z[33]= { 100,0,0,50,50,100,100,0,0,100,100,100,100,50,50,0,0,100,100,100,100,100,50,50,100,50,50,50,50,50,0,0,50 };
//��������
const int num = 33;

//����ͼʵ�ֺ���
void fun() {
	//����ͼ
	POINT* front = new POINT[num];
	for (int i = 0; i < num; i++) {
		front[i].x = X[i] + 500 + gap;
		front[i].y = 350 - Z[i] - gap;
	}
	//����ͼ
	POINT* side = new POINT[num];
	for (int i = 0; i < num; i++) {
		side[i].x = Y[i] + 250 - gap;
		side[i].y = 350 - Z[i] - gap;
	}
	//����ͼ
	POINT* up = new POINT[num];
	for (int i = 0; i < num; i++) {
		up[i].x = X[i] + 500 + gap;
		up[i].y = 600 - Y[i] + gap;
	}
	setcolor(YELLOW);
	for (int i = 0; i < num - 1; i++) {
		line(front[i].x, front[i].y, front[i + 1].x, front[i + 1].y);
		line(side[i].x, side[i].y, side[i + 1].x, side[i + 1].y);
		line(up[i].x, up[i].y, up[i + 1].x, up[i + 1].y);
	}
	free(front);
	free(side);
	free(up);
}

int main() {
	initgraph(1000, 700);
	line(0, 350, 1000, 350);
	line(500, 0, 500, 700);
	fun();
	_getch();
	closegraph();
	return 0;
}