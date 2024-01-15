//////////////////////////////////////////////////////
// 程序名称：多边形裁剪1-1
// 功	能：用逐边裁剪法实现多边形裁剪（无退化）
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-3-31

#include <graphics.h>
#include <conio.h>
#include <iostream>
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
void Cross(POINT s, POINT p, POINT p0, POINT p1, POINT &i) {
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
void Insert(POINT newpoint, int &mylen, POINT p[]) {
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

int main() {
	//接收框的信息
	float x0, y0, x1, y1;

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
			setcolor(YELLOW);
			polygon(outp4, len4);
			//原来的位置进行黄色标注裁剪
			
			times++;
		}
		//用户点击右键后在旁边空白处生成裁剪图形
		else if (m.message == WM_RBUTTONDOWN) {
			for (int i = 0; i < len4; i++) {
				outp4[i].x += 200;
			}
			setcolor(YELLOW);
			polygon(outp4, len4);
			times++;
		}
		if (times == 2) {
			break;
		}
	}

	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
	return 0;
}