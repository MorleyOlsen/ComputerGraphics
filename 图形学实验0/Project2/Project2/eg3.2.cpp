//////////////////////////////////////////////////////
// �������ƣ�ģ��������
// ��	�ܣ�����������ȷ���߶���㣬̧�����ȷ���յ㲢��ͼ
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-2-24

#include <graphics.h>

int main()
{
	// ��ʼ��ͼ�δ���
	initgraph(640, 480);

	ExMessage m;		// ������Ϣ����

	while (true)
	{
		// ��ȡһ�����򰴼���Ϣ
		m = getmessage(EX_MOUSE | EX_KEY);

		switch (m.message) {
		case WM_LBUTTONDOWN:
			moveto(m.x, m.y);//ȷ�����
		case WM_LBUTTONUP:
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);//����style
			setlinecolor(RED);//����color
			lineto(m.x, m.y);//ȷ���ص㲢����
		case WM_KEYDOWN:
			if (m.vkcode == VK_ESCAPE)
				return 0;	// �� ESC ���˳�����
		}
	}

	// �ر�ͼ�δ���
	closegraph();
	return 0;
}
