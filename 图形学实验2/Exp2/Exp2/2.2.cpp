//////////////////////////////////////////////////////
// �������ƣ���ֵ�ü�
// ��	�ܣ�����ֵ�ָ��㷨ʵ��ֱ�߶βü�
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-3-26
// Special Thanks To Gong WH

#include <graphics.h>
#include <conio.h>
#include <iostream>
using namespace std;

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
int XL, XR, YB, YT;

//�������
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

void MidClip(float x1, float y1, float x2, float y2) {
	int code1, code2;
	encode(x1, y1, &code1);
	encode(x2, y2, &code2);
	
	//�޷���������
	if (abs(x1 - x2) + abs(y1 - y2) <= 2) {
		return;
	}
	
	//�߶���ȫ���ɼ�
	if ((code1 & code2) != 0) {
		return;
	}

	//�߶���ȫ�ɼ�
	if ((code1 | code2) == 0) {
		setlinecolor(WHITE);
		line(x1, y1, x2, y2);
		return;
	}

	//�߶β��ֿɼ�=>�ݹ�ɡ���
	int midx = (x1 + x2) / 2, midy = (y1 + y2) / 2;
	
	MidClip(midx, midy, x2, y2);
	MidClip(x1, y1, midx, midy);


	/*
	//����Ż���������
	int midcode;
	encode(midx, midy, &midcode);
	//�е�ɼ�����������
	if (midcode == 0) {
		MidClip(midx, midy, x2, y2);
		MidClip(x1, y1, midx, midy);
	}
	//�е㲻�ɼ����ж��е���ĸ�����ͬһ����
	else {
		int cnt1[4] = { 0 }, cnt2[4] = { 0 }, cntmid[4] = { 0 };
		//handle midcode
		do {
			if (midcode >= 8) {
				cntmid[0] = 1;
				midcode -= 8;
			}
			else if (midcode >= 4) {
				cntmid[1] = 1;
				midcode -= 4;
			}
			else if (midcode >= 2) {
				cntmid[2] = 1;
				midcode -= 2;
			}
			else if (midcode >= 1) {
				cntmid[3] = 1;
				midcode -= 1;
			}
			else {
				continue;
			}
		} while (midcode != 0);
		//handle code1
		do {
			if (code1 >= 8) {
				cnt1[0] = 1;
				code1 -= 8;
			}
			else if (code1 >= 4) {
				cnt1[1] = 1;
				code1 -= 4;
			}
			else if (code1 >= 2) {
				cnt1[2] = 1;
				code1 -= 2;
			}
			else if (code1 >= 1) {
				cnt1[3] = 1;
				code1 -= 1;
			}
			else {
				continue;
			}
		} while (code1 != 0);
		//handle code2
		do {
			if (code2 >= 8) {
				cnt2[0] = 1;
				code2 -= 8;
			}
			else if (code2 >= 4) {
				cnt2[1] = 1;
				code2 -= 4;
			}
			else if (code2 >= 2) {
				cnt2[2] = 1;
				code2 -= 2;
			}
			else if (code2 >= 1) {
				cnt2[3] = 1;
				code2 -= 1;
			}
			else {
				continue;
			}
		} while (code2 != 0);
		int count1 = 0, count2 = 0;
		for (int i = 0; i < 4; i++) {
			if (cnt1[i] == cntmid[i]) {
				count1++;
			}
			if (cnt2[i] == cntmid[i]) {
				count2++;
			}
		}
		if (count1 > count2) {
			//point 1 area is closer to midpoint area
			MidClip(x1, y1, midx, midy);
		}
		else {
		    //point 2 area is closer to midpoint area
			MidClip(midx, midy, x2, y2);
		}
	}
	*/
}

int main() {
	//�û�����a��b����
	int xa, ya, xb, yb;
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
			MidClip(xa, ya, xb, yb);

		case WM_KEYDOWN:
			if (m.vkcode == VK_ESCAPE)
				return 0;	// �� ESC ���˳�����
		}
	}
	closegraph();
	return 0;
}