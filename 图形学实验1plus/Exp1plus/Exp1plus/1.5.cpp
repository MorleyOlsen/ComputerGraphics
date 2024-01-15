//////////////////////////////////////////////////////
// �������ƣ�����Բ�㷨
// ��	�ܣ���һ���볤��Ϊa�Ͱ����Ϊb��������Բ�������ѡ��Բ��λ��
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-3-10

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <cmath>
using namespace std;

void Oval(int myx, int myy, int a, int b, int color) {
	double xp, yp, d;
	int x, y;

	//��һ����
	xp = (double)a * a / sqrt(a * a + b * b);
	yp = (double)b * b / sqrt(a * a + b * b);
	//(0,b)=>p
	x = 0; 
	y = b;
	d = b * b + (-b + 0.25) * a * a;
	while (x <= xp) {
		putpixel(x + myx, y + myy, color);
		if (d <= 0) {
			d = d + (2 * x + 3) * b * b;
			x++;
		}
		else {
			d = d + (x * 2 + 3) * b * b + (-2 * y + 2) * a * a;
			x++;
			y--;
		}
	}
	//p->(a,0)
	x = a;
	y = 0;
	d = (-a + 0.25) * b * b + a * a;
	while (y < yp) {
		putpixel(myx + x, myy + y, color);
		if (d <= 0) {
			d += (2 * y + 3) * a * a;
			y++;
		}
		else {
			d += (2 * y + 3) * a * a + (-2 * x + 2) * b * b;
			x--;
			y++;
		}
	}

	//�ڶ�����
	xp = (double)-a * a / sqrt(a * a + b * b);
	yp = (double)b * b / sqrt(a * a + b * b);
	//(0,b)=>p
	x = 0;
	y = b;
	d = b * b + (-b + 0.25) * a * a;
	while (x >= xp) {
		putpixel(x + myx, y + myy, color);
		if (d <= 0) {
			d = d + (-2 * x + 3) * b * b;
			x--;
		}
		else {
			d = d + (-x * 2 + 3) * b * b + (-2 * y + 2) * a * a;
			x--;
			y--;
		}
	}
	//p->(a,0)
	x = -a;
	y = 0;
	d = (-a + 0.25) * b * b + a * a;
	while (y < yp) {
		putpixel(myx + x, myy + y, color);
		if (d <= 0) {
			d += (2 * y + 3) * a * a;
			y++;
		}
		else {
			d += (2 * y + 3) * a * a + (2 * x + 2) * b * b;
			x++;
			y++;
		}
	}

	//��������
	xp = (double)-a * a / sqrt(a * a + b * b);
	yp = (double)-b * b / sqrt(a * a + b * b);
	//(0,-b)=>p
	x = 0;
	y = -b;
	d = b * b + (-b + 0.25) * a * a;
	while (x >= xp) {
		putpixel(x + myx, y + myy, color);
		if (d <= 0) {
			d = d + (-2 * x + 3) * b * b;
			x--;
		}
		else {
			d = d + (-x * 2 + 3) * b * b + (2 * y + 2) * a * a;
			x--;
			y++;
		}
	}
	//p->(-a,0)
	x = -a;
	y = 0;
	d = (-a + 0.25) * b * b + a * a;
	while (y >= yp) {
		putpixel(myx + x, myy + y, color);
		if (d <= 0) {
			d += (-2 * y + 3) * a * a;
			y--;
		}
		else {
			d += (-2 * y + 3) * a * a + (2 * x + 2) * b * b;
			x++;
			y--;
		}
	}

	//��������
	xp = (double)a * a / sqrt(a * a + b * b);
	yp = (double)-b * b / sqrt(a * a + b * b);
	//(0,-b)=>p
	x = 0;
	y = -b;
	d = b * b + (-b + 0.25) * a * a;
	while (x <= xp) {
		putpixel(x + myx, y + myy, color);
		if (d <= 0) {
			d = d + (2 * x + 3) * b * b;
			x++;
		}
		else {
			d = d + (x * 2 + 3) * b * b + (2 * y + 2) * a * a;
			x++;
			y++;
		}
	}
	//p->(a,0)
	x = a;
	y = 0;
	d = (-a + 0.25) * b * b + a * a;
	while (y >= yp) {
		putpixel(myx + x, myy + y, color);
		if (d <= 0) {
			d += (-2 * y + 3) * a * a;
			y--;
		}
		else {
			d += (-2 * y + 3) * a * a + (-2 * x + 2) * b * b;
			x--;
			y--;
		}
	}
}

int main() {
	//�û�������Բ����ز���
	int a, b, colornum;
	cout << "please input the long and short parameters of your oval" << endl;
	cin >> a >> b;
	cout << endl;
	cout << "please choose a number to define the color of your oval" << endl;
	cout << "0:WHITE 1:RED 2:YELLOW" << endl;
	cin >> colornum;
	int colorarray[3] = { WHITE,RED,YELLOW };

	//ͼ�ν���
	initgraph(640, 480);
	ExMessage m;
	while (true) {
		m = getmessage(EX_MOUSE | EX_KEY);
		switch (m.message) {
		case WM_LBUTTONDOWN:
			setfillcolor(GREEN);
			fillrectangle(m.x - 3, m.y - 3, m.x + 3, m.y + 3);
			Oval(m.x, m.y, a, b, colorarray[colornum]);
		case WM_KEYDOWN:
			if (m.vkcode == VK_ESCAPE)
				return 0;	// �� ESC ���˳�����
		}
	}
	closegraph();
	return 0;
}