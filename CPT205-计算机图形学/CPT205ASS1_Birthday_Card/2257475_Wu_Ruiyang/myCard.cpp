// File ID: BirthdayCard.cpp
// Title: Birthday Card ~ Mario adventure
// Author: Ruiyang.Wu sID:2257475

#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>
#include <functional>
#include <random>
#include <chrono>
#define PI 3.14159265358979323846
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
const int GL_MULTISAMPLE = 0x809D;

const int windowWidth = 1000; // 窗口宽度
const int windowHeight = 600; // 窗口高度
const int pixelSize = 3; // 每个“像素”小方块的大小，小人高66pix，宽42pix
float characterX = 100; // 小人的x坐标
float characterY = 50; // 小人的y坐标

const float gravity = 2; // 重力加速度
float jumpSpeed = 25; // 跳跃初速度
float moveSpeed = 7; //移动速度
float velocityY = 0; // y方向速度
bool isJumping = false; // 判断是否在跳跃中
bool moveLeft = false; // 向左移动的标志
bool moveRight = false; // 向右移动的标志
bool startedFlag = false;
bool gotCakeFlag = false;
int timestep = 0;
float textY = 700;

struct autoFlag{
    bool value = false;
    std::chrono::time_point<std::chrono::steady_clock> setTime;
};

autoFlag restartFlag;
autoFlag showInfoFlag;

// 改变flag状态
void setFlag(autoFlag &flag) {
    flag.value = true;
    flag.setTime = std::chrono::steady_clock::now(); // 记录当前时间
}

void checkFlag(autoFlag &flag) {
    if (flag.value) {
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - flag.setTime).count() >= 5) {
            flag.value = false; // 5秒后设置为false
//            std::cout << "Flag reset to false." << std::endl; // 调试输出
        }
    }
}

//* info
// 根据x坐标给出地板高度
int getFloor(float x){
    if(x<150) return 50;
    else if(x>=150 && x<200) return 100;
    else if(x>=200 && x<250) return 150;
    else if(x>=250 && x<300) return 200;
    else if(x>=300 && x<400) return 250;
    else if(x>=400 && x<500) return 0;
    else if(x>=500 && x<550) return 200;
    else if(x>=550 && x<600) return 150;
    else if(x>=600 && x<650) return 100;
    else return 50;
}



//* 绘制
// 定义16位颜色码的二维数组表示彩色像素小人，0xRRGGBBAA透明度的值范围是 0（完全透明）到 255（完全不透明）
unsigned int dR = 0xAC3232FF; //darkRed
unsigned int lR = 0xD95763FF; //lightRed
unsigned int dS = 0xD9A066FF; //darkSkin
unsigned int lS = 0xEEC39AFF; //lightSkin
unsigned int hC = 0x222034FF; //hairColor
unsigned int eC = 0x663931FF; //eyeColor
unsigned int bW = 0xCBDBFCFF; //blueWhite
unsigned int dG = 0x6ABE30FF; //darkGreen
unsigned int lG = 0x99E550FF; //lightGreen
unsigned int dB = 0x5B6EE1FF; //darkBlue
unsigned int lB = 0x639BFFFF; //lightBlue
unsigned int bL = 0x000000FF; //black
unsigned int tS = 0x00000000; //transparent

//Re: 小人
unsigned int pixelArt[22][14] = {
        {tS, tS, tS, tS, tS, tS, dR, lR, lR, lR, tS, tS, tS, tS},
        {tS, tS, tS, tS, dR, dR, dR, lR, lR, lR, lR, tS, tS, tS},
        {tS, tS, tS, dR, dR, lR, lR, lR, lR, lR, lR, lR, tS, tS},
        {tS, tS, tS, dR, lR, lR, bW, bW, bW, bW, bW, bW, bW, bW},
        {tS, tS, hC, hC, hC, dS, hC, dS, hC, dS, hC, hC, tS, tS},
        {tS, tS, tS, hC, hC, lS, dS, lS, lS, lS, lS, hC, tS, tS},
        {tS, tS, hC, hC, dS, lS, lS, eC, lS, lS, eC, tS, tS, tS},
        {tS, tS, tS, hC, dS, lS, lS, eC, lS, lS, eC, tS, tS, tS},
        {tS, tS, tS, dS, lS, lS, lS, lS, lS, lS, lS, tS, tS, tS},
        {tS, tS, dG, dS, dS, lS, lS, lS, lS, lS, lS, tS, tS, tS},
        {tS, tS, lB, lG, dB, dB, lB, bW, bW, bW, lB, lG, tS, tS},
        {tS, dB, lB, dB, lG, lB, lB, bW, bW, bW, lB, lG, tS, tS},
        {dB, lB, dG, dB, lG, lB, lB, bW, bW, bW, lB, dB, tS, tS},
        {lB, tS, dG, lG, dB, dB, lB, bW, bW, bW, lB, dB, dS, lS},
        {dS, tS, dG, hC, hC, hC, hC, hC, hC, hC, hC, tS, tS, tS},
        {lS, tS, tS, bL, bL, bL, bL, bL, bL, bL, bL, tS, tS, tS},
        {tS, tS, tS,  bL, bL, bL, bL, bL, bL, bL, bL, tS, tS, tS},
        {tS, tS, tS,  bL, bL, bL, bL, bL, bL, bL, bL, tS, tS, tS},
        {tS, tS, tS,  bL, bL, bL, tS, tS, bL, bL, bL, tS, tS, tS},
        {tS, tS, tS,  bL, bL, tS, tS, tS, bL, bL, tS, tS, tS, tS},
        {tS, tS, tS,  bL, tS, tS, tS, tS, bL, tS, tS, tS, tS, tS},
        {tS, tS, tS,  dR, tS, tS, tS, tS, dR, tS, tS, tS, tS, tS}
};

// 将32位颜色码转换为RGBA浮点数（0-1范围）
void colorFromHex(unsigned int hexColor, float &r, float &g, float &b, float &a) {
    r = ((hexColor >> 24) & 0xFF) / 255.0f; // 提取红色分量
    g = ((hexColor >> 16) & 0xFF) / 255.0f; // 提取绿色分量
    b = ((hexColor >> 8) & 0xFF) / 255.0f;  // 提取蓝色分量
    a = (hexColor & 0xFF) / 255.0f;         // 提取透明度
}

// 绘制一个像素方块（位置，颜色）
void drawPixel(int x, int y, unsigned int hexColor) {
    float r, g, b, a;
    colorFromHex(hexColor, r, g, b, a);
    glColor4f(r, g, b, a); // 设置颜色和透明度
    glBegin(GL_QUADS);      // 绘制四边形
    glVertex2f(x, y);
    glVertex2f(x + pixelSize, y);
    glVertex2f(x + pixelSize, y + pixelSize);
    glVertex2f(x, y + pixelSize);
    glEnd();
}

