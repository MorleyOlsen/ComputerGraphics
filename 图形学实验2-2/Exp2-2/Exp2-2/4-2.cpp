//////////////////////////////////////////////////////
// �������ƣ�����βü�1-2
// ��	�ܣ�����߲ü���ʵ�ֶ���βü������˻���
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-3-31

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

//��ı߽�
float XL = 5, XR = 140, YB = 74, YT = 149;
POINT Edge[] = { {XR,YB},{XR,YT},{XL,YT},{XL,YB} };
//�Զ�������
POINT Vertex[] = { {110,84},{160,94},{90,169},{90,94},{70,90},{50,230}, {165,230},{175,89},{163,54} };
int inlen = 9;
#define max 100

//�ж϶���Ͳü��ߵ������ϵ
bool Inside(POINT test, POINT p0, POINT p1) {
	if (p1.x > p0.x) {
		//�ü����Ǵ��ڵ��±�
		if (test.y >= p0.y) {
			return 1;
		}
	}
	else if (p1.x < p0.x) {
		//�ü����Ǵ��ڵ��ϱ�
		if (test.y <= p0.y) {
			return 1;
		}
	}
	else if (p1.y > p0.y) {
		//�ü����Ǵ��ڵ��ұ�
		if (test.x <= p0.x) {
			return 1;
		}
	}
	else if (p1.y < p0.y) {
		//�ü����Ǵ��ڵ����
		if (test.x >= p0.x) {
			return 1;
		}
	}
	return 0;
}

//�����ε�һ���ߺͲü��ߵĽ���
void Cross(POINT s, POINT p, POINT p0, POINT p1, POINT& i) {
	if (p0.y == p1.y) {
		//ˮƽ�ü���
		i.y = p0.y;
		i.x = s.x + (p0.y - s.y) * (p.x - s.x) / (p.y - s.y);
	}
	else {
		//��ֱ�ü���
		i.x = p0.x;
		i.y = s.y + (p0.x - s.x) * (p.y - s.y) / (p.x - s.x);
	}
}

//���µĶ���ζ������ԭ�ж�����
void Insert(POINT newpoint, int& mylen, POINT p[]) {
	p[mylen].x = newpoint.x;
	p[mylen].y = newpoint.y;
	mylen++;
	//������+=1
}

//�ü��㷨
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

//VS�����ÿ��Ű�=��=
int cmp(void* a, void* b) {
	return *(int*)a - *(int*)b;
}

int main() {
	//���տ����Ϣ
	initgraph(640, 480);

	//�����Զ���point�����
	setcolor(WHITE);
	polygon(Vertex, 9);

	//���ƿ�
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
		//�û������������ɲü�ͼ��
		if (m.message == WM_LBUTTONDOWN) {
			//�ü�����
			//POINT Edge[] = { {XR,YB},{XR,YT},{XL,YT},{XL,YB} };
			//�ұߴ��ڲü���
			SHClip(inlen, Vertex, len1, outp1, Edge[0], Edge[1]);
			//�ϱߴ��ڲü���
			SHClip(len1, outp1, len2, outp2, Edge[1], Edge[2]);
			//��ߴ��ڲü���
			SHClip(len2, outp2, len3, outp3, Edge[2], Edge[3]);
			//�±ߴ��ڲü���
			SHClip(len3, outp3, len4, outp4, Edge[3], Edge[0]);

			//���߹���
			//setcolor(YELLOW);
			//polygon(outp4, len4);
			//ԭ����λ�ý��л�ɫ��ע�ü�

			/*closegraph();			// �رջ�ͼ����
			for (int t = 0; t < len4; t++) {
				cout << outp4[t].x <<" " << outp4[t].y << endl;

			}*/

			//�˻��ߣ�����outp4�޸İ�
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
					//+200���أ�������Ϊ�ˣ�����չʾorz
					line(outp4[i].x + 200, outp4[i].y, outp4[i + 1].x + 200, outp4[i + 1].y);
				}
			}
			
			//float XL = 5, XR = 140, YB = 74, YT = 149;
			//{XR,YB},{XR,YT},{XL,YT},{XL,YB}
			//{ {110,84},{160,94},{90,169},{90,94},{70,90},{50,230}, {165,230},{175,89},{163,54} };
			
			//������ֵ����С�������������߶��������ӡ�
			int xl[10], xr[10], yb[10], yt[10];//��¼�Ϳ��غϵĵ�
			int cntl = 0, cntr = 0, cntb = 0, cntt = 0;
			for (int t = 0; t < len4; t++) {
				if (outp4[t].x == int(XL)) {
					//����һ��x�������һ���ɶ��ά��������갡��Ц
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

			//Ϊʲô����sort�����أ�ͻȻ��bug⧲����������Ǵ�ͳ�����ĺ��ˡ�

			//����x,y����
			//��left��
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
			//��right��
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
			//��bottom��
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
			//��top��
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

	_getch();				// �����������
	closegraph();			// �رջ�ͼ����
	return 0;
}