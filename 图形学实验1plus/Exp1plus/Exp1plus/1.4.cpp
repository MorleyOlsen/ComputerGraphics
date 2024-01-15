//////////////////////////////////////////////////////
// �������ƣ���Բ�㷨
// ��	�ܣ����ķַ����뾶Ϊr��һ��������Բ�������ѡ��Բ��λ��
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-3-10

#include <graphics.h>
#include <conio.h>
#include <iostream>
using namespace std;

void Circle(int myx, int myy, int r, int color) {
	int x, y, delta, delta1, delta2, direction;

	//����һ���޵�Բ��
	x = 0;
	y = r;
	delta = 2 * (1 - r);
	while(y >= 0) {
		putpixel(myx + x, myy + y, color);
		if (delta < 0) {
			delta1 = 2 * (delta + y) - 1;
			if (delta1 <= 0) {
				direction = 1;
			}
			else {
				direction = 2;
			}
		}
		else if (delta > 0) {
			delta2 = 2 * (delta - x) - 1;
			if (delta2 <= 0) {
				direction = 2;
			}
			else {
				direction = 3;
			}
		}
		else {
			direction = 2;
		}
		switch (direction) {
		case 1:
			x++; 
			delta += 2 * x + 1; 
			break;
		case 2:
			x++; 
			y--; 
			delta += 2 * (x - y + 1); 
			break;
		case 3:
			y--; 
			delta += (-2 * y + 1); 
			break;
		}
	}

	//���ڶ����޵�Բ��
	x = 0;
	y = r;
	delta = 2 * (1 - r);
	while (y >= 0) {
		putpixel(myx + x, myy + y, color);
		if (delta < 0) {
			delta1 = 2 * (delta + y) - 1;
			if (delta1 <= 0) {
				direction = 1;
			}
			else {
				direction = 2;
			}
		}
		else if (delta > 0) {
			delta2 = 2 * (delta - x) - 1;
			if (delta2 <= 0) {
				direction = 2;
			}
			else {
				direction = 3;
			}
		}
		else {
			direction = 2;
		}
		switch (direction) {
		case 1:
			x--;
			delta += 2 * (-x) + 1;
			break;
		case 2:
			x--;
			y--;
			delta += 2 * (-x - y + 1);
			break;
		case 3:
			y--;
			delta += (-2 * y + 1);
			break;
		}
	}

	//���������޵�Բ��
	x = 0;
	y = -r;
	delta = 2 * (1 - r);
	while (y <= 0) {
		putpixel(myx + x, myy + y, color);
		if (delta < 0) {
			delta1 = 2 * (delta - y) - 1;
			if (delta1 <= 0) {
				direction = 1;
			}
			else {
				direction = 2;
			}
		}
		else if (delta > 0) {
			delta2 = 2 * (delta + x) - 1;
			if (delta2 <= 0) {
				direction = 2;
			}
			else {
				direction = 3;
			}
		}
		else {
			direction = 2;
		}
		switch (direction) {
		case 1:
			x--;
			delta += 2 * (-x) + 1;
			break;
		case 2:
			x--;
			y++;
			delta += 2 * (-x + y + 1);
			break;
		case 3:
			y++;
			delta += (2 * y + 1);
			break;
		}
	}

	//���������޵�Բ��
	x = 0;
	y = -r;
	delta = 2 * (1 - r);
	while (y <= 0) {
		putpixel(myx + x, myy + y, color);
		if (delta < 0) {
			delta1 = 2 * (delta - y) - 1;
			if (delta1 <= 0) {
				direction = 1;
			}
			else {
				direction = 2;
			}
		}
		else if (delta > 0) {
			delta2 = 2 * (delta - x) - 1;
			if (delta2 <= 0) {
				direction = 2;
			}
			else {
				direction = 3;
			}
		}
		else {
			direction = 2;
		}
		switch (direction) {
		case 1:
			x++;
			delta += 2 * x + 1;
			break;
		case 2:
			x++;
			y++;
			delta += 2 * (x + y + 1);
			break;
		case 3:
			y++;
			delta += (2 * y + 1);
			break;
		}
	}
}

int main() {
	//�û�����Բ����ز���
	int r,colornum;
	cout << "please input the radius of your circle" << endl;
	cin >> r;
	cout << endl;
	cout << "please choose a number to define the color of your circle" << endl;
	cout << "0:WHITE 1:RED 2:YELLOW" << endl;
	cin >> colornum;
	int colorarray[3] = { WHITE,RED,YELLOW };

	//ͼ�ν���
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
			Circle(m.x, m.y, r, colorarray[colornum]);
		case WM_KEYDOWN:
			if (m.vkcode == VK_ESCAPE)
				return 0;	// �� ESC ���˳�����
		}
	}
	closegraph();
	return 0;
}