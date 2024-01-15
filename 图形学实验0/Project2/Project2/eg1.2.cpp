//////////////////////////////////////////////////////
// 程序名称：一笔绘制
// 功	能：一笔绘制三角形、b、b中一杠的图像
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-2-24

#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <math.h>

int main()
{
	initgraph(640, 480);	// 创建绘图窗口，大小为 640x480 像素

	//三角形
	moveto(100, 200);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	setlinecolor(RED);
	lineto(200, 400);
	setlinecolor(GREEN);
	lineto(100, 300);
	setlinecolor(BLUE);
	lineto(100, 200);

	//b
	moveto(300, 200);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	setlinecolor(YELLOW);
	lineto(300, 400);
	lineto(400, 400);
	lineto(400, 300);
	lineto(300, 300);

	//b加一个杠
	moveto(500, 200);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	setlinecolor(YELLOW);
	lineto(500, 400);
	lineto(600, 400);
	lineto(600, 300);
	lineto(500, 300);
	lineto(600, 400);

	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
	return 0;
}