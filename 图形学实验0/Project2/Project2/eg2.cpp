//////////////////////////////////////////////////////
// 程序名称：填充绘制
// 功	能：绘制如图所示三角形并填充
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-2-24

#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
int main()
{
	initgraph(640, 480);	// 创建绘图窗口，大小为 640x480 像素

	int point1[] = { 100,0,128,0,48,80,150,80,170,100,0,100,100,0 };
	int point2[] = { 0,100,20,120,220,120,128,28,113,43,170,100,0,100 };
	int point3[] = { 76,80,128,28,220,120,228,100,128,0,48,80,76,80 };

	/*
	moveto(100, 0);
	for (int i = 2; i < 14; i+=2) {
		lineto(point1[i], point1[i + 1]);
	}
	*/
	setfillcolor(RED);
	solidpolygon((POINT*)point1, 7);
	setfillcolor(YELLOW);
	solidpolygon((POINT*)point2, 7);
	setfillcolor(BLUE);
	solidpolygon((POINT*)point3, 7);

	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
	return 0;
}