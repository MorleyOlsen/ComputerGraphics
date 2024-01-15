#include<iostream>
#include<graphics.h>
#include<conio.h>
using namespace std;
const int gap = 20;//Ϊ��ʹ��չʾ����ͼЧ��ʱ������ͼ���ص��������һ�������������ͼ�໥����һ������

//����һ��ͨ�ú������ڻ���������ά���������ͼ���нϺõ�չʾЧ����ֻ��Ҫ�����ռ��Ժ͵����������
void ThreeViews(const int* X, const int* Y, const int* Z, const unsigned& num)
{
	POINT* FrontView = new POINT[num];
	//Ϊ�˷���չʾ�Լ������긺����ͼ�εĻ��ƣ�������ԭ���ƶ�����ͼ������Ĳ�ʹ����������ȡ��������ʵ����һ��������ı任���̣�
	for (unsigned i = 0; i < num; i++)
	{
		FrontView[i].x = X[i] + 500 + gap;//�����걾���䣬������������ϵ�任��Ҫ����500������ΪչʾЧ�������ۼ���һ�����GAP
		FrontView[i].y = 350 - Z[i] - gap;//��������ķ���ȡ����������ԭ��ı䣬�����Ҫת��������ֵ������ȡԭֵ
	}

	//����һ��������洢����ͼ�ĵ�����
	POINT* SideView = new POINT[num];
	for (unsigned i = 0; i < num; i++)
	{
		SideView[i].x = Y[i] + 250 - gap;//����ԭ������������ͼ������
		SideView[i].y = 350 - Z[i] - gap;
	}
	//����һ��������洢����ͼ�ĵ�����
	POINT* VerticalView = new POINT[num];
	for (unsigned i = 0; i < num; i++)
	{
		VerticalView[i].x = X[i] + 520;
		VerticalView[i].y = 600 - Y[i] + gap;
	}

	initgraph(1000, 700);
	//�ֱ����������໥��ֱ�ľ�����ͼ���ĵ�ֱ����Ϊ����������
	line(0, 350, 1000, 350);
	line(500, 0, 500, 700);
	setcolor(GREEN);
	//��������ͼ���ڵ�һ�����ڣ�
	for (unsigned i = 0; i < num - 1; i++)
	{
		line(FrontView[i].x, FrontView[i].y, FrontView[i + 1].x, FrontView[i + 1].y);
	}
	_getch();
	//��������ͼ���ڵڶ������ڣ�
	for (unsigned i = 0; i < num - 1; i++)
	{
		line(SideView[i].x, SideView[i].y, SideView[i + 1].x, SideView[i + 1].y);
	}
	_getch();
	//��������ͼ���ڵ��������ڣ�
	for (unsigned i = 0; i < num - 1; i++)
	{
		line(VerticalView[i].x, VerticalView[i].y, VerticalView[i + 1].x, VerticalView[i + 1].y);
	}
	_getch();
	closegraph();
	//���Ҫ�����ͷŶ��ڵ��ڴ�ռ�
	delete[]FrontView;
	delete[]SideView;
	delete[]VerticalView;
	return;
}


//����ͨ�õ�����άͼ�ε��������ͼ�ĺ�����ֻ��Ҫ�������������������͵���������ĸ�������
void PositiveAxonometric(const int* X, const int* Y, const int* Z, const unsigned& num)
{
	initgraph(1000, 700);
	line(0, 350, 1000, 350);
	line(500, 0, 500, 700);
	setcolor(YELLOW);//�û�ɫ�����������ͼ��������֮ǰ����ɫ��������ͼ
	POINT* p = new POINT[num];
	//���������任��ĵ��������ֳɵĹ�ʽ��ֱ�����ü���
	for (unsigned i = 0; i < num; i++)
	{
		p[i].x = 0.7071 * X[i] - 0.7071 * Y[i] + 500;
		p[i].y = 350 + 0.4082 * X[i] + 0.4082 * Y[i] - 0.8165 * Z[i];
	}
	//�����������ֱ�߻�ͼ����
	for (unsigned i = 0; i < num - 1; i++)
	{
		line(p[i].x, p[i].y, p[i + 1].x, p[i + 1].y);
	}
	_getch();
	closegraph();
	delete[]p;//���Ҫ�����ͷŶ��ڵ��ڴ�ռ�
	return;
}

int main(void)
{
	//����Ŀռ����������Ǳ���Ĺؼ�����Ϊ��Ҫ���徭����άͶӰ�����֮����Ȼ����ԭ�е����������ϵ����˴˴��������ԵĶ���Ϊ����������������������ĵ�˳���ܹ�����̧�ʵء�
	//�������Ƴ���ȷ����ά����
	int X[33] = { 0,0,0,0,0,0,0,0,100,100,0,100,100,100,100,100,100,100,100,0,0,0,0,100,100,100,100,0,0,0,0,100,100 };
	int Y[33] = { 0,0,250,250,200,150,0,0,0,0,0,0,150,200,250,250,0,0,150,150,0,150,200,200,150,200,250,250,200,250,250,250,250 };
	int Z[33] = { 100,0,0,50,50,100,100,0,0,100,100,100,100,50,50,0,0,100,100,100,100,100,50,50,100,50,50,50,50,50,0,0,50 };
	
	
	ThreeViews(X, Y, Z, 33);
	_getch();
	PositiveAxonometric(X, Y, Z, 33);
	return 0;
}