//////////////////////////////////////////////////////
// 程序名称：Bezier曲面
// 功	能：绘制Bezier曲面，并采用自行设计输入和交互修改数据点的方式。
// 编译环境：VS2019，EasyX_20220116
// 作	者：夏婉可<2020301010225><1597493790@qq.com>
// 最后修改：2022-5-13
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <math.h>
using namespace std;
#define PI 3.1415926

//定义 N * N 的控制点数组
const int N = 8;
float controlPoints[N][N][3] ={
    { {-150, -150, 100}, {-100, -150, 0}, {-50, -150, 0}, {0, -150, 50}, {50, -150, 0}, {100, -150, 0}, {150, -150, -100}, {200, -150, 0} },
    { {-150, -100, 0}, {-100, -100, 50}, {-50, -100, -100}, {0, -100, 0}, {50, -100, 0}, {100, -100, 100}, {150, -100, 0}, {200, -100, -50} },
    { {-150, -50, 0}, {-100, -50, 0}, {-50, -50, 50}, {0, -50, 0}, {50, -50, 0}, {100, -50, 0}, {150, -50, -50}, {200, -50, 0} },
    { {-150, 0, -50}, {-100, 0, -100}, {-50, 0, 0}, {0, 0, 150}, {50, 0, 0}, {100, 0, -100}, {150, 0, -50}, {200, 0, -50} },
    { {-150, 50, 0}, {-100, 50, 0}, {-50, 50, -100}, {0, 50, 0}, {50, 50, 50}, {100, 50, 0}, {150, 50, 0}, {200, 50, 50} },
    { {-150, 100, 50}, {-100, 100, 0}, {-50, 100, 0}, {0, 100, -50}, {50, 100, -50}, {100, 100, 50}, {150, 100, 0}, {200, 100, 0} },
    { {-150, 150, 0}, {-100, 150, 100}, {-50, 150, -100}, {0, 150, 0}, {50, 150, 0}, {100, 150, 0}, {150, 150, -150}, {200, 150, 50} },
    { {-150, 200, 0}, {-100, 200, 0}, {-50, 200, 50}, {0, 200, -50}, {50, 200, 0}, {100, 200, -100}, {150, 200, 0}, {200, 200, 50} }
};

//计算贝塞尔基函数的C值
int C(int n, int k) {
    if (k > n) {
        return 0;
    }
    int c = 1;
    for (int i = 0; i < k; i++) {
        c *= (n - i);
        c /= (i + 1);
    }
    return c;
}

//勾勒函数
void display(float x, float y, float z) {
    putpixel(int(0.7071 * x - 0.7071 * y + 0.5f + 400), int(-0.4082 * x - 0.4082 * y + 0.8165 * z + 0.5f + 300), RED);
    putpixel(int(0.7071 * x - 0.7071 * y + 0.5f + 400) + 1, int(-0.4082 * x - 0.4082 * y + 0.8165 * z + 0.5f + 300), RED);
    putpixel(int(0.7071 * x - 0.7071 * y + 0.5f + 400) - 1, int(-0.4082 * x - 0.4082 * y + 0.8165 * z + 0.5f + 300), RED);
    putpixel(int(0.7071 * x - 0.7071 * y + 0.5f + 400), int(-0.4082 * x - 0.4082 * y + 0.8165 * z + 0.5f + 300) + 1, RED);
    putpixel(int(0.7071 * x - 0.7071 * y + 0.5f + 400), int(-0.4082 * x - 0.4082 * y + 0.8165 * z + 0.5f + 300) - 1, RED);
    putpixel(int(0.7071 * x - 0.7071 * y + 0.5f + 400) + 1, int(-0.4082 * x - 0.4082 * y + 0.8165 * z + 0.5f + 300) + 1, RED);
    putpixel(int(0.7071 * x - 0.7071 * y + 0.5f + 400) + 1, int(-0.4082 * x - 0.4082 * y + 0.8165 * z + 0.5f + 300) - 1, RED);
    putpixel(int(0.7071 * x - 0.7071 * y + 0.5f + 400) - 1, int(-0.4082 * x - 0.4082 * y + 0.8165 * z + 0.5f + 300) + 1, RED);
    putpixel(int(0.7071 * x - 0.7071 * y + 0.5f + 400) - 1, int(-0.4082 * x - 0.4082 * y + 0.8165 * z + 0.5f + 300) - 1, RED);
}

//Bezier曲面绘制
void Bezier() {
    //绘制控制点
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            fillcircle(int(0.7071 * controlPoints[i][j][0] - 0.7071 * controlPoints[i][j][1] + 0.5f + 400), int(-0.4082 * controlPoints[i][j][0] - 0.4082 * controlPoints[i][j][1] + 0.8165 * controlPoints[i][j][2] + 0.5f + 300), 3);
        }
    }
    // 绘制贝塞尔曲面
    const int nPoints = 50;  // 每行/列计算的点数
    float uStep = 1.0f / nPoints;
    float vStep = 1.0f / nPoints;
    for (float u = 0; u < 1; u += uStep) {
        for (float v = 0; v < 1; v += vStep) {
            float x = 0, y = 0, z = 0;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    // 计算贝塞尔基函数的值
                    float basisU = powf(1 - u, N - 1 - i) * powf(u, i) * float(C(N - 1, i));
                    float basisV = powf(1 - v, N - 1 - j) * powf(v, j) * float(C(N - 1, j));
                    float basis = basisU * basisV;
                    // 使用贝塞尔基函数的值和控制点计算曲面上的点
                    x += basis * controlPoints[i][j][0];
                    y += basis * controlPoints[i][j][1];
                    z += basis * controlPoints[i][j][2];
                }
            }
            // 将曲面上的点连接起来
            display(x, y, z);
        }
    }
}

//主函数
int main(){
    initgraph(800, 600);
    Bezier();
    ExMessage m;
    while (1) {
        m = getmessage(EX_MOUSE | EX_KEY);
        switch (m.message) {
        case WM_RBUTTONDOWN:
            //右键修改坐标信息
            closegraph();
            int row, column, newx, newy, newz;
            //输入数组中的坐标，进行修改
            cout << "which point do you want to change? please input its row & column array number" << endl;
            while (1) {
                cin >> row;
                cin >> column;
                if (row >= N) {
                    cout << "row number input error, try again" << endl;
                }
                else if (column >= N) {
                    cout << "column number input error, try again" << endl;
                }
                else {
                    break;
                }
            }
            cout << "please input the reset coordinate" << endl;
            cin >> newx >> newy >> newz;
            controlPoints[row][column][0] = newx;
            controlPoints[row][column][1] = newy;
            controlPoints[row][column][2] = newz;
            cout << "successfully reset, please wait a second to see a new graph" << endl;
            initgraph(800, 600);

        case WM_LBUTTONDOWN:
            //左键绘制
            Bezier();

        case WM_KEYDOWN:
            //退出图形化界面
            if (m.vkcode == VK_ESCAPE) {
                return 0;
            }
        }
    }
    
    _getch();
    closegraph();
    return 0;
}