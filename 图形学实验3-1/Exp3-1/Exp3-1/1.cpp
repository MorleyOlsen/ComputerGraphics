//////////////////////////////////////////////////////
// 程序名称：实验3-1
// 功	能：实现预设图像的平移变换、比例变换等变换
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-4-5

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <math.h>
using namespace std;
#define pi 3.1415926535

int main() {
	POINT t1[] = { {200,200} , {200,20} , {220,80} };
	POINT t2[] = { {200,200} , {200,20} , {180,80} };
	int len = 3;
	float Tx = 50, Ty = 50;//平移
	float Sx = 0.5, Sy = 0.5;//比例
	float angle = 45 * pi / 180;//旋转，没做出来QwQ
	float C = 0.5, B = -0.5;//错切

	//initialize graph
	initgraph(640, 480);

	//勾画初始图案
	setfillcolor(RED);
	fillpolygon(t1, 3);
	polygon(t2, 3);

	//record the times of changing
	int times = 0;

	ExMessage m;
	//全是单步变换。
	while (1) {
		m = getmessage(EX_MOUSE | EX_KEY);
		float cur1x[3], cur1y[3], cur2x[3], cur2y[3];
		//平移
		if (m.message == WM_LBUTTONDOWN && times == 0) {
			for (int i = 0; i < len; i++) {
				t1[i].x += Tx;
				t1[i].y += Ty;
				t2[i].x += Tx;
				t2[i].y += Ty;
			}
			setfillcolor(RED);
			fillpolygon(t1, 3);
			polygon(t2, 3);
			times++;
		}
		//比例
		else if (m.message == WM_LBUTTONDOWN && times == 1) {
			for (int i = 0; i < len; i++) {
				t1[i].x += 50;
				t2[i].x += 50;
			}
			//以一顶点为缩放点
			for (int i = 1; i < len; i++) {
				t1[i].x = Sx * (t1[i].x - t1[0].x) + t1[0].x;
				t2[i].x = Sx * (t2[i].x - t2[0].x) + t2[0].x;
				t1[i].y = Sy * (t1[i].y - t1[0].y) + t1[0].y;
				t2[i].y = Sy * (t2[i].y - t2[0].y) + t2[0].y;
			}
			setfillcolor(RED);
			fillpolygon(t1, 3);
			polygon(t2, 3);
			times++;
		}
		//对称 about x axis
		else if (m.message == WM_LBUTTONDOWN && times == 2) {
			float mid = t1[0].y;
			for (int i = 0; i < len; i++) {
				t1[i].y = 2 * mid - t1[i].y;
				t2[i].y = 2 * mid - t2[i].y;
			}
			setfillcolor(RED);
			fillpolygon(t1, 3);
			polygon(t2, 3);
			times++;
		}
		//对称 about y axis
		else if (m.message == WM_LBUTTONDOWN && times == 3) {
			float midx = t1[2].x;
			for (int i = 0; i < len; i++) {
				t1[i].x = 2 * midx - t1[i].x;
				t2[i].x = 2 * midx - t2[i].x;
				//float cur1x[3], cur1y[3], cur2x[3], cur2y[3];
				cur1x[i] = t1[i].x;
				cur1y[i] = t1[i].y;
				cur2x[i] = t2[i].x;
				cur2y[i] = t2[i].y;
			}
			setfillcolor(RED);
			fillpolygon(t1, 3);
			polygon(t2, 3);
			times++;
		}
		//错切 沿x轴方向关于y错切（x = x + cy）
		else if (m.message == WM_LBUTTONDOWN && times == 4) {
			for (int i = 0; i < len; i++) {
				t1[i].x += C * t1[i].y;
				t2[i].x += C * t2[i].y;
			}
			setfillcolor(RED);
			fillpolygon(t1, 3);
			polygon(t2, 3);
			times++;
		}
		//错切 沿y轴方向关于x错切（y = y + bx）
		else if (m.message == WM_LBUTTONDOWN && times == 5) {
			for (int i = 0; i < len; i++) {
				/*
				//float cur1x[3], cur1y[3], cur2x[3], cur2y[3];
				cur1x[i] = t1[i].x;
				cur1y[i] = t1[i].y;
				cur2x[i] = t2[i].x;
				cur2y[i] = t2[i].y;
				*/

				//t1[i].y += B * t1[i].x;
				//t2[i].y += B * t2[i].x;
				t1[i].y = cur1y[i] + B * cur1x[i];
				t1[i].x = cur1x[i];
				t2[i].y = cur2y[i] + B * cur2x[i];
				t2[i].x = cur2x[i];
			}
			setfillcolor(RED);
			fillpolygon(t1, 3);
			polygon(t2, 3);
			times++;
		}
	}
	_getch();
	closegraph();
	return 0;
}