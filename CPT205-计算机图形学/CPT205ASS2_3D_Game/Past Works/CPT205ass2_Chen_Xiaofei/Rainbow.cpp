#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <array>
#include <algorithm>

// ==================== 全局变量定义 ====================

// 图片数据
static GLint imageWidth;
static GLint imageHeight;
static GLint pixelLength;
static GLubyte* pixelData = nullptr;

// 游戏参数
const float TRACK_WIDTH = 6.0f;
const int GATES_PER_ROW = 3;
const float GATE_WIDTH = TRACK_WIDTH / GATES_PER_ROW;
const float PLAYER_STEP = GATE_WIDTH / 8.0f;
const std::vector<int> ADD_VALUES = {0, 5, 10, 20};
const std::vector<int> SUB_VALUES = {0, 10, 20, 50};
const std::vector<int> MUL_VALUES = {1, 2, 5, 10};
const std::vector<int> DIV_VALUES = {1, 2, 5, 10};

float leftBoundary = -3.0f;
float rightBoundary = 3.0f;
int playerHP = 100;
float playerPosX = 0.0f;
float playerSpeed = 0.05f;

// 跳跃相关
bool isJumping = false;
float jumpHeight = 0.0f;
float maxJumpHeight = 2.0f;
float jumpSpeed = 0.05f;
bool canJump = true;

// Buff状态
bool isBuffActive = false;
int currentBuffType = -1;
int buffTimer = 0;

// 保存原始属性以便恢复
float originalPlayerSpeed = 0.05f;
float originalEnemySpeed = 0.03f;
float originalPlayerBulletSpeed = 0.2f;

// 游戏状态
bool isGameOver = false;
bool isPaused = false;
bool isVictory = false;

// 敌人颜色
const std::vector<std::array<float, 3>> enemyColors = {
        {1.0f, 0.0f, 0.0f},    // 红色
        {1.0f, 0.5f, 0.0f},    // 橙色
        {1.0f, 1.0f, 0.0f},    // 黄色
        {0.0f, 1.0f, 0.0f},    // 绿色
        {0.0f, 0.0f, 1.0f},    // 蓝色
        {0.29f, 0.0f, 0.51f},  // 靛色
        {0.56f, 0.0f, 1.0f}    // 紫色
};

// 敌人生成控制
int currentEnemyIndex = 0;
int rowsPassed = 0;
int nextEnemySpawnRow = 10;

// ==================== 结构体定义 ====================

// 门
struct Gate {
    float posX;
    float posZ;
    char operation;
    int value;
    bool isFlashing = false;
    int flashTimer = 0;
    bool isActive = true;
};

// 洞
struct Hole {
    float posX;
    float posZ;
    int type; // 0: 红色, 1: 橙色, 2: 黄色, 3: 绿色, 4: 蓝色, 5: 靛色, 6: 紫色
    bool isFlashing = false;
    int flashTimer = 0;
    bool isActive = true;
};

// 子弹
struct Bullet {
    float posX, posY, posZ;
    float speed;
    float color[3];
    bool fromPlayer;

    bool operator==(const Bullet& other) const {
        return posX == other.posX && posY == other.posY && posZ == other.posZ && speed == other.speed && fromPlayer == other.fromPlayer;
    }
};

// 敌人
struct Enemy {
    float posX = 0.0f;
    float posY = 0.5f;
    float posZ = -15.0f;
    float speed = 0.03f;
    float size = 0.5f;
    float color[3] = {1.0f, 0.0f, 0.0f};
    bool isActive = false;
    int HP = 5000;
    std::vector<Bullet> bullets;
    float fireCooldown = 2.0f;

    float targetPosX = 0.0f;
    float pauseTimer = 0.0f; // 暂停计时器
};

std::vector<Gate> gates;
std::vector<Hole> holes;
std::vector<Bullet> playerBullets;
std::vector<Bullet> enemyBullets;
std::vector<Enemy> enemies;

// ==================== 功能函数实现 ====================