// 绘制角色
void renderPixelCharacter() {
    for (int row = 22; row >= 0; --row) { // 从最后一行开始
        for (int col = 0; col < 14; ++col) {
            unsigned int color = pixelArt[row][col];
            drawPixel(characterX + col * pixelSize, characterY + (21 - row) * pixelSize, color);
        }
    }
}


//Re: 楼梯
// 定义楼梯的宽度和高度，以及一个简单的楼梯结构
struct Platform {
    int x, y, width, height;
} platforms[] = {
        // 左侧
        {150, 50, 50, 50},
        {200, 100, 50, 50},
        {250, 150, 50, 50},
        {300, 200, 50, 50},
        {350, 200, 50, 50},
        // 右侧
        {500, 150, 50, 50},
        {550, 100, 50, 50},
        {600, 50, 50, 50},
        // 竖向左
        {350, 150, 50, 50},
        {350, 100, 50, 50},
        {350, 50, 50, 50},
        // 竖向右
        {500, 100, 50, 50},
        {500, 50, 50, 50},
};

// 渲染楼梯并模拟砖块纹理
void renderPlatforms() {
    for (const auto &platform : platforms) {
        float startX = platform.x;
        float startY = platform.y;
        float endX = platform.x + platform.width;
        float endY = platform.y + platform.height;

        glLineWidth(2.0f); // 你可以调整这个值来改变线的粗细
        glBegin(GL_LINE_LOOP);
        glColor3f(0.4f, 0.2f, 0.06f);
        glVertex2f(startX-1, startY-1);
        glVertex2f( startX-1, endY+1);
        glVertex2f( endX+1,  endY+1);
        glVertex2f(endX+1,  startY-1);
        glEnd();


        // 分段绘制小块以模拟砖块纹理
        const int numRows = 5; // 砖块行数
        const int numCols = 2; // 砖块列数
        float brickWidth = platform.width / numCols;
        float brickHeight = platform.height / numRows;

        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                // 模拟砖块的颜色变化
                if ((i + j) % 2 == 0) {
                    glColor3f(0.6f, 0.3f, 0.1f); // 暗色砖块
                } else {
                    glColor3f(0.7f, 0.4f, 0.2f); // 亮色砖块
                }

                // 计算每个小砖块的顶点
                float x1 = startX + j * brickWidth;
                float y1 = startY + i * brickHeight;
                float x2 = x1 + brickWidth;
                float y2 = y1 + brickHeight;

                glBegin(GL_QUADS);
                glVertex2f(x1, y1);
                glVertex2f(x2, y1);
                glVertex2f(x2, y2);
                glVertex2f(x1, y2);
                glEnd();
            }
        }
    }
}

//Re: 地刺
struct Spike{
    int x, y, width, height;
} spikes[] = {
        {400, 0, 25, 50},
        {425, 0, 25, 50},
        {450, 0, 25, 50},
        {475, 0, 25, 50},
};

void renderSpikes() {
    for (const auto &spike : spikes) {
        // 画平滑着色三角形
        glEnable(GL_SMOOTH);
        glBegin(GL_TRIANGLES);
        glColor3f(0.5,0.51,0.53);
        glVertex2f(spike.x,spike.y);    // left point
        glColor3f(0.73,0.80,0.96);
        glVertex2f(spike.x+0.5*spike.width,spike.y+spike.height); // high point
        glColor3f(0.5,0.51,0.53);
        glVertex2f(spike.x+spike.width,spike.y); // right point

        glColor3f(0.3,0.31,0.33);
        glVertex2f(spike.x+0.75*spike.width,spike.y);    // left point
        glColor3f(0.63,0.70,0.86);
        glVertex2f(spike.x+0.5*spike.width,spike.y+spike.height); // high point
        glColor3f(0.3,0.31,0.33);
        glVertex2f(spike.x+spike.width,spike.y); // right point
        glEnd();
        // 禁用平滑着色（如果你之后不需要它的话）
        glDisable(GL_SMOOTH);

        glLineWidth(1.0f);  // 设置线宽，你可以根据需要调整这个值
        glEnable(GL_LINE_SMOOTH);  // 启用抗锯齿线（可选）
        glBegin(GL_LINE_LOOP);
        glColor3f(0.0, 0.0, 0.0);  // 设置线条颜色，例如黑色
        glVertex2f(spike.x, spike.y);    // left point
        glVertex2f(spike.x + 0.5 * spike.width, spike.y + spike.height); // high point
        glVertex2f(spike.x + spike.width, spike.y); // right point
        glEnd();
    }
}

//Re: 地面
double fractionalPart(int x, int y) {
    double result = (7.0 * x + 3.0 * y) / 93.0;
    return std::fmod(result, 1.0); // 获取小数部分
}

float generatePseudoRandomNumber(int x, int y) {
    // 组合 x 和 y，并使用 hash 生成一个种子
    std::size_t seed = std::hash<int>()(x) ^ (std::hash<int>()(y) << 1);
    // 使用种子初始化随机数引擎
    std::mt19937 rng(static_cast<unsigned int>(seed)); // mt19937 是一个高质量伪随机数引擎
    // 定义一个范围在 [0, 100] 之间的均匀分布
    std::uniform_int_distribution<int> dist(0, 100);
    // 生成伪随机数
    float random = dist(rng)/100.0;
    return random;
}
// 定义地面的宽度和高度
struct Ground {
    int x, y, width, height;
} grounds[] = {
        {0, 0, 399, 50},
        {500, 0, 500, 50}
};

