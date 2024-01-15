//////////////////////////////////////////////////////
// 程序名称：多边形裁剪1-2
// 功	能：用逐边裁剪法实现多边形裁剪（有退化）
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-3-31

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

//框的边界
float XL = 5, XR = 140, YB = 74, YT = 149;
POINT Edge[] = { {XR,YB},{XR,YT},{XL,YT},{XL,YB} };
//自定义多边形
POINT Vertex[] = { {110,84},{160,94},{90,169},{90,94},{70,90},{50,230}, {165,230},{175,89},{163,54} };
int inlen = 9;
#define max 100

//判断顶点和裁剪边的内外关系
bool Inside(POINT test, POINT p0, POINT p1) {
	if (p1.x > p0.x) {
		//裁剪边是窗口的下边
		if (test.y >= p0.y) {
			return 1;
		}
	}
	else if (p1.x < p0.x) {
		//裁剪边是窗口的上边
		if (test.y <= p0.y) {
			return 1;
		}
	}
	else if (p1.y > p0.y) {
		//裁剪边是窗口的右边
		if (test.x <= p0.x) {
			return 1;
		}
	}
	else if (p1.y < p0.y) {
		//裁剪边是窗口的左边
		if (test.x >= p0.x) {
			return 1;
		}
	}
	return 0;
}

//求多边形的一条边和裁剪边的交点
void Cross(POINT s, POINT p, POINT p0, POINT p1, POINT& i) {
	if (p0.y == p1.y) {
		//水平裁剪边
		i.y = p0.y;
		i.x = s.x + (p0.y - s.y) * (p.x - s.x) / (p.y - s.y);
	}
	else {
		//竖直裁剪边
		i.x = p0.x;
		i.y = s.y + (p0.x - s.x) * (p.y - s.y) / (p.x - s.x);
	}
}

//将新的多边形顶点加入原有顶点组
void Insert(POINT newpoint, int& mylen, POINT p[]) {
	p[mylen].x = newpoint.x;
	p[mylen].y = newpoint.y;
	mylen++;
	//顶点数+=1
}

//裁剪算法
void SHClip(int mylen, POINT in[], int& outlen, POINT out[], POINT p0, POINT p1) {
	POINT s, p, i;
	outlen = 0;
	s = in[mylen - 1];
	for (int j = 0; j < mylen; j++) {
		p = in[j];
		if (Inside(p, p0, p1)) {
			if (Inside(s, p0, p1)) {
				Insert(p, outlen, out);
			}
			else {
				Cross(s, p, p0, p1, i);
				Insert(i, outlen, out);
				Insert(p, outlen, out);
			}
		}
		else if (Inside(s, p0, p1)) {
			Cross(s, p, p0, p1, i);
			Insert(i, outlen, out);
		}
		s = p;
	}
}

//VS不让用快排啊=。=
int cmp(void* a, void* b) {
	return *(int*)a - *(int*)b;
}

