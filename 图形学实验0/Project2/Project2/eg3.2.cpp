//////////////////////////////////////////////////////
// 程序名称：模仿鼠标操作
// 功	能：按下鼠标左键确定线段起点，抬起左键确定终点并画图
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-2-24

#include <graphics.h>

int main()
{
	// 初始化图形窗口
	initgraph(640, 480);

	ExMessage m;		// 定义消息变量

	while (true)
	{
		// 获取一条鼠标或按键消息
		m = getmessage(EX_MOUSE | EX_KEY);

		switch (m.message) {
		case WM_LBUTTONDOWN:
			moveto(m.x, m.y);//确定起点
		case WM_LBUTTONUP:
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);//设置style
			setlinecolor(RED);//设置color
			lineto(m.x, m.y);//确定重点并连线
		case WM_KEYDOWN:
			if (m.vkcode == VK_ESCAPE)
				return 0;	// 按 ESC 键退出程序
		}
	}

	// 关闭图形窗口
	closegraph();
	return 0;
}