// 绘制地面并添加噪声
const int noiseResolution = pixelSize; // 噪声分辨率，越小越细腻
void drawGroundWithNoise() {
    for (const auto &g : grounds) {
        //土地层
        for (int x = g.x; x < g.x + g.width; x += noiseResolution) {
            for (int y = g.y; y < g.y + 36; y += noiseResolution) {
                float brownNoise = generatePseudoRandomNumber(x,y) * 0.2f;  // 生成与位置相关的随机棕色值
                glColor3f(0.6f+brownNoise, 0.4f+brownNoise, 0.2f+brownNoise);  // 应用噪声棕色值
                glBegin(GL_QUADS);
                glVertex2f(x, y);
                glVertex2f(x + noiseResolution, y);
                glVertex2f(x + noiseResolution, y + noiseResolution);
                glVertex2f(x, y + noiseResolution);
                glEnd();
            }
        }
        // 中间层
        for (int x = g.x; x < g.x + g.width; x += noiseResolution) {
            for (int y = g.y+36; y < g.y + 42; y += noiseResolution) {
                float randNoize = generatePseudoRandomNumber(x,y) * 0.2f;
                if(randNoize>0.1){
                    float greenNoise = 0.5f + randNoize;
                    float redNoise = greenNoise -0.2;
                    glColor3f(redNoise, greenNoise, 0.2f);  // 应用噪声绿色值
                    glBegin(GL_QUADS);
                    glVertex2f(x, y);
                    glVertex2f(x + noiseResolution, y);
                    glVertex2f(x + noiseResolution, y + noiseResolution);
                    glVertex2f(x, y + noiseResolution);
                    glEnd();
                } else{
                    float brownNoise = randNoize;  // 生成随机棕色值
                    glColor3f(0.6f+brownNoise, 0.4f+brownNoise, 0.2f+brownNoise);  // 应用噪声棕色值
                    glBegin(GL_QUADS);
                    glVertex2f(x, y);
                    glVertex2f(x + noiseResolution, y);
                    glVertex2f(x + noiseResolution, y + noiseResolution);
                    glVertex2f(x, y + noiseResolution);
                    glEnd();
                }
            }
        }
        // 草地层
        for (int x = g.x; x < g.x + g.width; x += noiseResolution) {
            for (int y = g.y+ 42; y < g.y + 50; y += noiseResolution) {
                float greenNoise = 0.5f + fractionalPart(x,y) * 0.2f;  // 生成随机绿色值
                float redNoise = greenNoise -0.2;
                glColor3f(redNoise, greenNoise, 0.2f);  // 应用噪声绿色值
                glBegin(GL_QUADS);
                glVertex2f(x, y);
                glVertex2f(x + noiseResolution, y);
                glVertex2f(x + noiseResolution, y + noiseResolution);
                glVertex2f(x, y + noiseResolution);
                glEnd();
            }
        }
    }
}

//Re: 天空 天蓝(84,176,255)鱼肚白(231,207,172);黄昏(230,120,105)晚霞(254,129,0);黑夜(5,17,56)深蓝(42,119,144)
// 插值函数，计算两个颜色之间的中间颜色
void interpolateColor(float x, int up, double *out_r, double *out_g, double *out_b) {
    if (up == 1) { // 上半部分颜色
        if (x >= 0 && x < 350) {
            double scaledX = x / 350.0;
            // 天蓝(84,176,255)到黄昏(230,120,105)
            *out_r = (84 * (1.0 - scaledX) + 230 * scaledX) / 255.0;
            *out_g = (176 * (1.0 - scaledX) + 120 * scaledX) / 255.0;
            *out_b = (255 * (1.0 - scaledX) + 105 * scaledX) / 255.0;
        } else { // 350 <= x < 1000
            double scaledX = (x - 350) / 500.0;
            // 黄昏(230,120,105)到黑夜(5,17,56)
            *out_r = (230 * (1.0 - scaledX) + 5 * scaledX) / 255.0;
            *out_g = (120 * (1.0 - scaledX) + 17 * scaledX) / 255.0;
            *out_b = (105 * (1.0 - scaledX) + 56 * scaledX) / 255.0;
        }
    } else { // 下半部分颜色
        if (x >= 0 && x < 350) {
            double scaledX = x / 350.0;
            // 鱼肚白(231,207,172)到晚霞(254,129,0)255 178 132
            *out_r = (231 * (1.0 - scaledX) + 254 * scaledX) / 255.0;
            *out_g = (207 * (1.0 - scaledX) + 178 * scaledX) / 255.0;
            *out_b = (172 * (1.0 - scaledX) + 132 * scaledX) / 255.0;
        } else { // 350 <= x < 1000
            double scaledX = (x - 350) / 500.0;
            // 晚霞(254,129,0)到深蓝(42,119,144)
            *out_r = (255 * (1.0 - scaledX) + 42 * scaledX) / 255.0;
            *out_g = (178 * (1.0 - scaledX) + 119 * scaledX) / 255.0;
            *out_b = (132 * (1.0 - scaledX) + 144 * scaledX) / 255.0;
        }
    }
}

void drawSky(){
    glEnable(GL_SMOOTH);
    glBegin(GL_QUADS);
    double iR, iG, iB;
    interpolateColor(characterX , 0, &iR, &iG, &iB);
    glColor3f(iR,iG,iB); // left down
    glVertex2f(0,0);
    glColor3f(iR,iG,iB); // right down
    glVertex2f(1000,0);
    interpolateColor(characterX , 1, &iR, &iG, &iB);
    glColor3f(iR,iG,iB); // right up
    glVertex2f(1000,600);
    glColor3f(iR,iG,iB); // left up
    glVertex2f(0,600);
    glEnd();
}

//Re: 背景城市
void drawBuildings(float translationX, float translationY){
    glPushMatrix(); // 保存当前矩阵状态
    glTranslatef(translationX, translationY, 0.0f); // 应用平移变换

    glColor3ub(84, 140, 186);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-50, 0);
    glVertex2f(0, 0);
    for (int i = 300; i < 330; i++) {
        double angle = i * 3.14159265 / 180.0;
        double x = 10 * cos(angle);
        double y = 10 * sin(angle) + 10;
        glVertex2f(x, y);
    }
    glVertex2f(8.5, 20);

    for (int i = 150; i > 100; i--) {
        double angle = angle = i * 3.14159265 / 180.0;
        double x = 10 * cos(angle) + 20;
        double y = 10 * sin(angle) + 20;
        glVertex2f(x, y);
    }

    glVertex2f(35, 30);
    glVertex2f(35, 5);

    for (int i = 210; i < 240; i++) {
        double angle = i * 3.14159265 / 180.0;
        double x = 10 * cos(angle) + 44;
        double y = 10 * sin(angle) + 10;
        glVertex2f(x, y);
    }

    glVertex2f(55, 0);
    glVertex2f(57, 70);
    glVertex2f(62, 60);
    glVertex2f(64, 78);
    glVertex2f(67, 60);
    glVertex2f(70, 70);
    glVertex2f(73, 20);
    glVertex2f(100, 20);
    for (int i = 300; i < 380; i++) {
        double angle = i * 3.14159265 / 180.0;
        double x = 10 * cos(angle) + 110;
        double y = 10 * sin(angle) + 30;
        glVertex2f(x, y);
    }
    for (int i = 90; i > 0; i--) {
        double angle = i * 3.14159265 / 180.0;
        double x = 10 * cos(angle) + 120;
        double y = 10 * sin(angle) + 25;
        glVertex2f(x, y);
    }
    glVertex2f(135, 0);
    glVertex2f(170, 0);
    glVertex2f(165, 20);
    glVertex2f(175, 18);
    glVertex2f(185, 19);
    glVertex2f(193, 17);
    glVertex2f(205, 15);
    glVertex2f(204, 0);
    glVertex2f(235, 0);
    glVertex2f(237, 68);
    glVertex2f(245, 0);
    glVertex2f(246, 1);
    glVertex2f(247, 1);
    glVertex2f(248, 2);
    glVertex2f(249, 3);
    glVertex2f(250, 3);
    glVertex2f(251, 20);
    glVertex2f(261, 19);
    glVertex2f(264, 0);
    glVertex2f(290, 0);
    glVertex2f(291, 10);
    glVertex2f(301, 11);
    glVertex2f(303, 70);
    glVertex2f(340, 68);
    glVertex2f(342, 4);
    for (int i = 210; i < 270; i++) {
        double angle = i * 3.14159265 / 180.0;
        double x = 10 * cos(angle) + 350;
        double y = 10 * sin(angle) + 10;
        glVertex2f(x, y);
    }
    glVertex2f(400, 0);
    glEnd();

    glPopMatrix();
}

