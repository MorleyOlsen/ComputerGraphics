//////////////////////////////////////////////////////
// �������ƣ�LB�ü�
// ��	�ܣ���Liang-Barsky�㷨ʵ��ֱ�߶βü�
// ���뻷����VS2019��EasyX_20220116
// ��	�ߣ������<2020301010225><1597493790@qq.com>
// ����޸ģ�2022-3-17

#include <graphics.h>
#include <conio.h>
#include <iostream>
using namespace std;

float XL, XR, YT, YB;

void Displayline(float x1, float y1, float x2, float y2) {
    setlinecolor(WHITE);
    line(x1, y1, x2, y2);
}

void LiangBarsky(float x1, float y1, float x2, float y2, float XL, float XR, float YT, float YB) {
    float ansx1, ansx2, ansy1, ansy2;
    //ƽ����y��
    if (x1 - x2 == 0) {
        if (x1<XL || x1>XR) {
            return;
        }
        else {
            int ymin = max(YB, min(y1, y2));
            int ymax = min(YT, max(y1, y2));
            if (ymin <= ymax) {
                ansx1 = ansx2 = x1;
                ansy1 = ymin;
                ansy2 = ymax;
            }
            else {
                return;
            }
        }
    }
    //ƽ����x��
    else if (y1 - y2 == 0) {
        if (y1<YB || y1>YT) {
            return;
        }
        else {
            int xmin = max(XL, min(x1, x2));
            int xmax = min(XR, max(x1, x2));
            if (xmin <= xmax) {
                ansy1 = ansy2 = y1;
                ansx1 = xmin;
                ansx2 = xmax;
            }
            else {
                return;
            }
        }
    }
    //��ƽ����������
    else {
        float p1, p2, p3, p4;
        float q1, q2, q3, q4;
        p1 = -(x2 - x1);
        p2 = -p1;
        p3 = -(y2 - y1);
        p4 = -p3;
        q1 = x1 - XL;
        q2 = XR - x1;
        q3 = y1 - YB;
        q4 = YT - y1;
        float u1, u2, u3, u4;
        u1 = q1 / p1;
        u2 = q2 / p2;
        u3 = q3 / p3;
        u4 = q4 / p4;
        float umin, umax;
        if (p1 < 0) {
            if (p3 < 0) {
                umin = max(0, max(u1, u3));
                umax = min(1, min(u2, u4));
            }
            else {
                umin = max(0, max(u1, u4));
                umax = min(1, min(u2, u3));
            }
        }
        else {
            if (p3 < 0) {
                umin = max(0, max(u2, u3));
                umax = min(1, min(u1, u4));
            }
            else {
                umin = max(0, max(u2, u4));
                umax = min(1, min(u1, u3));
            }
        }
        if (umin <= umax) {
            ansx1 = x1 + umin * (x2 - x1);
            ansx2 = x1 + umax * (x2 - x1);
            ansy1 = y1 + umin * (y2 - y1);
            ansy2 = y1 + umax * (y2 - y1);
        }
        else {
            return;
        }
    }
    Displayline(ansx1, ansy1, ansx2, ansy2);
    return;
}

int main() {
    //�û�����a��b����
    float xa, ya, xb, yb;
    cout << "please input the coordinate of A point:" << endl;
    cin >> xa >> ya;
    cout << "please input the coordinate of B point:" << endl;
    cin >> xb >> yb;
    float x0, y0, x1, y1;
    //0->left bottom; 1->right top;

    initgraph(640,480);
    ExMessage m;
    //����AB�߶Σ���ɫ
    setlinecolor(GREEN);
    line(xa, ya, xb, yb);

    while (true) {
        m = getmessage(EX_MOUSE | EX_KEY);
        switch (m.message) {
        case WM_LBUTTONDOWN:
            x0 = m.x;
            y0 = m.y;
            setlinecolor(WHITE);
            setfillcolor(GREEN);
            fillrectangle(m.x - 3, m.y - 3, m.x + 3, m.y + 3);
        case WM_RBUTTONDOWN:
            x1 = m.x;
            y1 = m.y;
            setlinecolor(WHITE);
            setfillcolor(GREEN);
            fillrectangle(m.x - 3, m.y - 3, m.x + 3, m.y + 3);
            //�ж��û�������~���� / ����~���� / ����~���� / ����~����
            if ((x0 < x1) && (y0 > y1)) {
                XL = x0;
                XR = x1;
                YB = y1;
                YT = y0;
            }
            else if ((x0 < x1) && (y0 < y1)) {
                XL = x0;
                XR = x1;
                YB = y0;
                YT = y1;
            }
            else if ((x0 > x1) && (y0 > y1)) {
                XL = x1;
                XR = x0;
                YB = y1;
                YT = y0;
            }
            else if ((x0 > x1) && (y0 < y1)) {
                XL = x1;
                XR = x0;
                YB = y0;
                YT = y1;
            }
            //���ղü���
            setlinecolor(RED);
            line(XL, YT, XR, YT);
            line(XL, YB, XR, YB);
            line(XL, YT, XL, YB);
            line(XR, YT, XR, YB);
            //�ü�����Ϊ��ɫ
            LiangBarsky(xa, ya, xb, yb, XL, XR, YT, YB);
        case WM_KEYDOWN:
            if (m.vkcode == VK_ESCAPE)
                return 0;	// �� ESC ���˳�����
        }
    }
    closegraph();  //�رջ�ͼ����
    return 0;
}