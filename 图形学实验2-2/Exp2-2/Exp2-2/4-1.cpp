//////////////////////////////////////////////////////
// �������ƣ�����βü�1-1
// ��	�ܣ�����߲ü���ʵ�ֶ���βü������˻���
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-3-31

#include <graphics.h>
#include <conio.h>
#include <iostream>
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
void Cross(POINT s, POINT p, POINT p0, POINT p1, POINT &i) {
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
void Insert(POINT newpoint, int &mylen, POINT p[]) {
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

int main() {
	//���տ����Ϣ
	float x0, y0, x1, y1;

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
			setcolor(YELLOW);
			polygon(outp4, len4);
			//ԭ����λ�ý��л�ɫ��ע�ü�
			
			times++;
		}
		//�û�����Ҽ������Ա߿հ״����ɲü�ͼ��
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

	_getch();				// �����������
	closegraph();			// �رջ�ͼ����
	return 0;
}