//Re: 绘制CB
void drawCB(float translationX, float translationY, float w){    //绘制cb
    glPushMatrix(); // 保存当前矩阵状态
    glTranslatef(translationX, translationY, 0.0f); // 应用平移变换
//    glPushMatrix();
    glScalef(1.2f, 1.2f, 1.0f); // 在x和y方向上缩放1.5倍

    glLineWidth(w); // 设置边框线宽为2.0
    glColor3f(0.6f, 0.5f, 0.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(300, 350);
    glVertex2f(330, 350);
    glVertex2f(340, 330);
    glVertex2f(360, 330);
    glVertex2f(360, 350);
    glVertex2f(500, 350);
    glVertex2f(500, 240);
    glVertex2f(460, 240);
    glVertex2f(460, 300);
    glVertex2f(420, 300);
    glVertex2f(380, 240);
    glVertex2f(300, 240);
    glEnd();

    if(characterX>650){glColor3f(.9f, .9f, 0.2f);}
    else glColor3f(0.5f, 0.5f, 0.8f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(324, 350);
    glVertex2f(336, 325);
    glVertex2f(365, 325);
    glVertex2f(365, 350);
    glEnd();
    if(characterX>600){glColor3f(.9f, .9f, 0.2f);}
    else glColor3f(0.5f, 0.5f, 0.8f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(300, 240);
    glVertex2f(300, 235);
    glVertex2f(383, 235);
    glVertex2f(423, 295);
    glVertex2f(455, 295);
    glVertex2f(455, 235);
    glVertex2f(500, 235);
    glVertex2f(500, 240);
    glEnd();
    glColor3f(0.6f, 0.5f, 0.5f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(310, 235);
    glVertex2f(310, 190);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(490, 235);
    glVertex2f(490, 215);
    glEnd();
    // 下方梯形组合
    glColor3f(0.6f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(300, 188);
    glVertex2f(300, 165);
    glVertex2f(500, 165);
    glVertex2f(500, 215);
    glVertex2f(435, 215);;
    glEnd();
    if(characterX>550){glColor3f(.9f, .9f, 0.2f);}
    else glColor3f(0.5f, 0.6f, 1.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(500, 210);
    glVertex2f(438, 210);
    glVertex2f(300, 183);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(300, 170);
    glVertex2f(500, 170);
    glEnd();
    glColor3f(0.45f, 0.4f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(310, 165);
    glVertex2f(310, 145);
    glVertex2f(490, 145);
    glVertex2f(490, 165);
    glEnd();

    glPopMatrix();
}

//Re: 绘制文字
void renderBitmapString(float x, float y, void *font, const char *string) {
    glRasterPos2f(x, y); // 设置光栅位置
    while (*string) {
        glutBitmapCharacter(font, *string); // 绘制每个字符
        string++;
    }
}

//Re: 绘制星星
struct Star {
    float x;
    float y;
    float size;
    float rotation; // 旋转角度
    float alpha;
};
const int numStars = 12; // 星星数量
Star stars[numStars]; // 星星数组
// 初始化星星的位置和大小
void initStars() {
    srand(static_cast<unsigned int>(time(0))); // 用当前时间作为随机数种子
    for (int i = 0; i < numStars; ++i) {
        stars[i].x = static_cast<float>(rand() % 1000); // 随机x位置
        stars[i].y = static_cast<float>(rand() % 600 + 600); // 随机y位置（初始在视口上方）
        stars[i].size = static_cast<float>(rand() % 5 + 12); // 随机大小
        stars[i].alpha = 1.0;
    }
}
// 绘制五角星
void drawStar(const Star& star) {
    glPushMatrix();
    glTranslatef(star.x, star.y, 0);
    glRotatef(star.rotation, 0, 0, 1); // 旋转星星
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < 5; i++) {
        // 计算每个三角形的顶点
        float angle = 2 * PI / 5 * i; // 每个角的角度
        float outerX = star.size * cos(angle); // 外部顶点
        float outerY = star.size * sin(angle);
        float innerX = (star.size / 2) * cos(angle + PI / 5); // 内部顶点
        float innerY = (star.size / 2) * sin(angle + PI / 5);
        // 第一个顶点（中心）
        glColor4f(1.0f, 0.93f, 0.6f,star.alpha); // 顶部颜色
        glVertex2f(0, 0);
        // 外部顶点
        glColor4f(0.72f, 0.6f, 0,star.alpha); // 外部颜色
        glVertex2f(outerX, outerY);
        // 内部顶点
        glColor4f(0.82f, 0.7f, 0,star.alpha); // 内部颜色
        glVertex2f(innerX, innerY);
    }
    // 绘制星星的另一半
    for (int i = 0; i < 5; i++) {
        // 计算每个三角形的顶点
        float angle = 2 * PI / 5 * i; // 每个角的角度
        float outerX = star.size * cos(angle); // 外部顶点（相反方向）
        float outerY = star.size * sin(angle);
        float innerX = (star.size / 2) * cos(angle - PI / 5); // 内部顶点（相反方向）
        float innerY = (star.size / 2) * sin(angle - PI / 5);
        // 第一个顶点（中心）
        glColor4f(1.0f, 0.93f, 0.6f,star.alpha); // 顶部颜色
        glVertex2f(0, 0);
        // 外部顶点
        glColor4f(0.72f, 0.6f, 0,star.alpha); // 外部颜色
        glVertex2f(outerX, outerY);
        // 内部顶点
        glColor4f(0.82f, 0.7f, 0,star.alpha); // 内部颜色
        glVertex2f(innerX, innerY);
    }
    glEnd();
    glPopMatrix();
}
// 更新星星的位置
void updateStars() {
    for (int i = 0; i < numStars; ++i) {
        stars[i].y -= 0.2f; // 每帧向下移动
        if (stars[i].y<800) stars[i].alpha -= 0.0003;
        if (stars[i].y < 0) { // 如果星星掉出视口
            stars[i].y = static_cast<float>(rand() % 600+600); // 重置到上方
            stars[i].x = static_cast<float>(rand() % 1000); // 随机x位置
            stars[i].alpha = 1.0;
        }
    }
}

//Re: 绘制云彩
struct Cloud {
    float x;    // 云的 x 坐标
    float y;    // 云的 y 坐标
    float size; // 云的大小
};

std::vector<Cloud> clouds; // 存储云的数组
const int cloudCount = 8;  // 云的数量
const float cloudSpeed = 0.05f; // 云移动速度

void initClouds() {
    // 初始化云的位置和大小
    for (int i = 0; i < cloudCount; ++i) {
        Cloud cloud;
        cloud.x = rand() % 1000; // 随机 x 坐标
        cloud.y = 400 + rand() % 175; // 随机 y 坐标
        cloud.size = 20 + rand() % 40; // 随机大小
        clouds.push_back(cloud);
    }
}

void drawCloud(const Cloud& cloud) {
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 1.0f, 1.0f, 0.8f); // 白色云彩，带有透明度

    // 绘制简单的云彩形状
    for (int i = 0; i < 360; i += 15) {
        float angle = i * 3.14159f / 180; // 转换为弧度
        float x = cloud.x + cloud.size * cos(angle);
        float y = cloud.y + cloud.size * sin(angle) / 2; // 高度缩小
        glVertex2f(x, y);
    }
    glEnd();
}

void updateClouds() {
    for (auto& cloud : clouds) {
        cloud.x -= cloudSpeed; // 向右移动
        // 如果云超出屏幕，则将其重置到左侧
        if (cloud.x+cloud.size < 0) {
            cloud.x = windowWidth+cloud.size; // 重置到左侧，考虑云的大小
            cloud.y = 400 + rand() % 100; // 随机 y 坐标
        }
    }
    glutPostRedisplay(); // 触发重绘
}

//Re: 绘制月亮
void drawFullMoon(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.8f); // 设置颜色为淡黄色
    // 绘制圆形
    glVertex2f(x, y); // 圆心
    for (int i = 0; i <= 360; i++) {
        float angle = i * PI / 180; // 转换为弧度
        float xOffset = radius * cos(angle);
        float yOffset = radius * sin(angle);
        glVertex2f(x + xOffset, y + yOffset);
    }
    glEnd();
}

//Re: 绘制帮助窗口
void drawHelpWindow(){
    glBegin(GL_QUADS);
    glColor4ub(0, 0, 0, 128); // 黑色，50%透明度
    glVertex2f(90, 525);
    glVertex2f(395, 525);
    glVertex2f(395, 390);
    glVertex2f(90, 390);
    glEnd();
    glColor3ub(21,230,125);
    renderBitmapString(90,532,GLUT_BITMAP_HELVETICA_18,"Help Info:");
    glColor3ub(255,178,132);
    renderBitmapString(100,500,GLUT_BITMAP_TIMES_ROMAN_24,"Press [A] [D] to Move");
    renderBitmapString(100,475,GLUT_BITMAP_TIMES_ROMAN_24,"Press [W] to Jump");
    renderBitmapString(100,450,GLUT_BITMAP_TIMES_ROMAN_24,"Press [E] to Get the CARD!!!");
    renderBitmapString(100,425,GLUT_BITMAP_TIMES_ROMAN_24,"Press [Q] to Quit");
    renderBitmapString(100,400,GLUT_BITMAP_TIMES_ROMAN_24,"[Click] to get Balloons");
}

//Re: 震屏
// 震屏参数
bool shakeScreen = false;
float shakeIntensity = 5.0f; // 震动强度
int shakeDuration = 1000; // 震动持续时间（毫秒）
int shakeStartTime = 0;
// 声明一个全局变量保存摄像机的初始位置
float cameraX = 0.0f;
float cameraY = 0.0f;
// 震屏函数
void shake() {
    if (shakeScreen) {
        int currentTime = glutGet(GLUT_ELAPSED_TIME);
        if (currentTime - shakeStartTime < shakeDuration) {
            glLoadIdentity(); // 确保没有震动时，重置矩阵
            glTranslatef(cameraX, cameraY, 0); // 重新设置摄像机位置
            // 随机偏移
            float offsetX = (rand() % (int)(shakeIntensity * 2)) - shakeIntensity;
            float offsetY = (rand() % (int)(shakeIntensity * 2)) - shakeIntensity;
            // 应用震动偏移
            glTranslatef(offsetX, offsetY, 0);
        } else {
            shakeScreen = false; // 停止震动
            // 归位摄像机
            glLoadIdentity(); // 重置当前矩阵
            glTranslatef(cameraX, cameraY, 0); // 重新设置摄像机位置
        }
    } else {
        glLoadIdentity(); // 确保没有震动时，重置矩阵
        glTranslatef(cameraX, cameraY, 0); // 重新设置摄像机位置
    }
}
// 触发震屏的方法
void triggerShake() {
    shakeScreen = true; // 开始震动
    shakeStartTime = glutGet(GLUT_ELAPSED_TIME); // 记录震动开始时间

}

//Re: 蛋糕
const int numPoints = 1000; // 曲线上的点数
float A = 80.0f; // 振幅
float B = 60.0f; // 振幅
float a = 5; // x方向频率
float b = 4; // y方向频率
float delta = PI / 2; // 相位差
float theta = PI /4; //奶油角度
const int numSegments = 100; // 椭圆的分段数
const float ellipse1Width = 7.0f; // 椭圆1宽度
const float ellipse1Height = 15.0f; // 椭圆1高度
const float ellipse2Width = 15.0f; // 椭圆2宽度
const float ellipse2Height = 25.0f; // 椭圆2高度
int creamNumber = 10;
void lissajousCake(float lissaX, float lissaY){
    glBegin(GL_QUADS); // 蛋糕
    glColor3ub(242,182,192);
    glVertex2f(lissaX,lissaY);
    glVertex2f(lissaX,lissaY+2*B);
    glVertex2f(lissaX+2*A,lissaY+2*B);
    glVertex2f(lissaX+2*A,lissaY);
    glEnd();

    glBegin(GL_QUADS); // 蜡烛
    float leftX = lissaX + (4.0f / 5.0f) * A; // 使用浮点数确保计算正确
    float topY = lissaY + (2.0f + 2.0f / 3.0f) * B;
    glEnable(GL_SMOOTH);
    glColor3ub(255,140,130);
    glVertex2f(leftX, topY);
    glVertex2f(leftX + (2.0f / 5.0f) * A, topY); // 右上角
    glColor3ub(228,218,149);
    glVertex2f(leftX + (2.0f / 5.0f) * A, lissaY + 2 * B); // 右下角
    glVertex2f(leftX, lissaY + 2 * B);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 1.0f, 0.0f);
    for (int i = 0; i < numPoints; i++) {
        float t = (float)i / (float)numPoints * (2.0f * PI); // 从0到2π
        float x = A * sin(a * t + delta);
        float y = B * sin(b * t);
        glVertex2f(x +A+ lissaX, y +B+ lissaY); // 平移到视口中心
    }
    glEnd();

    for (int i = 0; i < creamNumber; i++) {
        float centerX = lissaX + 2 * A * i / (creamNumber-1);  // 每个椭圆的 x 坐标中心
        float centerY = lissaY + 2 * B;      // 每个椭圆的 y 坐标中心

        glBegin(GL_TRIANGLE_FAN); // 使用三角扇形填充椭圆
        glColor3f(1.0f, 1.0f, 0.9f); // 设置填充颜色为白色
        glVertex2f(centerX, centerY); // 椭圆的中心点

        for (int k = 0; k <= numSegments; k++) {
            float angle = 2.0f * PI * k / numSegments; // 当前角度
            float x = 15 * cos(angle); // 椭圆的 x 坐标
            float y = 8 * sin(angle);  // 椭圆的 y 坐标

            // 应用旋转
            float rotatedX = x * cos(theta) - y * sin(theta);
            float rotatedY = x * sin(theta) + y * cos(theta);

            // 平移到中心
            glVertex2f(rotatedX + centerX, rotatedY + centerY);
        }
        glEnd(); // 完成当前椭圆的绘制
    }

    float el1H = lissaY + (2.0f+2.0f/3.0f+1.0f/8.0f)* B;
    float el2H = lissaY + (2.0f+2.0f/3.0f+1.0f/4.0f)* B;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f); // 椭圆颜色（黄色）
    glVertex2f(lissaX+A, el2H); // 椭圆中心
    for (int i = 0; i <= numSegments; ++i) {
        float theta = (float)i / (float)numSegments * 2.0f * 3.14159f; // 角度
        float x = lissaX+A + (ellipse2Width / 2) * cos(theta); // X坐标
        float y = el2H + (ellipse2Height / 2) * sin(theta); // Y坐标
        glVertex2f(x, y); // 添加椭圆的顶点
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f); // 椭圆颜色（红色）
    glVertex2f(lissaX+A, el1H); // 椭圆中心
    for (int i = 0; i <= numSegments; ++i) {
        float theta = (float)i / (float)numSegments * 2.0f * 3.14159f; // 角度
        float x = lissaX+A + (ellipse1Width / 2) * cos(theta); // X坐标
        float y = el1H + (ellipse1Height / 2) * sin(theta); // Y坐标
        glVertex2f(x, y); // 添加椭圆的顶点
    }
    glEnd();
}

float cakeY = 600; // Start position (y-coordinate) high in the sky
float fallSpeed = 0; // Initial fall speed
float gravityCake = 0.5; // Gravity constant to control fall acceleration
bool cakeOnGround = FALSE;

// Function to update the cake position
void updateCakePosition() {
    if (gotCakeFlag && !cakeOnGround) {
        // Apply gravity to increase fall speed
        fallSpeed += gravityCake;
        cakeY -= fallSpeed; // Move the cake down by fallSpeed each frame

        // Check if the cake reached the ground (e.g., y = 0)
        if (cakeY <= 50) {
            cakeY = 50; // Stop at ground level
            cakeOnGround = false; // Stop the fall
            fallSpeed = 0; // Reset fall speed for future falls
        }
    }
}

//Re: 气球
const float maxHeight = 600.0f; // Height where balloon will burst
const float swaySpeed = 0.1f;  // Speed of sway
const float floatSpeed = 1.5f;  // Upward speed
struct Confetti {
    float x, y, size, fallSpeed;
    float color[3]; // RGB color
};

struct Balloon {
    float x, y;
    bool exploded;
    std::vector<Confetti> confetti;
};

std::vector<Balloon> balloons;

// Initialize a single balloon at a specified position
void initBalloon(float startX, float startY) {
    Balloon balloon = {startX, startY, false, {}};
    balloons.push_back(balloon);
}

// Spawn balloons at random horizontal positions along the bottom
void spawnBalloon() {
    float startX = static_cast<float>(rand() % 1000); // Adjust 1000 to window width
    float startY = 0.0f; // Start at the bottom
    initBalloon(startX, startY);
}

void spawnBalloonClick(float x, float y){
    initBalloon(x, y);
}

// Generate confetti for an exploded balloon
void generateConfetti(Balloon &balloon) {
    for (int i = 0; i < 20; ++i) {
        Confetti piece;
        piece.x = balloon.x + (rand() % 50 - 10);
        piece.y = balloon.y + (rand() % 20 - 10);
        piece.size = (rand() % 5 + 2);
        piece.fallSpeed = (rand() % 3 + 1) * 0.1f;
        piece.color[0] = (rand() % 100) / 100.0f;
        piece.color[1] = (rand() % 100) / 100.0f;
        piece.color[2] = (rand() % 100) / 100.0f;
        balloon.confetti.push_back(piece);
    }
}

// Update each balloon and its confetti
void updateBalloons() {
    for (auto &balloon : balloons) {
        if (!balloon.exploded) {
            // Upward movement with sway
            balloon.y += floatSpeed;
            balloon.x += swaySpeed * sin(balloon.y / 15.0f)*3;

            // Check if it should explode
            if (balloon.y >= maxHeight) {
                balloon.exploded = true;
                generateConfetti(balloon);
            }
        } else {
            // Update confetti falling
            for (auto &piece : balloon.confetti) {
                piece.y -= piece.fallSpeed; // Apply gravity
                piece.x += (rand() % 3 - 1) * 0.5f; // Slight horizontal movement
            }
        }
    }
}

// Render each balloon and its confetti
void renderBalloons() {
    for (const auto &balloon : balloons) {
        if (!balloon.exploded) {
            // Render the balloon body
            glColor3f(1.0f, 0.5f, 0.7f); // Balloon color
            glPushMatrix();
            glTranslatef(balloon.x, balloon.y, 0.0f);

            // Draw balloon as filled ellipse
            glBegin(GL_TRIANGLE_FAN);
            for (int angle = 0; angle <= 360; angle += 10) {
                float rad = angle * (PI / 180.0f); // Convert to radians
                float ellipseX = 15.0f * cos(rad); // Width of the balloon
                float ellipseY = 20.0f * sin(rad); // Height of the balloon
                glVertex2f(ellipseX, ellipseY);
            }
            glEnd();

            // Draw knot at the bottom of the balloon
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(0.9f, 0.4f, 0.6f); // Slightly darker for knot
            glVertex2f(0.0f, -20.0f);
            glVertex2f(-3.0f, -23.0f);
            glVertex2f(3.0f, -23.0f);
            glEnd();

            glPopMatrix();

            // Draw the string attached to the balloon
            glColor3f(0.5f, 0.5f, 0.5f); // String color
            glBegin(GL_LINES);
            glVertex2f(balloon.x, balloon.y - 20.0f); // Starting point at knot
            glVertex2f(balloon.x, balloon.y - 50.0f); // Length of the string
            glEnd();
        } else {
            // Render confetti for the exploded balloon
            for (const auto &piece : balloon.confetti) {
                glColor3fv(piece.color);
                glRectf(piece.x - piece.size / 2, piece.y - piece.size / 2,
                        piece.x + piece.size / 2, piece.y + piece.size / 2);
            }
        }
    }
}

//Re: 字体
void selectFont(int size, int charset, const char* face){
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
                              charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

void drawString(const char* str) {
    int len;
    wchar_t* wstring;
    HDC hDC = wglGetCurrentDC();
    GLuint list = glGenLists(1);

    // 使用 UTF-8 编码进行转换
    len = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
    wstring = (wchar_t*)malloc(len * sizeof(wchar_t));

    // 转换为宽字符
    MultiByteToWideChar(CP_UTF8, 0, str, -1, wstring, len);

    for (int i = 0; i < len - 1; ++i) { // 忽略最后的 '\0'
        wglUseFontBitmapsW(hDC, wstring[i], 1, list);
        glCallList(list);
    }

    free(wstring);
    glDeleteLists(list, 1);
}

void drawtext1() {
    glBegin(GL_QUADS);
    glColor4ub(0, 0, 0, 70); // 黑色透明
    glVertex2f(190, textY+25);  // 左上
    glVertex2f(760, textY+25);  // 右上
    glVertex2f(760, textY-65);
    glVertex2f(190, textY-65);
    glEnd();

    glColor3f(1.0f, 0.7f, 0.8f);
    selectFont(35, ANSI_CHARSET, "Lucida Handwriting");
    glRasterPos2f(300, textY);
    drawString("HHappy Birthday to YOU!");

    glColor3f(1.0, 1.0, 1.0);
    selectFont(35, ANSI_CHARSET, "SimSun");
    glRasterPos2f(200, textY-55);
    drawString("\\(^Д^*)/祝你生日快乐!(ﾉ´▽｀)ﾉ♪"); //お誕生日おめでとう
}

void updateText1(){
    if (textY>360){
        textY -= 0.8f;
    }else
        textY = 360;
}

//Re: 信封
int enveTime = 0;
void drawEnvelope(float x, float enveY) {
    float y = enveY + (sin(++enveTime*PI/50.0)+1.0)*10.0;
    float width = 80;
    float height = 48;

    glColor3ub(200,200,200);
    renderBitmapString(916,y + 79,GLUT_BITMAP_HELVETICA_18,"Press [E]");
    glColor3ub(10,10,10);
    renderBitmapString(915,y + 80,GLUT_BITMAP_HELVETICA_18,"Press [E]");

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.6f); // 信纸黄色
    glVertex2f(x + 5, y + 5);
    glVertex2f(x + width - 5, y + 5);
    glVertex2f(x + width - 5, y + height +25);
    glVertex2f(x + 5, y + height +25);
    glEnd();
    glLineWidth(1);
    // Draw the line
    glBegin(GL_LINES);
    glColor3f(0.15,0.15,0.1);
    glVertex2f(x + 5+9, y + height +20);
    glVertex2f(x + width - 5-9, y + height +20);
    glVertex2f(x + 5+9, y + height +16);
    glVertex2f(x + width - 5-9, y + height +16);
    glVertex2f(x + 5+9, y + height +12);
    glVertex2f(x + width - 5-9, y + height +12);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f); // 信封颜色为白色
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width / 2, y + height + 20); // 顶部尖角
    glVertex2f(x, y + height);
    glEnd();

    // 绘制信封内部
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f); // 内部颜色为灰色
    glVertex2f(x + 5, y + 5);
    glVertex2f(x + width - 5, y + 5);
    glVertex2f(x + width - 5, y + height - 5);
    glVertex2f(x + 5, y + height - 5);
    glEnd();

    // Draw heart in the center
    float heartX = x + width / 2;
    float heartY = y + height / 2;
    float radius = 6.0f; // Radius of heart's circular parts
    glColor3f(1.0f, 0.0f, 0.0f); // Heart color red
    // Left semi-circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(heartX - radius / 2-5, heartY); // Center of the left circle
    for (int i = 0; i <= 180; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(heartX - radius / 2 + cos(angle) * radius, heartY + sin(angle) * radius);
    }
    glEnd();
    // Right semi-circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(heartX + radius / 2+5, heartY); // Center of the right circle
    for (int i = 0; i <= 180; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(heartX + radius / 2 + cos(angle) * radius, heartY + sin(angle) * radius);
    }
    glEnd();
    // Bottom triangle
    glBegin(GL_TRIANGLES);
    glVertex2f(heartX - radius-4, heartY); // Left point of the triangle
    glVertex2f(heartX + radius+4, heartY); // Right point of the triangle
    glVertex2f(heartX, heartY - radius * 1.5f); // Bottom point of the triangle
    glEnd();
}