// 加载 BMP 图片函数
void loadBMP(const char* filename) {
    FILE* pFile = nullptr;
    // 以二进制模式打开 BMP 文件
    fopen_s(&pFile, filename, "rb");
    if (pFile == nullptr) {
        std::cerr << "Unable to open the image file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    // 跳过 BMP 文件头前 18 个字节，读取宽度和高度
    fseek(pFile, 18, SEEK_SET);
    fread(&imageWidth, sizeof(imageWidth), 1, pFile);
    fread(&imageHeight, sizeof(imageHeight), 1, pFile);

    // 计算每行像素的字节长度（BMP 每行必须是 4 的倍数）
    pixelLength = imageWidth * 3;
    while (pixelLength % 4 != 0) {
        pixelLength++;
    }
    pixelLength *= imageHeight;

    // 分配内存并读取像素数据
    pixelData = (GLubyte*)malloc(pixelLength);
    if (pixelData == nullptr) {
        std::cerr << "Memory allocation failed!" << std::endl;
        fclose(pFile);
        exit(EXIT_FAILURE);
    }

    // BMP 文件的像素数据从第 54 字节开始
    fseek(pFile, 54, SEEK_SET);
    fread(pixelData, pixelLength, 1, pFile);

    fclose(pFile);
}

// 加权随机数生成
int weightedRandom(const std::vector<int>& values, const std::vector<int>& weights) {
    int totalWeight = 0;
    for (int weight : weights) {
        totalWeight += weight;
    }

    int randomValue = rand() % totalWeight;
    int cumulativeWeight = 0;

    for (size_t i = 0; i < weights.size(); ++i) {
        cumulativeWeight += weights[i];
        if (randomValue < cumulativeWeight) {
            return values[i];
        }
    }
    return values[0];
}

// 初始化门
void initGates() {
    srand(static_cast<unsigned int>(time(0)));

    std::vector<int> addWeights = {29,60,10,1};
    std::vector<int> subWeights = {29,60,10,1};
    std::vector<int> mulWeights = {29,60,10,1};
    std::vector<int> divWeights = {29,60,10,1};

    for (int i = 0; i < 5; ++i) {
        float rowZ = static_cast<float>(-20 * (i + 1));
        for (int j = 0; j < GATES_PER_ROW; ++j) {
            char operation;
            int value;

            int opRand = rand() % 100;
            if (opRand < 60) {
                operation = '+';
                value = weightedRandom(ADD_VALUES, addWeights);
            }
            else if (opRand < 75) {
                operation = '-';
                value = weightedRandom(SUB_VALUES, subWeights);
            }
            else if (opRand < 95) {
                operation = '*';
                value = weightedRandom(MUL_VALUES, mulWeights);
            }
            else {
                operation = '/';
                value = weightedRandom(DIV_VALUES, divWeights);
            }

            float posX = -TRACK_WIDTH / 2 + GATE_WIDTH * j + GATE_WIDTH / 2;
            Gate gate = {
                    posX,
                    rowZ,
                    operation,
                    value
            };
            gates.push_back(gate);
        }
    }
}

// 初始化敌人
void initEnemies() {
    for (int i = 0; i < 7; i++) {
        Enemy enemy;
        enemy.posX = -TRACK_WIDTH / 2 + (rand() % static_cast<int>(TRACK_WIDTH));
        enemy.posZ = -15.0f;
        enemy.size = 0.5f;
        enemy.speed = originalEnemySpeed;
        enemy.color[0] = enemyColors[i][0];
        enemy.color[1] = enemyColors[i][1];
        enemy.color[2] = enemyColors[i][2];
        enemy.isActive = false;

        // 设置初始目标位置为当前位置
        enemy.targetPosX = enemy.posX;

        enemies.push_back(enemy);
    }
}

// 重新激活门
void resetGates() {
    for (auto &gate : gates) {
        gate.isActive = true;
    }
}

// 生成洞
void generateHole() {
    if (isBuffActive) return; // 如果当前有增益，暂不生成新洞

    Hole hole;
    // 随机选择位置：左、中、右
    int position = rand() % 3;
    if (position == 0) {
        hole.posX = leftBoundary + GATE_WIDTH / 2;
    }
    else if (position == 1) {
        hole.posX = 0.0f;
    }
    else {
        hole.posX = rightBoundary - GATE_WIDTH / 2;
    }

    // 设置posZ在玩家位置的远处
    hole.posZ = -50.0f;

    // 随机选择洞的类型（0-6）
    hole.type = rand() % 7;

    holes.push_back(hole);
}

// 渲染文本
void renderText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// 渲染3D文本
void renderText3D(float x, float y, float z, const char* text, const float color[3]) {
    glPushMatrix();
    glColor3f(color[0], color[1], color[2]);
    glRasterPos3f(x, y, z);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
    glPopMatrix();
}

// 渲染“游戏结束”文本
void renderGameOverText() {
    float white[] = {1.0f, 1.0f, 1.0f};
    glColor3fv(white);
    renderText(300, 300, "GAME OVER");
}

// 渲染“胜利”文本
void renderVictoryText() {
    float white[] = {1.0f, 1.0f, 1.0f};
    glColor3fv(white);
    renderText(300, 300, "YOU WIN!");
}

// 渲染跑道
void renderTrack() {
    glColor3f(0.6f, 0.3f, 0.1f); // 棕色跑道
    for (int i = 0; i < 20; ++i) {
        glPushMatrix();
        glTranslatef(0.0f, -1.0f, -10.0f * i);
        glBegin(GL_QUADS);
        glVertex3f(-4.0f, 0.0f, 0.0f);
        glVertex3f(4.0f, 0.0f, 0.0f);
        glVertex3f(4.0f, 0.0f, -10.0f);
        glVertex3f(-4.0f, 0.0f, -10.0f);
        glEnd();
        glPopMatrix();
    }
}

// 渲染门
void renderGate(Gate gate) {
    // 仅当门活跃或者正在闪烁时渲染
    if (!gate.isActive && !gate.isFlashing) return;

    glPushMatrix();
    glTranslatef(gate.posX, 0.0f, gate.posZ);

    float color[4] = {0.0f, 1.0f, 0.0f, 0.5f};
    if (gate.isFlashing) {
        float intensity = fabs(sin(gate.flashTimer * 0.1f));
        color[0] = intensity;
        color[1] = 1.0f;
        color[2] = intensity;
    }
    else {
        if (gate.operation == '+') { color[0] = 0.0f; color[1] = 1.0f; color[2] = 1.0f; }
        if (gate.operation == '-') { color[0] = 1.0f; color[1] = 0.0f; color[2] = 1.0f; }
        if (gate.operation == '*') { color[0] = 1.0f; color[1] = 0.843f; color[2] = 0.0f; }
        if (gate.operation == '/') { color[0] = 0.66f; color[1] = 0.66f; color[2] = 0.66f; }
    }

    // 绘制门主体
    glColor4f(color[0], color[1], color[2], color[3]);
    glBegin(GL_QUADS);
    glVertex3f(-GATE_WIDTH / 2, 0.0f, 0.0f);
    glVertex3f(GATE_WIDTH / 2, 0.0f, 0.0f);
    glVertex3f(GATE_WIDTH / 2, 1.5f, 0.0f);
    glVertex3f(-GATE_WIDTH / 2, 1.5f, 0.0f);
    glEnd();

    // 绘制边框
    glColor3f(0.545f, 0.271f, 0.075f);
    glBegin(GL_QUADS);
    // 左边框
    glVertex3f(-GATE_WIDTH / 2, 0.0f, 0.01f);
    glVertex3f(-GATE_WIDTH / 2 + 0.05f, 0.0f, 0.01f);
    glVertex3f(-GATE_WIDTH / 2 + 0.05f, 1.5f, 0.01f);
    glVertex3f(-GATE_WIDTH / 2, 1.5f, 0.01f);
    // 右边框
    glVertex3f(GATE_WIDTH / 2 - 0.05f, 0.0f, 0.01f);
    glVertex3f(GATE_WIDTH / 2, 0.0f, 0.01f);
    glVertex3f(GATE_WIDTH / 2, 1.5f, 0.01f);
    glVertex3f(GATE_WIDTH / 2 - 0.05f, 1.5f, 0.01f);
    glEnd();

    glPopMatrix();

    // 绘制门的数值
    char buffer[10];
    sprintf(buffer, "%c%d", gate.operation, gate.value);
    renderText3D(gate.posX, 1.7f, gate.posZ, buffer, color);
}

// 渲染洞
void renderHoles() {
    for (const auto& hole : holes) {
        if (!hole.isActive && !hole.isFlashing) continue;

        glPushMatrix();
        glTranslatef(hole.posX, 0.0f, hole.posZ);

        // 根据类型设置颜色
        float color[4];
        switch (hole.type) {
            case 0: // 红色
                color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.0f; break;
            case 1: // 橙色
                color[0] = 1.0f; color[1] = 0.5f; color[2] = 0.0f; break;
            case 2: // 黄色
                color[0] = 1.0f; color[1] = 1.0f; color[2] = 0.0f; break;
            case 3: // 绿色
                color[0] = 0.0f; color[1] = 1.0f; color[2] = 0.0f; break;
            case 4: // 蓝色
                color[0] = 0.0f; color[1] = 0.0f; color[2] = 1.0f; break;
            case 5: // 靛色
                color[0] = 0.29f; color[1] = 0.0f; color[2] = 0.51f; break;
            case 6: // 紫色
                color[0] = 0.56f; color[1] = 0.0f; color[2] = 1.0f; break;
        }

        // 闪烁效果
        if (hole.isFlashing) {
            float intensity = fabs(sin(hole.flashTimer * 0.1f));
            glColor4f(color[0] * intensity, color[1] * intensity, color[2] * intensity, 0.5f);
        }
        else {
            glColor4f(color[0], color[1], color[2], 0.5f);
        }

        // 绘制洞主体
        glBegin(GL_QUADS);
        glVertex3f(-GATE_WIDTH / 2, 0.0f, 0.0f);
        glVertex3f(GATE_WIDTH / 2, 0.0f, 0.0f);
        glVertex3f(GATE_WIDTH / 2, 1.5f, 0.0f);
        glVertex3f(-GATE_WIDTH / 2, 1.5f, 0.0f);
        glEnd();

        // 绘制边框
        glColor3f(0.545f, 0.271f, 0.075f);
        glBegin(GL_QUADS);
        // 左边框
        glVertex3f(-GATE_WIDTH / 2, 0.0f, 0.01f);
        glVertex3f(-GATE_WIDTH / 2 + 0.05f, 0.0f, 0.01f);
        glVertex3f(-GATE_WIDTH / 2 + 0.05f, 1.5f, 0.01f);
        glVertex3f(-GATE_WIDTH / 2, 1.5f, 0.01f);
        // 右边框
        glVertex3f(GATE_WIDTH / 2 - 0.05f, 0.0f, 0.01f);
        glVertex3f(GATE_WIDTH / 2, 0.0f, 0.01f);
        glVertex3f(GATE_WIDTH / 2, 1.5f, 0.01f);
        glVertex3f(GATE_WIDTH / 2 - 0.05f, 1.5f, 0.01f);
        glEnd();

        glPopMatrix();
    }
}

// 渲染子弹
void renderBullets() {
    // 渲染玩家子弹
    for (const Bullet& bullet : playerBullets) {
        glPushMatrix();
        glTranslatef(bullet.posX, bullet.posY, bullet.posZ);
        glColor3f(bullet.color[0], bullet.color[1], bullet.color[2]);
        glutSolidSphere(0.1f, 16, 16);
        glPopMatrix();
    }

    // 渲染敌人子弹
    for (const Bullet& bullet : enemyBullets) {
        glPushMatrix();
        glTranslatef(bullet.posX, bullet.posY, bullet.posZ);
        glColor3f(bullet.color[0], bullet.color[1], bullet.color[2]);
        glutSolidSphere(0.1f, 16, 16);
        glPopMatrix();
    }
}

// 渲染玩家
void renderPlayer() {
    if (isBuffActive && currentBuffType == 5) {
        // 玩家隐身，不渲染
        return;
    }
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // 白色玩家
    glTranslatef(playerPosX, jumpHeight, -5.0f);
    glutSolidSphere(0.3f, 16, 16);
    glPopMatrix();
}

// 渲染敌人
void renderEnemies() {
    for (const auto &enemy : enemies) {
        if (enemy.isActive) {
            glPushMatrix();
            glTranslatef(enemy.posX, 0.5f, enemy.posZ);
            glColor3f(enemy.color[0], enemy.color[1], enemy.color[2]);
            glutSolidSphere(enemy.size, 20, 20);
            glPopMatrix();
        }
    }
}

// 更新跳跃逻辑
void updateJump() {
    if (isJumping) {
        if (jumpHeight < maxJumpHeight) {
            jumpHeight += jumpSpeed;
        }
        else {
            isJumping = false;
        }
    }
    else {
        if (jumpHeight > 0.0f) {
            jumpHeight -= jumpSpeed;
        }
        else {
            jumpHeight = 0.0f;
            canJump = true;
        }
    }
}

// 生成敌人子弹
void generateEnemyBullet(Enemy& enemy) {
    if (isBuffActive && currentBuffType == 5) { // 靛色增益：敌人不发射子弹
        return;
    }

    Bullet bullet;
    bullet.posX = enemy.posX;
    bullet.posY = enemy.posY;
    bullet.posZ = enemy.posZ;
    bullet.speed = originalPlayerBulletSpeed;
    bullet.color[0] = enemy.color[0];
    bullet.color[1] = enemy.color[1];
    bullet.color[2] = enemy.color[2];
    bullet.fromPlayer = false;
    enemyBullets.push_back(bullet);
}

// 更新敌人子弹
void updateEnemyBullets() {
    for (auto it = enemyBullets.begin(); it != enemyBullets.end(); ) {
        it->posZ += it->speed;
        if (it->posZ > 0.0f) {
            it = enemyBullets.erase(it);
        }
        else {
            ++it;
        }
    }
}

// 更新玩家子弹
void updatePlayerBullets() {
    for (auto it = playerBullets.begin(); it != playerBullets.end(); ) {
        it->posZ -= it->speed;
        if (it->posZ < -20.0f) {
            it = playerBullets.erase(it);
        }
        else {
            ++it;
        }
    }
}

// 应用增益效果
void applyBuff(int type) {
    currentBuffType = type;
    buffTimer = 300;

    switch (type) {
        case 0: // 红色：增加玩家子弹攻击力
            // 增加子弹攻击力的逻辑
            break;
        case 1: // 橙色：玩家横向移动速度变为2倍
            playerSpeed *= 2.0f;
            break;
        case 2: // 黄色：玩家受到敌人子弹伤害减半
            // 在碰撞检测中应用
            break;
        case 3: // 绿色：玩家持续增加自身HP，每帧加1
            // 在更新游戏逻辑时处理
            break;
        case 4: // 蓝色：敌人横向移动速度减半
            for (auto &enemy : enemies) {
                if (enemy.isActive) {
                    enemy.speed *= 0.5f;
                }
            }
            break;
        case 5: // 靛色：玩家暂时隐身，敌人不发射子弹
            // 隐身处理
            break;
        case 6: // 紫色：玩家子弹散射
            // 在发射子弹时调整逻辑
            break;
    }
}

// 取消增益效果
void cancelBuff() {
    switch (currentBuffType) {
        case 0: // 红色
            // 恢复子弹攻击力
            break;
        case 1: // 橙色
            playerSpeed = originalPlayerSpeed;
            break;
        case 2: // 黄色
            // 恢复伤害逻辑
            break;
        case 3: // 绿色
            // 停止增加HP
            break;
        case 4: // 蓝色
            for (auto &enemy : enemies) {
                if (enemy.isActive) {
                    enemy.speed = originalEnemySpeed;
                }
            }
            break;
        case 5: // 靛色
            // 恢复可见状态，并允许敌人发射子弹
            break;
        case 6: // 紫色
            // 恢复子弹发射逻辑
            break;
    }
    isBuffActive = false;
    currentBuffType = -1;
}

// 管理增益效果
void manageBuff() {
    if (isBuffActive) {
        buffTimer--;
        if (buffTimer <= 0) {
            cancelBuff();
        }
        else {
            // 持续应用绿色增益：每帧增加玩家HP
            if (currentBuffType == 3) {
                playerHP += 1;
            }
        }
    }
}

// 更新敌人
void updateEnemies(float deltaTime) {
    for (auto& enemy : enemies) {
        if (enemy.isActive) {
            if (enemy.pauseTimer > 0.0f) {
                // 如果敌人正在暂停，递减暂停计时器
                enemy.pauseTimer -= deltaTime;
                if (enemy.pauseTimer <= 0.0f) {
                    enemy.pauseTimer = 0.0f;
                }
                continue; // 不移动敌人
            }

            // 计算敌人与目标位置的差距
            float distance = enemy.targetPosX - enemy.posX;

            // 如果敌人几乎到达目标位置
            if (fabs(distance) < 0.05f) {
                // 选择一个新的随机目标位置
                enemy.targetPosX = -TRACK_WIDTH / 2 + static_cast<float>(rand()) / RAND_MAX * TRACK_WIDTH;

                // 设置暂停时间
                enemy.pauseTimer = 0.5f;
            } else {
                // 计算移动方向
                float direction = (distance > 0) ? 1.0f : -1.0f;

                // 计算每帧的移动距离
                float moveDistance = enemy.speed * deltaTime * direction;

                // 防止敌人超出边界
                if ((direction > 0 && (enemy.posX + moveDistance) > rightBoundary) ||
                    (direction < 0 && (enemy.posX + moveDistance) < leftBoundary)) {
                    enemy.posX = (direction > 0) ? rightBoundary : leftBoundary;
                }
                else {
                    // 更新敌人位置
                    enemy.posX += moveDistance;
                }
            }
        }
    }
}

// 检查玩家子弹与敌人的碰撞
void checkPlayerBulletCollision() {
    for (size_t i = 0; i < playerBullets.size(); ) {
        Bullet& bullet = playerBullets[i];
        bool bulletErased = false;

        for (auto &enemy : enemies) {
            if (enemy.isActive) {
                if (fabs(bullet.posX - enemy.posX) < (GATE_WIDTH / 2) && fabs(bullet.posZ - enemy.posZ) < 0.5f) {
                    // 碰撞
                    if (isBuffActive && currentBuffType == 0) { // 红色增益
                        enemy.HP -= 200;
                    }
                    else {
                        enemy.HP -= 100;
                    }
                    playerBullets.erase(playerBullets.begin() + i);
                    bulletErased = true;
                    if (enemy.HP <= 0) {
                        enemy.isActive = false;
                        resetGates();
                        currentEnemyIndex++;
                        if (currentEnemyIndex >= enemies.size()) {
                            isVictory = true;
                            isPaused = true;
                        }
                        else {
                            nextEnemySpawnRow += 20;
                        }
                    }
                    break;
                }
            }
        }

        if (!bulletErased) {
            ++i;
        }
    }
}

// 检查敌人子弹与玩家的碰撞
void checkBulletCollision() {
    for (auto it = enemyBullets.begin(); it != enemyBullets.end(); ) {
        // 检查子弹是否与玩家发生碰撞，同时检查玩家的跳跃高度
        if (fabs(playerPosX - it->posX) < 0.3f && fabs(it->posZ - (-5.0f + jumpHeight)) < 0.2f) {
            // 如果玩家跳跃的高度在子弹的范围内
            if (jumpHeight <= 1.5f) {
                // 子弹碰撞到玩家
                if (isBuffActive && currentBuffType == 2) { // 黄色增益
                    playerHP -= 50;
                }
                else {
                    playerHP -= 100;
                }
                it = enemyBullets.erase(it);
                if (playerHP <= 0) {
                    isGameOver = true;
                    isPaused = true;
                    playerSpeed = 0.0f;
                }
            }
            else {
                // 玩家跳得比较高，子弹未击中
                it = enemyBullets.erase(it);
            }
        }
        else {
            ++it;
        }
    }
}

// 更新游戏逻辑
void updateGame(int value) {
    if (!isGameOver && !isVictory) {

        updateJump();

        // 更新门位置并检测是否需要生成敌人
        for (size_t i = 0; i < gates.size(); i++) {
            Gate& gate = gates[i];
            gate.posZ += playerSpeed;

            if (gate.posZ > 1.0f) {
                gate.posZ -= 100.0f;
                gate.isActive = true;

                if (i % GATES_PER_ROW == 0) { // 每排门的第一个门
                    rowsPassed++;

                    // 检查是否需要生成敌人
                    if (rowsPassed >= nextEnemySpawnRow && currentEnemyIndex < enemies.size()) {
                        enemies[currentEnemyIndex].isActive = true;
                        // 禁用所有门
                        for (auto &g : gates) {
                            g.isActive = false;
                        }
                        // 生成一个洞
                        generateHole();
                    }
                }
            }

            if (gate.isActive && fabs(playerPosX - gate.posX) < GATE_WIDTH / 2) {
                if (gate.posZ > -5.0f && gate.posZ < -4.5f) {
                    if (jumpHeight > 1.5f) {
                        continue;
                    }

                    if (gate.operation == '+') playerHP += gate.value;
                    if (gate.operation == '-') playerHP -= gate.value;
                    if (gate.operation == '*') playerHP *= gate.value;
                    if (gate.operation == '/') playerHP = gate.value != 0 ? playerHP / gate.value : playerHP;

                    gate.isActive = false;
                    gate.isFlashing = true;
                    gate.flashTimer = 30;
                }
            }

            if (gate.isFlashing) {
                gate.flashTimer--;
                if (gate.flashTimer <= 0) {
                    gate.isFlashing = false;
                }
            }
        }

        // 更新洞位置
        for (size_t i = 0; i < holes.size(); ) {
            Hole& hole = holes[i];
            hole.posZ += playerSpeed;

            if (hole.posZ > 1.0f) { // 超出视野范围
                holes.erase(holes.begin() + i);
            }
            else {
                // 处理闪烁计时
                if (hole.isFlashing) {
                    hole.flashTimer--;
                    if (hole.flashTimer <= 0) {
                        hole.isFlashing = false;
                    }
                }

                // 检查是否与玩家碰撞
                if (hole.isActive && fabs(playerPosX - hole.posX) < GATE_WIDTH && fabs(hole.posZ - (-5.0f)) < 1.0f) {
                    // 触发增益
                    applyBuff(hole.type);
                    hole.isActive = false;
                    hole.isFlashing = true;
                    hole.flashTimer = 30;
                    isBuffActive = true;
                    buffTimer = 300;
                }

                ++i;
            }
        }

        // 更新敌人
        float deltaTime = 0.016f;
        updateEnemies(deltaTime);

        // 更新子弹
        updatePlayerBullets();
        updateEnemyBullets();

        // 检查碰撞
        checkPlayerBulletCollision();
        checkBulletCollision();

        // 管理增益效果
        manageBuff();

        // 敌人发射子弹
        for (auto &enemy : enemies) {
            if (enemy.isActive) {
                enemy.fireCooldown -= deltaTime;
                if (enemy.fireCooldown <= 0.0f) {
                    generateEnemyBullet(enemy);
                    enemy.fireCooldown = 2.0f;
                }
            }
        }

        // 判断游戏是否结束
        if (playerHP <= 0 && !isPaused) {
            isGameOver = true;
            isPaused = true;
            playerSpeed = 0.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateGame, 0);
}

// 重置游戏
void resetGame() {
    playerPosX = 0.0f;
    playerHP = 100;
    playerSpeed = originalPlayerSpeed;
    isGameOver = false;
    isPaused = false;
    isVictory = false;

    gates.clear();
    initGates();

    holes.clear();
    playerBullets.clear();
    enemyBullets.clear();

    for (auto &enemy : enemies) {
        enemy.isActive = false;
        enemy.HP = 5000;
        enemy.bullets.clear();
        enemy.fireCooldown = 2.0f;
        enemy.speed = originalEnemySpeed;
    }

    currentEnemyIndex = 0;
    rowsPassed = 0;
    nextEnemySpawnRow = 10;
    isBuffActive = false;
    currentBuffType = -1;
    buffTimer = 0;

    glutPostRedisplay();
}

// 键盘输入
void handleKeypress(unsigned char key, int x, int y) {
    if (key == 'a' || key == 'A') {
        if (playerPosX - PLAYER_STEP >= leftBoundary) {
            playerPosX -= PLAYER_STEP;
        }
    }

    if (key == 'd' || key == 'D') {
        if (playerPosX + PLAYER_STEP <= rightBoundary) {
            playerPosX += PLAYER_STEP;
        }
    }

    if (key == ' ' && canJump) {
        isJumping = true;
        canJump = false;
    }

    if (key == 'r' || key == 'R') {
        resetGame();
    }

    glutPostRedisplay();
}

// 鼠标点击
void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !isPaused && !isVictory) {
        if (isBuffActive && currentBuffType == 6) { // 紫色增益：散射射击
            // 三列子弹，x轴偏移
            float offsets[3] = { -0.3f,  0.0f,  0.3f };
            for (int i = 0; i < 3; i++) {
                Bullet bullet = { playerPosX + offsets[i], 0.0f, -5.0f, originalPlayerBulletSpeed, {1.0f, 1.0f, 1.0f}, true };
                playerBullets.push_back(bullet);
            }
        }
        else { // 普通单一射击
            Bullet bullet = { playerPosX, 0.0f, -5.0f, originalPlayerBulletSpeed, {1.0f, 1.0f, 1.0f}, true };
            playerBullets.push_back(bullet);
        }
    }
}

