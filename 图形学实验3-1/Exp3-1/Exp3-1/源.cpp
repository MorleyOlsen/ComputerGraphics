//实验名称：五种二维图形的几何变换（平移、比例、旋转、对称、错切）
//功       能：对于系统给定的基本图形，用户输入几何变换类型，程序根据用户给定的参数绘制二维图形的几何变换，用户按任意键可以查看动态过程
//编译环境：Visual Studio 2022，EasyX_20220116
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<cmath>
using namespace std;

const double pi = 3.1415926;//用符号常量的方式定义圆周率，比用宏定义define更加安全

//五种基本变换均不会改变基本图形自身的点坐标，因此可以使得原来点的坐标被重复使用

//平移变换函数，函数的主要参数为横纵坐标的平移距离，在绘制时用红色图形表示平移变换
void Translation(const int* x, const int* y, const unsigned& n, const int& dx, const int& dy)
{
	//首先绘制一次平移变换前的图形，以便展示区别
	initgraph(1000, 800);
	setfillcolor(RED);
	POINT* p = new POINT[n];
	for (unsigned i = 0; i < n; i++)
	{
		p[i] = { x[i],y[i] };
	}
	fillpolygon(p, n);
	_getch();
	//展示平移图形，与原图形在同一张图中
	for (unsigned i = 0; i < n; i++)
	{
		p[i].x += dx;
		p[i].y += dy;
	}
	fillpolygon(p, n);
	_getch();
	return;
}

//比例变换函数，函数的主要参数为横轴和纵轴的比例变换系数，在绘制时用黄色图形表示比例变换
void ScaleChange(const int* x, const int* y, const unsigned& n, const double& sx, const double& sy)
{
	//考虑到实际过程中参考点不一定是原点，因此让用户输入是否将坐标原点作为参考点
	int DefaultPoint;
	cout << "请确定是否采用默认参考点(0,0)（1表示使用，其他输入表示不使用)：";
	cin >> DefaultPoint;
	POINT* p = new POINT[n];
	//直接使用坐标原点作为参考点的情况
	if (DefaultPoint == 1)
	{
		initgraph(1000, 800);
		setfillcolor(YELLOW);
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = x[i];
			p[i].y = y[i];
		}
		fillpolygon(p, n);
		_getch();
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x *= sx;
			p[i].y *= sy;
		}
		fillpolygon(p, n);
		_getch();
		return;
	}
	//用户自定义参考点的情况
	else
	{
		int x0, y0;
		cout << "请输入参考点的横纵坐标:";
		cin >> x0 >> y0;
		initgraph(1000, 800);
		setfillcolor(YELLOW);
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = x[i];
			p[i].y = y[i];
		}
		fillpolygon(p, n);
		_getch();
		closegraph();
		initgraph(1000, 800);
		setfillcolor(YELLOW);
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = sx * p[i].x - (sx - 1) * x0;
			p[i].y = sy * p[i].y - (sy - 1) * y0;
		}
		fillpolygon(p, n);
		_getch();
		return;
	}
}

//旋转变换函数，函数的主要参数为旋转角度，绘图时用蓝色表示旋转操作
void Rotation(const int* x, const int* y, const unsigned& n, const double& angle)
{
	//与比例变换类似，让用户自行选择是否以坐标原点为旋转中心
	int DefaultPoint;
	cout << "请选择是否采用默认参考点(0,0)(1表示使用，其他输入表示不使用）：";
	cin >> DefaultPoint;
	POINT* p = new POINT[n];
	double Angle = angle * pi / 180.0;
	//以坐标原点作为旋转中心的情况
	if (DefaultPoint == 1)
	{
		initgraph(1000, 800);
		setfillcolor(BLUE);
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = x[i];
			p[i].y = y[i];
		}
		fillpolygon(p, n);
		_getch();
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = int(double(x[i]) * cos(Angle) - double(y[i]) * sin(Angle) + 0.5);
			p[i].y = int(double(y[i]) * sin(Angle) + double(y[i]) * cos(Angle) + 0.5);
		}
		fillpolygon(p, n);
		_getch();
		return;
	}
	//以用户自定义的点作为旋转中心的情况
	else
	{
		int x0, y0;
		cout << "请输入参考点的横纵坐标:";
		cin >> x0 >> y0;
		initgraph(1000, 800);
		setfillcolor(BLUE);
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = x[i];
			p[i].y = y[i];
		}
		fillpolygon(p, n);
		_getch();

		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = int(double(x[i] - x0) * cos(Angle) - double(y[i] - y0) * sin(Angle) + x0 + 0.5);
			p[i].y = int(double(x[i] - x0) * sin(Angle) + double(y[i] - y0) * cos(Angle) + y0 + 0.5);
		}
		fillpolygon(p, n);
		_getch();
		return;
	}
}