//Re: 封面
float coverTime = 0;
void drawCover(){
    glBegin(GL_TRIANGLES);
    glColor4ub(223,205,186,150);
    glVertex2f(0,600);
    glVertex2f(1000,600);
    glVertex2f(500,200+coverTime);
    glEnd();
    // Enjoy the journey ahead 108 56 1
    glColor4f(0.42f, 0.22f, 0.01f,std::max(0.0,1.0-coverTime/600.0));
    selectFont(35, ANSI_CHARSET, "Lucida Handwriting");
    glRasterPos2f(318, 375);
    drawString("EEnjoy the Journey Ahead");

    glBegin(GL_QUADS);
    glColor3ub(223,205,186);
    glVertex2f(0,600-coverTime);
    glVertex2f(500,200-coverTime);
    glVertex2f(500,-coverTime);
    glVertex2f(0,-coverTime);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(223,205,186);
    glVertex2f(500,200-coverTime);
    glVertex2f(500,-coverTime);
    glVertex2f(1000,-coverTime);
    glVertex2f(1000,600-coverTime);
    glEnd();
    glColor3ub(44,44,44);
    renderBitmapString(420,160-coverTime,GLUT_BITMAP_HELVETICA_18,"Press [H] for HELP");
    renderBitmapString(370,135-coverTime,GLUT_BITMAP_HELVETICA_18,"[click] to Open the Birthday Card");

    glColor3ub(44,44,85);
    selectFont(35, ANSI_CHARSET, "Lucida Handwriting");
    glRasterPos2f(0,10-coverTime);
    drawString("From your BEST Friend");
    selectFont(35, ANSI_CHARSET, "Lucida Handwriting");
    glRasterPos2f(820,10-coverTime);
    drawString("Best Wishes");
}

