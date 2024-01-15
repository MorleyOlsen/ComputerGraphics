//////////////////////////////////////////////////////
// �������ƣ�CS�ü�
// ��	�ܣ���Cohen-Sutherland�㷨ʵ��ֱ�߶βü�
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-3-17

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
		//�ҽ��㣬ͨ���߽�������ֵ
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
		//���·�Χ�ڵĽ���
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
	//�û�����a��b����
	float xa, ya, xb, yb;
	cout << "please input the coordinate of A point:" << endl;
	cin >> xa >> ya;
	cout << "please input the coordinate of B point:" << endl;
	cin >> xb >> yb;
	int x0, y0, x1, y1;
	//0->left bottom; 1->right top;

	//ͼ�ν���
	initgraph(640, 480);
	ExMessage m;
	//����AB�߶Σ���ɫ
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
			//�ж��û�������~���� / ����~���� / ����~���� / ����~����
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
			//���ղü���
			setlinecolor(RED);
			line(XL, YT, XR, YT);
			line(XL, YB, XR, YB);
			line(XL, YT, XL, YB);
			line(XR, YT, XR, YB);
			//�ü�����Ϊ��ɫ
			CSLineClip(xa, ya, xb, yb);
		case WM_KEYDOWN:
			if (m.vkcode == VK_ESCAPE)
				return 0;	// �� ESC ���˳�����
		}
	}
	closegraph();
	return 0;
}