int main() {
	//接收框的信息
	initgraph(640, 480);

	//绘制自定的point多边形
	setcolor(WHITE);
	polygon(Vertex, 9);

	//绘制框
	setlinecolor(RED);
	line(XL, YT, XR, YT);
	line(XL, YB, XR, YB);
	line(XL, YT, XL, YB);
	line(XR, YT, XR, YB);

	ExMessage m;
	POINT outp1[max], outp2[max], outp3[max], outp4[max];
	int len1, len2, len3, len4;
	int times = 0;

	while (1) {
		m = getmessage(EX_MOUSE | EX_KEY);
		//用户点击左键后生成裁剪图形
		if (m.message == WM_LBUTTONDOWN) {
			//裁剪过程
			//POINT Edge[] = { {XR,YB},{XR,YT},{XL,YT},{XL,YB} };
			//右边窗口裁剪边
			SHClip(inlen, Vertex, len1, outp1, Edge[0], Edge[1]);
			//上边窗口裁剪边
			SHClip(len1, outp1, len2, outp2, Edge[1], Edge[2]);
			//左边窗口裁剪边
			SHClip(len2, outp2, len3, outp3, Edge[2], Edge[3]);
			//下边窗口裁剪边
			SHClip(len3, outp3, len4, outp4, Edge[3], Edge[0]);

			//连线过程
			//setcolor(YELLOW);
			//polygon(outp4, len4);
			//原来的位置进行黄色标注裁剪

			/*closegraph();			// 关闭绘图窗口
			for (int t = 0; t < len4; t++) {
				cout << outp4[t].x <<" " << outp4[t].y << endl;

			}*/

			//退化边，根据outp4修改吧
			for (int i = 0; i < len4 - 1; i++) {
				int flag = 1;
				if (outp4[i].x == outp4[i + 1].x) {
					if (outp4[i].x == int(XL) || outp4[i].x == int(XR)) {
						flag = 0;
					}
				}
				if (outp4[i].y == outp4[i + 1].y) {
					if (outp4[i].y == int(YB) || outp4[i].y == int(YT)) {
						flag = 0;
					}
				}
				if (flag == 1) {
					setcolor(YELLOW);
					//+200像素，可能是为了，方便展示orz
					line(outp4[i].x + 200, outp4[i].y, outp4[i + 1].x + 200, outp4[i + 1].y);
				}
			}
			
			//float XL = 5, XR = 140, YB = 74, YT = 149;
			//{XR,YB},{XR,YT},{XL,YT},{XL,YB}
			//{ {110,84},{160,94},{90,169},{90,94},{70,90},{50,230}, {165,230},{175,89},{163,54} };
			
			//将坐标值按从小到大排序，奇数线段依次连接。
			int xl[10], xr[10], yb[10], yt[10];//记录和框重合的点
			int cntl = 0, cntr = 0, cntb = 0, cntt = 0;
			for (int t = 0; t < len4; t++) {
				if (outp4[t].x == int(XL)) {
					//有了一个x坐标了我还用啥二维数组存坐标啊，笑
					//[XL,y]
					xl[cntl++] = outp4[t].y;
				}
				if (outp4[t].x == int(XR)) {
					//[XR,y]
					xr[cntr++] = outp4[t].y;
				}
				if (outp4[t].y == int(YB)) {
					//[x,YB]
					yb[cntb++] = outp4[t].x;
				}
				if (outp4[t].y == int(YT)) {
					//[x,YB]
					yt[cntt++] = outp4[t].x;
				}
			}

			/*void selectSort(int& a, int alen) {
				for (int i = 0; i < alen - 1; i++) {
					int min = i;
					for (int j = i + 1; j < alen; j++) {
						if (a[j] < a[min]) {
							min = j;
						}
					}
					//swap elements
					int temp = a[min];
					a[min] = a[i];
					a[i] = temp;
				}
			}*/

			//为什么调用sort函数呢，突然的bug猝不及防。还是传统方法改好了。

			//排序x,y坐标
			//画left边
			if (cntl != 0) {
				for (int i = 0; i < cntl - 1; i++) {
					int min = i;
					for (int j = i + 1; j < cntl; j++) {
						if (xl[j] < xl[min]) {
							min = j;
						}
					}
					int t = xl[min];
					xl[min] = xl[i];
					xl[i] = t;
				}
				for (int i = 0; i < cntl; i += 2) {
					setcolor(YELLOW);
					line(int(XL) + 200, xr[i], int(XL) + 200, xr[i + 1]);
				}
			}
			//画right边
			if (cntr != 0) {
				for (int i = 0; i < cntr - 1; i++) {
					int min = i;
					for (int j = i + 1; j < cntr; j++) {
						if (xr[j] < xr[min]) {
							min = j;
						}
					}
					int t = xr[min];
					xr[min] = xr[i];
					xr[i] = t;
				}
				for (int i = 0; i < cntr; i += 2) {
					setcolor(YELLOW);
					line(int(XR) + 200, xr[i], int(XR) + 200, xr[i + 1]);
				}
			}
			//画bottom边
			if (cntb != 0) {
				for (int i = 0; i < cntb - 1; i++) {
					int min = i;
					for (int j = i + 1; j < cntb; j++) {
						if (yb[j] < yb[min]) {
							min = j;
						}
					}
					int t = yb[min];
					yb[min] = yb[i];
					yb[i] = t;
				}
				for (int i = 0; i < cntb; i += 2) {
					setcolor(YELLOW);
					line(yb[i] + 200, int(YB), yb[i + 1] + 200, int(YB));
				}
			}
			//画top边
			if (cntt != 0) {
				for (int i = 0; i < cntt - 1; i++) {
					int min = i;
					for (int j = i + 1; j < cntt; j++) {
						if (yt[j] < yt[min]) {
							min = j;
						}
					}
					int t = yt[min];
					yt[min] = yt[i];
					yt[i] = t;
				}
				for (int i = 0; i < cntt; i += 2) {
					setcolor(YELLOW);
					line(yt[i] + 200, int(YT), yt[i + 1] + 200, int(YT));
				}
			}
		}
	}

	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
	return 0;
}