void updateCover(){
    if (startedFlag){
        if (coverTime<600){
            coverTime+=1.6f;
        } else coverTime=600;
    }
}


//* 游戏逻辑
// 更新小人的位置
void updatePosition() {
    // 处理左右移动
    if (moveLeft) {
        characterX -= moveSpeed;
    }
    if (moveRight) {
        characterX += moveSpeed;
    }
    // 处理跳跃
    if (isJumping) {
        characterY += velocityY; // 更新垂直位置
        velocityY -= gravity; // 应用重力
    }
    // 检查是否接触到地面
    if (characterY <= getFloor(characterX) || characterY <= getFloor(characterX + 14 * pixelSize)) {
        characterY = std::max(getFloor(characterX),getFloor(characterX+14*pixelSize)); // 重置到地面高度
        isJumping = false; // 停止跳跃
        velocityY = 0; // 重置垂直速度
    } else if (!isJumping) {
        // 如果不在跳跃状态且不在地面，应用重力
        characterY += velocityY; // 更新垂直位置
        velocityY -= gravity; // 应用重力
    }
    // 确保小人不超界
    if(characterX<0){
        characterX = 0;
    }
    if (characterX+ 14 * pixelSize>1000){
        characterX = 1000 -14 * pixelSize;
    }
    // 死亡后回家
    if(characterY<25){
        characterX = 100;
        characterY = 50;
        setFlag(restartFlag);
    }
}