// 渲染场景
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 渲染背景图片
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // 获取当前窗口尺寸
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    gluOrtho2D(0, viewport[2], 0, viewport[3]);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // 禁用深度测试和深度写入，确保背景位于最底层
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    // 设置绘制位置为窗口左下角
    glRasterPos2i(0, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // 图像数据的对齐
    glDrawPixels(imageWidth, imageHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixelData);

    // 恢复深度测试和深度写入
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);


    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    // 继续渲染 3D 场景
    glLoadIdentity();
    gluLookAt(0.0f, 2.0f, 5.0f,  // 观察点位置
              0.0f, 0.0f, -5.0f, // 目标点位置
              0.0f, 1.0f, 0.0f); // 上方向

    // 渲染各种游戏元素
    renderTrack();
    for (const auto& gate : gates) {
        renderGate(gate);
    }
    renderEnemies();
    renderPlayer();
    renderBullets();
    renderHoles();

    // 渲染 HUD（界面元素）
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    char buffer[100];
    sprintf(buffer, "HP: %d", playerHP);
    renderText(10, 580, buffer);

    for (const auto &enemy : enemies) {
        if (enemy.isActive) {
            sprintf(buffer, "Enemy HP: %d", enemy.HP);
            renderText(10, 560, buffer);
            break;
        }
    }

    if (isGameOver) {
        renderGameOverText();
    }

    if (isVictory) {
        renderVictoryText();
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

// 初始化OpenGL
void initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 黑色背景

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// ==================== 主函数 ====================
int main(int argc, char** argv) {
    // 初始化随机数种子
    srand(static_cast<unsigned int>(time(0)));
    // 初始化 GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // 加载背景图片
    loadBMP("Rainbow.bmp");

    // 初始化窗口
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rainbow");

    // 初始化 OpenGL 和游戏实体
    initOpenGL();
    initGates();
    initEnemies();

    // 注册回调函数
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(handleMouse);
    glutTimerFunc(16, updateGame, 0);

    // 进入主循环
    glutMainLoop();

    // 程序结束前释放像素数据
    if (pixelData != nullptr) {
        free(pixelData);
        pixelData = nullptr;
    }

    return 0;
}