//对称变换函数，函数的主要参数为对称轴的方程，用直线的一般式表示，用绿色图形来表示对称变换
void Symmetry(const int* x, const int* y, const unsigned& n, const double& A, const double& B, const double& C)
{
	initgraph(1000, 800);
	setfillcolor(GREEN);
	POINT* p = new POINT[n];
	for (unsigned i = 0; i < n; i++)
	{
		p[i].x = x[i];
		p[i].y = y[i];
	}
	fillpolygon(p, n);
	_getch();
	for (unsigned i = 0; i < n; i++)
	{
		int tempx, tempy;
		tempx = p[i].x - int(2 * A * (A * p[i].x + B * p[i].y + C) / (A * A + B * B) + 0.5);
		tempy = p[i].y - int(2 * B * (A * p[i].x + B * p[i].y + C) / (A * A + B * B) + 0.5);
		p[i].x = tempx;
		p[i].y = tempy;
	}
	fillpolygon(p, n);
	_getch();
	return;
}

//错切变换函数，函数的主要参数是横轴和纵轴的错切系数，用浅蓝色图形表示错切变换
void StaggeredCutting(const int* x, const int* y, const unsigned& n, const double& a, const double& b)
{
	initgraph(1000, 800);
	setfillcolor(LIGHTBLUE);
	POINT* p = new POINT[n];
	for (unsigned i = 0; i < n; i++)
	{
		p[i].x = x[i];
		p[i].y = y[i];
	}
	fillpolygon(p, n);
	_getch();
	for (unsigned i = 0; i < n; i++)
	{
		int tempx, tempy;
		tempx = p[i].x + a * p[i].y;
		tempy = p[i].y + b * p[i].x;
		p[i].x = tempx;
		p[i].y = tempy;
	}
	fillpolygon(p, n);
	_getch();
	return;
}

int main(void)
{
	//以一个等腰三角形作为基本图形，当然也可以使用其他基本图形或者让用户自定义一个基本图形，此处未作引申
	int x[3] = { 100,100,150 };
	int y[3] = { 100,300,200 };

	//根据用户的输入来判断进行的基本变换类型
	int cmd;
	cout << "请输入您想要进行的基本变换类型（1表示平移，2表示比例变换，3表示旋转，4表示对称，5表示错切）：";
	cin >> cmd;
	if (cmd == 1)
	{
		int dx, dy;
		cout << "您选择平移操作，请分别输入横纵方向的平移距离：";
		cin >> dx >> dy;
		cout << "参数确认成功，按任意键继续程序...(画图中按任意键继续，完成后按任意键返回)" << endl;
		_getch();
		Translation(x, y, 3, dx, dy);//传参后直接调用平移函数展示绘制效果
	}
	else if (cmd == 2)
	{
		double sx, sy;
		cout << "您选择比例变换操作，请输入横轴和纵轴的变换比例：";
		cin >> sx >> sy;
		ScaleChange(x, y, 3, sx, sy);//传参后直接调用比例变换函数展示绘制效果
	}
	else if (cmd == 3)
	{
		double angle;
		cout << "请输入逆时针旋转的角度大小（用角度表示）：";
		cin >> angle;
		Rotation(x, y, 3, angle);//直接调用旋转函数绘制变换效果
	}
	else if (cmd == 4)
	{
		double A, B, C;
		cout << "请输入对称轴的直线方程参数（形如Ax+By+C=0，分别输入A、B、C）：";
		cin >> A >> B >> C;
		cout << "参数确认成功，按任意键继续程序...(画图完成后按任意键返回)" << endl;
		_getch();
		Symmetry(x, y, 3, A, B, C);//调用对称函数展示对称变换的变换效果
	}
	else if (cmd == 5)
	{
		double a, b;
		cout << "请分别输入横轴错切系数和纵轴错切系数：";
		cin >> a >> b;
		cout << "参数确认成功，按任意键继续程序...（画图完成后按任意键返回）" << endl;
		StaggeredCutting(x, y, 3, a, b);//调用错切变换函数展示绘制效果
	}
	else//对于其他输入，则退出程序并输出相关的提示信息
	{
		cout << "没有找到对应的绘图命令哦~" << endl;
	}
	return 0;
}