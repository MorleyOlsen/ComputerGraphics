//////////////////////////////////////////////////////
// �������ƣ�����βü�2
// ��	�ܣ���Weiler-Atherton�ü���ʵ�ֶ���βü�
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-3-31

#include <graphics.h>
#include <conio.h>
#include <iostream>
using namespace std;

//��ı߽�
float XL = 20, XR = 150, YB = 200, YT = 450;
POINT Edge[] = { {XR,YB},{XR,YT},{XL,YT},{XL,YB} };
//�Զ������Σ�˳ʱ�����������
POINT Vertex[] = { {300,100},{100,400},{200,120},{50,300},{100,100} };
int inlen = 5, outlen = 0;
int keepx[100], keepy[100];

//������ֵ
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

//���뺯��
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

//CS�ü�
int CSLineClip(float x1, float y1, float x2, float y2) {
	//��¼ԭʼ��
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
		//�ҽ��㣬ͨ���߽�������ֵ
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
		//���·�Χ�ڵĽ���
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

	//���ն˵���x1 y1, x2 y2
	//���ڱ���������ԣ�һ����һ����ԭʼ�㣬������һ��ʼ��¼��
	//����õĽ���push��keep������
	//��¼ԭʼ�� float x10 = x1, y10 = y1, x20 = x2, y20 = y2;
	if (x10 == x1 && y10 == y1) {
		//1���ԭʼ��һ������2���ǽ��㣬����2��
		keepx[outlen] = x2;
		keepy[outlen] = y2;
		outlen++;//???�������־Ϳ���ȫ����
	}
	else if (x20 == x2 && y20 == y2) {
		//2���ԭʼ��һ������1���ǽ��㣬����1��
		keepx[outlen] = x1;
		keepy[outlen] = y1;
		outlen++;
	}

	//����
	setlinecolor(YELLOW);
	line(x1, y1, x2, y2);
	return 0;
}

int main() {
	initgraph(640, 480);

	//�����Զ���point�����
	setcolor(WHITE);
	polygon(Vertex, inlen);
	setcolor(RED);
	polygon(Edge, 4);

	//Ѱ�ҵ�һ�����ⲿ->�ڲ��ıߣ��󽻵�
	int startnum = -1, endnum = -1;
	for (int i = 0; i < inlen; i++) {
		int code1 = -1, code2 = -1;
		//��ĩβ���ж�
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
		//ĩβ���ж�
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
	//������Ͷ�����Ƿ��н���
	if (startnum == -1) {
		//û�ҵ�����
		return 0;
	}
	/*else {
		cout << startnum << " " << endnum; //����ж�
	}*/

	//����ȫ��count���У�����������Ȼ�󴫲ν�ȥ��
	//int count = 0;

	//CSCLIP������������ֱ�������⽻��Ȼ��clip��
	CSLineClip(Vertex[startnum].x, Vertex[startnum].y, Vertex[endnum].x, Vertex[endnum].y);

	int curnum = endnum;
	int times = 1;//�ж��Ƿ�ѭ������
	while (1) {
		int code1 = -1, code2 = -1;
		int flag = -1;
		//����ʼ����룬�����Ƿ��ڿ���
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

		//�����㶼�ڿ���
		if (code1 == 0 && code2 == 0) {
			setlinecolor(YELLOW);
			if (flag == 1) {
				line(Vertex[curnum].x, Vertex[curnum].y, Vertex[curnum + 1].x, Vertex[curnum + 1].y);
			}
			else if (flag == 0) {
				line(Vertex[inlen - 1].x, Vertex[inlen - 1].y, Vertex[0].x, Vertex[0].y);
			}
		}
		//����ڣ��յ���
		else if (code1 == 0 && code2 != 0) {
			if (flag == 1) {
				CSLineClip(Vertex[curnum].x, Vertex[curnum].y, Vertex[curnum + 1].x, Vertex[curnum + 1].y);
			}
			else if (flag == 0) {
				CSLineClip(Vertex[inlen - 1].x, Vertex[inlen - 1].y, Vertex[0].x, Vertex[0].y);
			}
		}
		//����⣬�յ���
		else if (code1 != 0 && code2 == 0) {
			if (flag == 1) {
				CSLineClip(Vertex[curnum].x, Vertex[curnum].y, Vertex[curnum + 1].x, Vertex[curnum + 1].y);
			}
			else if (flag == 0) {
				CSLineClip(Vertex[inlen - 1].x, Vertex[inlen - 1].y, Vertex[0].x, Vertex[0].y);
			}
		}
		//����⣬�յ���
		else {
			//������
		}

		//��¼��򽻵�ͳ��򽻵㣬������


		//��ǰ�߶��ж��겢�����꣬����һ��ѭ������curnum
		if (curnum == inlen - 1) {
			curnum = 0;
			times++;
		}
		else {
			curnum++;
			times++;
		}

		//�ж�ѭ���˳�
		if (times == inlen) {
			break;
		}
	}

	for (int i = 0; i < outlen; i += 2) {
		line(keepx[i], keepy[i], keepx[i + 1], keepy[i + 1]);
	}

	_getch();				// �����������
	closegraph();			// �رջ�ͼ����
	//cout << outlen;
	/*
	//�����ж�
	for (int i = 0; i < outlen; i++) {
		cout << keepx[i] << " " << keepy[i] << endl;
	}
	*/
	return 0;
}