//ʵ�����ƣ����ֶ�άͼ�εļ��α任��ƽ�ơ���������ת���Գơ����У�
//��       �ܣ�����ϵͳ�����Ļ���ͼ�Σ��û����뼸�α任���ͣ���������û������Ĳ������ƶ�άͼ�εļ��α任���û�����������Բ鿴��̬����
//���뻷����Visual Studio 2022��EasyX_20220116
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<cmath>
using namespace std;

const double pi = 3.1415926;//�÷��ų����ķ�ʽ����Բ���ʣ����ú궨��define���Ӱ�ȫ

//���ֻ����任������ı����ͼ������ĵ����꣬��˿���ʹ��ԭ��������걻�ظ�ʹ��

//ƽ�Ʊ任��������������Ҫ����Ϊ���������ƽ�ƾ��룬�ڻ���ʱ�ú�ɫͼ�α�ʾƽ�Ʊ任
void Translation(const int* x, const int* y, const unsigned& n, const int& dx, const int& dy)
{
	//���Ȼ���һ��ƽ�Ʊ任ǰ��ͼ�Σ��Ա�չʾ����
	initgraph(1000, 800);
	setfillcolor(RED);
	POINT* p = new POINT[n];
	for (unsigned i = 0; i < n; i++)
	{
		p[i] = { x[i],y[i] };
	}
	fillpolygon(p, n);
	_getch();
	//չʾƽ��ͼ�Σ���ԭͼ����ͬһ��ͼ��
	for (unsigned i = 0; i < n; i++)
	{
		p[i].x += dx;
		p[i].y += dy;
	}
	fillpolygon(p, n);
	_getch();
	return;
}

//�����任��������������Ҫ����Ϊ���������ı����任ϵ�����ڻ���ʱ�û�ɫͼ�α�ʾ�����任
void ScaleChange(const int* x, const int* y, const unsigned& n, const double& sx, const double& sy)
{
	//���ǵ�ʵ�ʹ����вο��㲻һ����ԭ�㣬������û������Ƿ�����ԭ����Ϊ�ο���
	int DefaultPoint;
	cout << "��ȷ���Ƿ����Ĭ�ϲο���(0,0)��1��ʾʹ�ã����������ʾ��ʹ��)��";
	cin >> DefaultPoint;
	POINT* p = new POINT[n];
	//ֱ��ʹ������ԭ����Ϊ�ο�������
	if (DefaultPoint == 1)
	{
		initgraph(1000, 800);
		setfillcolor(YELLOW);
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = x[i];
			p[i].y = y[i];
		}
		fillpolygon(p, n);
		_getch();
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x *= sx;
			p[i].y *= sy;
		}
		fillpolygon(p, n);
		_getch();
		return;
	}
	//�û��Զ���ο�������
	else
	{
		int x0, y0;
		cout << "������ο���ĺ�������:";
		cin >> x0 >> y0;
		initgraph(1000, 800);
		setfillcolor(YELLOW);
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = x[i];
			p[i].y = y[i];
		}
		fillpolygon(p, n);
		_getch();
		closegraph();
		initgraph(1000, 800);
		setfillcolor(YELLOW);
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = sx * p[i].x - (sx - 1) * x0;
			p[i].y = sy * p[i].y - (sy - 1) * y0;
		}
		fillpolygon(p, n);
		_getch();
		return;
	}
}

//��ת�任��������������Ҫ����Ϊ��ת�Ƕȣ���ͼʱ����ɫ��ʾ��ת����
void Rotation(const int* x, const int* y, const unsigned& n, const double& angle)
{
	//������任���ƣ����û�����ѡ���Ƿ�������ԭ��Ϊ��ת����
	int DefaultPoint;
	cout << "��ѡ���Ƿ����Ĭ�ϲο���(0,0)(1��ʾʹ�ã����������ʾ��ʹ�ã���";
	cin >> DefaultPoint;
	POINT* p = new POINT[n];
	double Angle = angle * pi / 180.0;
	//������ԭ����Ϊ��ת���ĵ����
	if (DefaultPoint == 1)
	{
		initgraph(1000, 800);
		setfillcolor(BLUE);
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = x[i];
			p[i].y = y[i];
		}
		fillpolygon(p, n);
		_getch();
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = int(double(x[i]) * cos(Angle) - double(y[i]) * sin(Angle) + 0.5);
			p[i].y = int(double(y[i]) * sin(Angle) + double(y[i]) * cos(Angle) + 0.5);
		}
		fillpolygon(p, n);
		_getch();
		return;
	}
	//���û��Զ���ĵ���Ϊ��ת���ĵ����
	else
	{
		int x0, y0;
		cout << "������ο���ĺ�������:";
		cin >> x0 >> y0;
		initgraph(1000, 800);
		setfillcolor(BLUE);
		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = x[i];
			p[i].y = y[i];
		}
		fillpolygon(p, n);
		_getch();

		for (unsigned i = 0; i < n; i++)
		{
			p[i].x = int(double(x[i] - x0) * cos(Angle) - double(y[i] - y0) * sin(Angle) + x0 + 0.5);
			p[i].y = int(double(x[i] - x0) * sin(Angle) + double(y[i] - y0) * cos(Angle) + y0 + 0.5);
		}
		fillpolygon(p, n);
		_getch();
		return;
	}
}

