//////////////////////////////////////////////////////
// �������ƣ�������
// ��	�ܣ�������ͼ��ʾ�����β����
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-2-24

#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
int main()
{
	initgraph(640, 480);	// ������ͼ���ڣ���СΪ 640x480 ����

	int point1[] = { 100,0,128,0,48,80,150,80,170,100,0,100,100,0 };
	int point2[] = { 0,100,20,120,220,120,128,28,113,43,170,100,0,100 };
	int point3[] = { 76,80,128,28,220,120,228,100,128,0,48,80,76,80 };

	/*
	moveto(100, 0);
	for (int i = 2; i < 14; i+=2) {
		lineto(point1[i], point1[i + 1]);
	}
	*/
	setfillcolor(RED);
	solidpolygon((POINT*)point1, 7);
	setfillcolor(YELLOW);
	solidpolygon((POINT*)point2, 7);
	setfillcolor(BLUE);
	solidpolygon((POINT*)point3, 7);

	_getch();				// �����������
	closegraph();			// �رջ�ͼ����
	return 0;
}