void checkGo(){
    if (characterX>540){
        if (characterY == getFloor(characterX+ 14 * pixelSize)
            && characterY!= getFloor(characterX-moveSpeed)){
            moveLeft = false; // 向左移动
        }
    }
    if (characterX<300){
        if (characterY == getFloor(characterX)
            && characterY!= getFloor(characterX+ 14 * pixelSize+moveSpeed)){
            moveRight = false; // 向右移动
        }
    }
}

// 键盘按下事件处理函数
void keyPress(unsigned char key, int x, int y) {
    if (key == 'a'|| key == 'A') {
        if (characterX>500){
            if (!(characterY == getFloor(characterX+ 14 * pixelSize)
                  && characterY!= getFloor(characterX-moveSpeed))){
                moveLeft = true; // 向左移动
            }
        } else moveLeft = true;
    }
    if (key == 'd'|| key == 'D') {
        if (characterX<400){
            if (!(characterY == getFloor(characterX)
                  && characterY!= getFloor(characterX+ 14 * pixelSize+moveSpeed))){
                moveRight = true; // 向右移动
            }
        } else moveRight = true;
    }
    if ((key == 'w'|| key == 'W') && !isJumping) { // 跳跃
        isJumping = true; // 开始跳跃
        velocityY = jumpSpeed; // 设置跳跃速度
    }
    if(key == 'h'|| key == 'H'){
        setFlag(showInfoFlag);
    }
    if (key == 'q'|| key == 'Q') {
        exit(0);
    }
    if ((key == 'e'|| key == 'E')&& characterX>900){
        triggerShake();
        gotCakeFlag = TRUE;
    }
}

