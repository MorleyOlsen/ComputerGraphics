//////////////////////////////////////////////////////
// 程序名称：画圆算法
// 功	能：用四分法画半径为r的一个完整的圆，用鼠标选择圆心位置
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-3-10

#include <graphics.h>
#include <conio.h>
#include <iostream>
using namespace std;

void Circle(int myx, int myy, int r, int color) {
	int x, y, delta, delta1, delta2, direction;

	//画第一象限的圆弧
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

	//画第二象限的圆弧
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

	//画第三象限的圆弧
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

	//画第四象限的圆弧
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
	//用户定义圆的相关参数
	int r,colornum;
	cout << "please input the radius of your circle" << endl;
	cin >> r;
	cout << endl;
	cout << "please choose a number to define the color of your circle" << endl;
	cout << "0:WHITE 1:RED 2:YELLOW" << endl;
	cin >> colornum;
	int colorarray[3] = { WHITE,RED,YELLOW };

	//图形界面
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
				return 0;	// 按 ESC 键退出程序
		}
	}
	closegraph();
	return 0;
}