//�ԳƱ任��������������Ҫ����Ϊ�Գ���ķ��̣���ֱ�ߵ�һ��ʽ��ʾ������ɫͼ������ʾ�ԳƱ任
void Symmetry(const int* x, const int* y, const unsigned& n, const double& A, const double& B, const double& C)
{
	initgraph(1000, 800);
	setfillcolor(GREEN);
	POINT* p = new POINT[n];
	for (unsigned i = 0; i < n; i++)
	{
		p[i].x = x[i];
		p[i].y = y[i];
	}
	fillpolygon(p, n);
	_getch();
	for (unsigned i = 0; i < n; i++)
	{
		int tempx, tempy;
		tempx = p[i].x - int(2 * A * (A * p[i].x + B * p[i].y + C) / (A * A + B * B) + 0.5);
		tempy = p[i].y - int(2 * B * (A * p[i].x + B * p[i].y + C) / (A * A + B * B) + 0.5);
		p[i].x = tempx;
		p[i].y = tempy;
	}
	fillpolygon(p, n);
	_getch();
	return;
}

//���б任��������������Ҫ�����Ǻ��������Ĵ���ϵ������ǳ��ɫͼ�α�ʾ���б任
void StaggeredCutting(const int* x, const int* y, const unsigned& n, const double& a, const double& b)
{
	initgraph(1000, 800);
	setfillcolor(LIGHTBLUE);
	POINT* p = new POINT[n];
	for (unsigned i = 0; i < n; i++)
	{
		p[i].x = x[i];
		p[i].y = y[i];
	}
	fillpolygon(p, n);
	_getch();
	for (unsigned i = 0; i < n; i++)
	{
		int tempx, tempy;
		tempx = p[i].x + a * p[i].y;
		tempy = p[i].y + b * p[i].x;
		p[i].x = tempx;
		p[i].y = tempy;
	}
	fillpolygon(p, n);
	_getch();
	return;
}

int main(void)
{
	//��һ��������������Ϊ����ͼ�Σ���ȻҲ����ʹ����������ͼ�λ������û��Զ���һ������ͼ�Σ��˴�δ������
	int x[3] = { 100,100,150 };
	int y[3] = { 100,300,200 };

	//�����û����������жϽ��еĻ����任����
	int cmd;
	cout << "����������Ҫ���еĻ����任���ͣ�1��ʾƽ�ƣ�2��ʾ�����任��3��ʾ��ת��4��ʾ�Գƣ�5��ʾ���У���";
	cin >> cmd;
	if (cmd == 1)
	{
		int dx, dy;
		cout << "��ѡ��ƽ�Ʋ�������ֱ�������ݷ����ƽ�ƾ��룺";
		cin >> dx >> dy;
		cout << "����ȷ�ϳɹ������������������...(��ͼ�а��������������ɺ����������)" << endl;
		_getch();
		Translation(x, y, 3, dx, dy);//���κ�ֱ�ӵ���ƽ�ƺ���չʾ����Ч��
	}
	else if (cmd == 2)
	{
		double sx, sy;
		cout << "��ѡ������任��������������������ı任������";
		cin >> sx >> sy;
		ScaleChange(x, y, 3, sx, sy);//���κ�ֱ�ӵ��ñ����任����չʾ����Ч��
	}
	else if (cmd == 3)
	{
		double angle;
		cout << "��������ʱ����ת�ĽǶȴ�С���ýǶȱ�ʾ����";
		cin >> angle;
		Rotation(x, y, 3, angle);//ֱ�ӵ�����ת�������Ʊ任Ч��
	}
	else if (cmd == 4)
	{
		double A, B, C;
		cout << "������Գ����ֱ�߷��̲���������Ax+By+C=0���ֱ�����A��B��C����";
		cin >> A >> B >> C;
		cout << "����ȷ�ϳɹ������������������...(��ͼ��ɺ����������)" << endl;
		_getch();
		Symmetry(x, y, 3, A, B, C);//���öԳƺ���չʾ�ԳƱ任�ı任Ч��
	}
	else if (cmd == 5)
	{
		double a, b;
		cout << "��ֱ�����������ϵ�����������ϵ����";
		cin >> a >> b;
		cout << "����ȷ�ϳɹ������������������...����ͼ��ɺ���������أ�" << endl;
		StaggeredCutting(x, y, 3, a, b);//���ô��б任����չʾ����Ч��
	}
	else//�����������룬���˳����������ص���ʾ��Ϣ
	{
		cout << "û���ҵ���Ӧ�Ļ�ͼ����Ŷ~" << endl;
	}
	return 0;
}