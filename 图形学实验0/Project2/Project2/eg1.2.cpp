//////////////////////////////////////////////////////
// �������ƣ�һ�ʻ���
// ��	�ܣ�һ�ʻ��������Ρ�b��b��һ�ܵ�ͼ��
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-2-24

#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <math.h>

int main()
{
	initgraph(640, 480);	// ������ͼ���ڣ���СΪ 640x480 ����

	//������
	moveto(100, 200);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	setlinecolor(RED);
	lineto(200, 400);
	setlinecolor(GREEN);
	lineto(100, 300);
	setlinecolor(BLUE);
	lineto(100, 200);

	//b
	moveto(300, 200);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	setlinecolor(YELLOW);
	lineto(300, 400);
	lineto(400, 400);
	lineto(400, 300);
	lineto(300, 300);

	//b��һ����
	moveto(500, 200);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
	setlinecolor(YELLOW);
	lineto(500, 400);
	lineto(600, 400);
	lineto(600, 300);
	lineto(500, 300);
	lineto(600, 400);

	_getch();				// �����������
	closegraph();			// �رջ�ͼ����
	return 0;
}