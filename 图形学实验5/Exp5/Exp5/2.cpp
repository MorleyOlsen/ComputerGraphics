//////////////////////////////////////////////////////
// 程序名称：Bezier曲面
// 功	能：绘制Bezier曲面，双三次类型。
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-5-9

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <cmath>
using namespace std;
#define pi 3.1415926
#define MAX 20

//三维点类
class Point3D {
public:
	double x, y, z;
	Point3D(int x = 0, int y = 0, int z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	};
	void operator=(Point3D& a) {
		x = a.x;
		y = a.y;
		z = a.z;
	};
	Point3D operator*(double a) {
		return Point3D(a * x, a * y, a * z);
	};
	Point3D operator+(Point3D a) {
		return Point3D(x + a.x, y + a.y, z + a.z);
	};
	void operator+=(Point3D a) {
		x += a.x;
		y += a.y;
		z += a.z;
	};
};

//求阶乘
long int Factorial(int n) {
	int i, sum = 1;
	if (n == 0) {
		return 1;
	}
	for (i = 2; i <= n; i++) {
		sum *= i;
	}
	return sum;
}

//Bernstein函数
double Bernstein(int i, int n, double t) {
	return (double)Factorial(n) / Factorial(i) / Factorial(n - i) * pow(t, i) * pow(1 - t, n - i);
}

//Bezier曲面求解
void BezierCurve(Point3D p[][MAX], int n, int m, int nd, int md, double sita, double fai) {
	double hu = 1.0 / nd;
	double hv = 1.0 / md;
	double u = 0, v = 0;
	int i, j, k, l;
	sita = sita * pi / 180;
	fai = fai * pi / 180;
	int** pB = new int* [nd + 1];
	for (i = 0; i <= nd; i++) {
		pB[i] = new int[2 * md + 2];
	}
	Point3D ptemp(0, 0, 0);
	for (i = 0; i <= nd; i++, u += hu) {
		v = 0;
		for (j = 0; j <= 2 * md + 1; j += 2, v += hv) {
			ptemp.x = 0;
			ptemp.y = 0;
			ptemp.z = 0;
			for (k = 0; k <= n; k++) {
				for (l = 0; l <= m; l++) {
					ptemp += p[k][l] * Bernstein(k, n, u) * Bernstein(l, m, v);
				}
			}
			pB[i][j] = ptemp.x * cos(sita) - ptemp.y * sin(sita) + 500;
			pB[i][j + 1] = -ptemp.x * sin(sita) * sin(fai) - ptemp.y * cos(sita) * sin(fai) + ptemp.z * cos(fai) + 400;
		}
		drawpoly(md + 1, pB[i]);
	}
	for (i = 0; i < nd + 1; i++) {
		delete[]pB[i];
	}
	delete[]pB;
}

//画控制多边形
void drawControlPoly_3D(Point3D p[][MAX], int n, int m, double sita, double fai, int color) {
	int** p2d = new int* [n + 1];
	int i, j;
	setcolor(color);
	sita = sita * pi / 180;
	fai = fai * pi / 180;
	for (i = 0; i < n + 1; i++) {
		p2d[i] = new int[2 * m + 4];
	}
	char str[80];
	//3D->2D
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= m; j++) {
			p2d[i][2 * j] = p[i][j].x * cos(sita) - p[i][j].y * sin(sita) + 500;
			p2d[i][2 * j + 1] = -p[i][j].x * sin(sita) * sin(fai) - p[i][j].y * cos(sita) * sin(fai) + p[i][j].z * cos(fai) + 400;
		}
		p2d[i][2 * j] = p2d[i][0];
		p2d[i][2 * j + 1] = p2d[i][1];
		drawpoly(m + 2, p2d[i]);
	}
	for (j = 0; j <= 2 * m + 1; j += 2) {
		moveto(p2d[0][j], p2d[0][j + 1]);
		for (i = 1; i <= n; i++) {
			lineto(p2d[i][j], p2d[i][j + 1]);
		}
	}
	for (i = 0; i < n + 1; i++) {
		delete[]p2d[i];
	}
	delete[]p2d;
}

//双几次曲面
void BezierCurve_Shuang(Point3D p[][MAX], int pn, int pm, int nd, int md, double sita, double fai, int shuangjici) {
	int i, j, k, l;
	Point3D point[MAX][MAX];
	for (i = 0; i < pn - shuangjici; i += shuangjici) {
		for (j = 0; j < pm - shuangjici; j += shuangjici) {
			for (k = 0; k <= shuangjici; k++) {
				for (l = 0; l <= shuangjici; l++) {
					point[k][l] = p[i + k][j + l];
				}
			}
			BezierCurve(point, shuangjici, shuangjici, nd, md, sita, fai);
		}
	}
}

//主函数
int main() {
	int n;
	double fai, sita;
	//固定角度了。
	sita = 20;
	fai = 160;
	n = 3;

	//顶点集合
	Point3D p[][MAX] = {
		{Point3D(0,0,0),Point3D(150,150,150),Point3D(250,150,150),Point3D(400,0,0)},
		{Point3D(50,200,0),Point3D(150,250,150),Point3D(250,250,150),Point3D(450,200,0)},
		{Point3D(20,400,0),Point3D(150,350,150),Point3D(250,350,150),Point3D(420,400,0)},
		{Point3D(0,600,0),Point3D(150,550,150),Point3D(250,550,150),Point3D(400,600,0)}
	};

	/*
	cout << "please input sita and fai" << endl;
	cin >> sita >> fai;
	cout << "please input your n" << endl;
	cin >> n;
	*/

	//初始化界面
	initgraph(1000, 700);
	setcolor(RED);

	//Bezier曲面
	BezierCurve_Shuang(p, 4, 4, 100, 100, sita, fai, n);
	//画控制多边形
	drawControlPoly_3D(p, 3, 3, sita, fai, GREEN);

	_getch();
	closegraph();
	return 0;
}