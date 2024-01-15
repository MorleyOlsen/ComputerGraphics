//////////////////////////////////////////////////////
// 程序名称：多边形裁剪2
// 功	能：用Weiler-Atherton裁剪法实现多边形裁剪
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-3-31

#include <graphics.h>
#include <conio.h>
#include <iostream>
using namespace std;

//框的边界
float XL = 20, XR = 150, YB = 200, YT = 450;
POINT Edge[] = { {XR,YB},{XR,YT},{XL,YT},{XL,YB} };
//自定义多边形，顺时针排序点坐标
POINT Vertex[] = { {300,100},{100,400},{200,120},{50,300},{100,100} };
int inlen = 5, outlen = 0;
int keepx[100], keepy[100];

//编码数值
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

//编码函数
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

//CS裁剪
int CSLineClip(float x1, float y1, float x2, float y2) {
	//记录原始点
	float x10 = x1, y10 = y1, x20 = x2, y20 = y2;

	int code1, code2, code;
	float x, y;
	encode(x1, y1, &code1);
	encode(x2, y2, &code2);
	while (code1 != 0 || code2 != 0) {
		if ((code1 & code2) != 0) {
			return 0;
		}
		code = code1;
		if (code1 == 0) {
			code = code2;
		}
		//找交点，通过边界找坐标值
		if ((LEFT & code) != 0) {
			x = XL;
			y = y1 + (y2 - y1) * (XL - x1) / (x2 - x1);
		}
		else if ((RIGHT & code) != 0) {
			x = XR;
			y = y1 + (y2 - y1) * (XR - x1) / (x2 - x1);
		}
		else if ((BOTTOM & code) != 0) {
			y = YB;
			x = x1 + (x2 - x1) * (YB - y1) / (y2 - y1);
		}
		else if ((TOP & code) != 0) {
			y = YT;
			x = x1 + (x2 - x1) * (YT - y1) / (y2 - y1);
		}
		//更新范围内的交点
		if (code == code1) {
			x1 = x;
			y1 = y;
			encode(x, y, &code1);
		}
		else {
			x2 = x;
			y2 = y;
			encode(x, y, &code2);
		}
	}

	//最终端点是x1 y1, x2 y2
	//由于本题的特殊性，一定有一个是原始点，那先在一开始记录下
	//把求得的交点push到keep数组中
	//记录原始点 float x10 = x1, y10 = y1, x20 = x2, y20 = y2;
	if (x10 == x1 && y10 == y1) {
		//1点和原始点一样，那2点是交点，存入2点
		keepx[outlen] = x2;
		keepy[outlen] = y2;
		outlen++;//???换个名字就可以全局了
	}
	else if (x20 == x2 && y20 == y2) {
		//2点和原始点一样，那1点是交点，存入1点
		keepx[outlen] = x1;
		keepy[outlen] = y1;
		outlen++;
	}

	//画线
	setlinecolor(YELLOW);
	line(x1, y1, x2, y2);
	return 0;
}

int main() {
	initgraph(640, 480);

	//绘制自定的point多边形
	setcolor(WHITE);
	polygon(Vertex, inlen);
	setcolor(RED);
	polygon(Edge, 4);

	//寻找第一个从外部->内部的边，求交点
	int startnum = -1, endnum = -1;
	for (int i = 0; i < inlen; i++) {
		int code1 = -1, code2 = -1;
		//非末尾点判断
		if (i < inlen - 1) {
			encode(Vertex[i].x, Vertex[i].y, &code1);
			encode(Vertex[i + 1].x, Vertex[i + 1].y, &code2);
			if (code1 != 0 && code2 == 0) {
				//external to internal
				startnum = i;
				endnum = i + 1;
				break;
			}
		}
		//末尾点判断
		else {
			encode(Vertex[inlen - 1].x, Vertex[inlen - 1].y, &code1);
			encode(Vertex[0].x, Vertex[0].y, &code2);
			if (code1 != 0 && code2 == 0) {
				//external to internal
				startnum = i;
				endnum = i + 1;
				break;
			}
		}
	}
	//看看框和多边形是否有交集
	if (startnum == -1) {
		//没找到交点
		return 0;
	}
	/*else {
		cout << startnum << " " << endnum; //输出判断
	}*/

	//设置全局count不行，给到主函数然后传参进去吧
	//int count = 0;

	//CSCLIP救我老命啊，直接求内外交点然后clip掉
	CSLineClip(Vertex[startnum].x, Vertex[startnum].y, Vertex[endnum].x, Vertex[endnum].y);

	int curnum = endnum;
	int times = 1;//判断是否循环结束
	while (1) {
		int code1 = -1, code2 = -1;
		int flag = -1;
		//给起始点编码，看看是否在框内
		if (curnum < inlen - 1) {
			encode(Vertex[curnum].x, Vertex[curnum].y, &code1);
			encode(Vertex[curnum + 1].x, Vertex[curnum + 1].y, &code2);
			flag = 1;
		}
		else {
			encode(Vertex[inlen - 1].x, Vertex[inlen - 1].y, &code1);
			encode(Vertex[0].x, Vertex[0].y, &code2);
			flag = 0;
		}

		//两个点都在框内
		if (code1 == 0 && code2 == 0) {
			setlinecolor(YELLOW);
			if (flag == 1) {
				line(Vertex[curnum].x, Vertex[curnum].y, Vertex[curnum + 1].x, Vertex[curnum + 1].y);
			}
			else if (flag == 0) {
				line(Vertex[inlen - 1].x, Vertex[inlen - 1].y, Vertex[0].x, Vertex[0].y);
			}
		}
		//起点内，终点外
		else if (code1 == 0 && code2 != 0) {
			if (flag == 1) {
				CSLineClip(Vertex[curnum].x, Vertex[curnum].y, Vertex[curnum + 1].x, Vertex[curnum + 1].y);
			}
			else if (flag == 0) {
				CSLineClip(Vertex[inlen - 1].x, Vertex[inlen - 1].y, Vertex[0].x, Vertex[0].y);
			}
		}
		//起点外，终点内
		else if (code1 != 0 && code2 == 0) {
			if (flag == 1) {
				CSLineClip(Vertex[curnum].x, Vertex[curnum].y, Vertex[curnum + 1].x, Vertex[curnum + 1].y);
			}
			else if (flag == 0) {
				CSLineClip(Vertex[inlen - 1].x, Vertex[inlen - 1].y, Vertex[0].x, Vertex[0].y);
			}
		}
		//起点外，终点外
		else {
			//不画线
		}

		//记录入框交点和出框交点，并连结


		//当前线段判断完并连线完，给下一轮循环更新curnum
		if (curnum == inlen - 1) {
			curnum = 0;
			times++;
		}
		else {
			curnum++;
			times++;
		}

		//判断循环退出
		if (times == inlen) {
			break;
		}
	}

	for (int i = 0; i < outlen; i += 2) {
		line(keepx[i], keepy[i], keepx[i + 1], keepy[i + 1]);
	}

	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
	//cout << outlen;
	/*
	//交点判断
	for (int i = 0; i < outlen; i++) {
		cout << keepx[i] << " " << keepy[i] << endl;
	}
	*/
	return 0;
}