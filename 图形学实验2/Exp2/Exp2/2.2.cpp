//////////////////////////////////////////////////////
// 程序名称：中值裁剪
// 功	能：用中值分割算法实现直线段裁剪
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-3-26
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

//区域编码
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
	
	//无法继续二分
	if (abs(x1 - x2) + abs(y1 - y2) <= 2) {
		return;
	}
	
	//线段完全不可见
	if ((code1 & code2) != 0) {
		return;
	}

	//线段完全可见
	if ((code1 | code2) == 0) {
		setlinecolor(WHITE);
		line(x1, y1, x2, y2);
		return;
	}

	//线段部分可见=>递归吧。。
	int midx = (x1 + x2) / 2, midy = (y1 + y2) / 2;
	
	MidClip(midx, midy, x2, y2);
	MidClip(x1, y1, midx, midy);


	/*
	//这个优化，不大行
	int midcode;
	encode(midx, midy, &midcode);
	//中点可见，继续二分
	if (midcode == 0) {
		MidClip(midx, midy, x2, y2);
		MidClip(x1, y1, midx, midy);
	}
	//中点不可见，判断中点和哪个点在同一区域
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
	//用户定义a、b坐标
	int xa, ya, xb, yb;
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
			MidClip(xa, ya, xb, yb);

		case WM_KEYDOWN:
			if (m.vkcode == VK_ESCAPE)
				return 0;	// 按 ESC 键退出程序
		}
	}
	closegraph();
	return 0;
}