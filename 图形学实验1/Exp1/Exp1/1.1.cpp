//////////////////////////////////////////////////////
// 程序名称：DDA
// 功	能：用DDA算法绘制任意斜率的曲线
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-3-3

#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <iostream>
using namespace std;

void DDA_Line(int x0, int y0, int x1, int y1, int color){
	int dx = x1 - x0, dy = y1 - y0, step, k;
	float x = x0, y = y0, xIncre, yIncre;

	//斜率绝对值大于1的时候，以 y 的变化为基准
	if (abs(dx) > abs(dy)) {
        step = abs(dx);
	}
	else {
		step = abs(dy);
	}

	//x和y的增量计算
	xIncre = (float)dx / (float)step;
	yIncre = (float)dy / (float)step;
	for (k = 0; k < step; k++) {
		putpixel(int(x + 0.5f), (int)(y + 0.5f), color);
		x += xIncre;
		y += yIncre;
	}
}

int main(){
	int x1, y1, x2, y2;
	cout << "please input the start point:" << endl;
	cin >> x1 >> y1;
	cout << "please input the end point:" << endl;
	cin >> x2 >> y2;
	
	initgraph(640, 480);
	DDA_Line(x1, y1, x2, y2, WHITE);

	_getch();
	closegraph();
	return 0;
}