// 键盘松开事件处理函数
void keyRelease(unsigned char key, int x, int y) {
    if (key == 'a'|| key == 'A') {
        moveLeft = false; // 停止向左移动
    }
    if (key == 'd'|| key == 'D') {
        moveRight = false; // 停止向右移动
    }
}

void mouseClick(int button, int state, int x, int y) {
    // Check if the left mouse button was clicked and released
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        startedFlag = TRUE; // Set the flag to false on click
    }
    if (gotCakeFlag){
        spawnBalloonClick(x, 600-y);
    }
}

//* 渲染函数
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // 清屏
    checkGo();
    checkFlag(restartFlag);
    checkFlag(showInfoFlag);
    shake();
    drawSky();                    //绘制天空
    if (characterX>650){
        for (auto star : stars) {
            updateStars();
            drawStar(star); // 绘制星星
        }
    }
    drawFullMoon(200.0f, 600+0.35*(700-characterX), 60.0f);
    for (const auto& cloud : clouds) {
        updateClouds();
        drawCloud(cloud); // 绘制每个云
    }
    // 绘制背景城市
    drawBuildings(0-0.05*characterX,70-0.1*characterY);
    drawBuildings(400-0.05*characterX,70-0.1*characterY);
    drawBuildings(800-0.05*characterX,70-0.1*characterY);
    drawCB(550-0.25*characterX,-120-0.1*characterY,2.0); //绘制cb
    renderPlatforms();            // 绘制楼梯
    renderSpikes();               // 绘制地刺
    drawGroundWithNoise();        // 绘制地面

    updateCakePosition();
    lissajousCake(675, cakeY); // 绘制蛋糕

    if (!gotCakeFlag){
        drawEnvelope(910, 60);  // 绘制信封
    }
    renderPixelCharacter();       // 绘制包含透明像素的小人
    if (gotCakeFlag) {
        if (timestep++ %50 == 0){
            spawnBalloon(); // 绘制气球
            timestep = timestep % 50;
        }
        renderBalloons();
    }
    updateBalloons();

    if (gotCakeFlag){
        updateText1();
        drawtext1();            // 绘制text1
    }

    if (restartFlag.value){
        glBegin(GL_QUADS);
        glColor4ub(0, 0, 0, 200); // 黑色，50%透明度
        glVertex2f(290, 425);
        glVertex2f(660, 425);
        glVertex2f(660, 390);
        glVertex2f(290, 390);
        glEnd();
        glColor3ub(255,178,132);
        renderBitmapString(300,400,GLUT_BITMAP_TIMES_ROMAN_24,"Try Again Dear Birthday Celebrant!");
    }
    updateCover();
    drawCover();         // 绘制封面
    if(showInfoFlag.value){       // 绘制Help窗口
        drawHelpWindow();
    }
    glFlush();                    // 刷新绘图命令
}

// 更新位置和渲染的回调
void timer(int value) {
    updatePosition();       // 更新位置
    glutPostRedisplay();    // 刷新窗口
    glutTimerFunc(16, timer, 0); // 每16ms调用一次（大约60fps）
}

// 初始化OpenGL设置
void initOpenGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 设置背景色为白色
    glEnable(GL_BLEND);                   // 启用混合
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // 设置混合函数
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight); // 使用正交投影
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // 初始化FreeGLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Birthday Card ~ Mario adventure | Presented by:2257475 Ruiyang.Wu");

    initOpenGL(); // 初始化OpenGL设置
    glutDisplayFunc(display); // 设置渲染函数
    initStars();
    initClouds();
    glutMouseFunc(mouseClick); // Register the mouse click callback
    glutKeyboardFunc(keyPress); // 设置键盘按下事件
    glutKeyboardUpFunc(keyRelease); // 设置键盘松开事件
    glutTimerFunc(8, timer, 0); // 开启定时器
    glEnable(GL_MULTISAMPLE); // MSAA

    glutMainLoop(); // 进入事件循环
    return 0;
}
