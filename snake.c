#include "snake.h"


Snake snake;                // 定义全局变量蛇
Food food;                  // 定义全局变量食物
Obstacle obstacles[OBSTACLE_COUNT]; // 障碍物数组
char now_Direction = RIGHT; // 定义全局变量当前方向
char direction = RIGHT;     // 定义全局变量用户输入的方向

void GotoXY(int x, int y) // 定义函数用于设置光标位置
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备的句柄
    COORD coord;                                   // 定义一个COORD结构体变量用于存储坐标
    coord.X = x;                                   // 设置X坐标
    coord.Y = y;                                   // 设置Y坐标
    SetConsoleCursorPosition(hOut, coord);         // 设置光标位置
}
void HideCursor() // 定义函数用于隐藏光标
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备的句柄
    CONSOLE_CURSOR_INFO cursorInfo = {1, 0};       // 定义一个CONSOLE_CURSOR_INFO结构体变量用于存储光标信息，设置光标大小为1，隐藏光标
    SetConsoleCursorInfo(hOut, &cursorInfo);       // 设置新的光标信息
}
int InitMenu() // 定义函数用于显示菜单并获取用户选择
{
    GotoXY(40, 12);                 // 设置光标位置
    printf("欢迎来到贪吃蛇游戏！"); // 显示菜单选项1
    GotoXY(43, 14);                 // 设置光标位置
    printf("1. 开始游戏");          // 显示菜单选项2
    GotoXY(43, 16);                 // 设置光标位置
    printf("2. 帮助");              // 显示菜单选项3
    GotoXY(43, 18);                 // 设置光标位置
    printf("3. 关于");              // 显示菜单选项4
    GotoXY(43, 20);                 // 设置光标位置
    printf("按任意键退出");       // 显示菜单选项5
    HideCursor();                   // 隐藏光标
    printf("请输入您的选择:");
    char choice = getch(); // 获取用户输入的选择
    int result = 0;
    switch (choice)
    {
    case '1':
        result = 1; // 用户选择开始游戏
        break;
    case '2':
        result = 2; // 用户选择帮助
        break;
    case '3':
        result = 3; // 用户选择关于
        break;
    default:
        break;
    }
    return result; // 返回用户选择的结果
}
void About() // 定义函数用于显示关于信息
{
    GotoXY(30, 12);
    printf("杭州电子科技大学 - 综合编程实践");
    GotoXY(43, 14);
    printf("贪吃蛇游戏");
    GotoXY(43, 16);
    printf("按任意键返回菜单");
    HideCursor();
    char choice = getch(); // 获取用户输入的选择
    system("cls");         // 清屏
}
void Helper() // 定义函数用于显示帮助信息
{
    GotoXY(40, 12);
    printf("游戏规则:");
    GotoXY(40, 14);
    printf("1. 使用WASD键控制蛇的移动");
    GotoXY(40, 16);
    printf("2. 吃食物使蛇变长，得分增加");
    GotoXY(40, 18);
    printf("3. 碰到墙、自己或障碍物会游戏结束");
    GotoXY(45, 20);
    printf("按任意键返回菜单");
    HideCursor();
    char choice = getch(); // 获取用户输入的选择
    system("cls");         // 清屏
}
void InitMap() // 定义函数用于绘制游戏地图
{
    // 生成地图上下边界
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        GotoXY(i, 0);
        printf("%c", MAP_CHAR);
        GotoXY(i, MAP_HEIGHT - 1);
        printf("%c", MAP_CHAR);
    }
    // 生成地图左右边界
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        GotoXY(0, i);
        printf("%c", MAP_CHAR);
        GotoXY(MAP_WIDTH - 1, i);
        printf("%c", MAP_CHAR);
    }


    // 显示初始得分
    GotoXY(50, 5);
    printf("得分：0");
}
void InitSnake() // 定义函数用于初始化蛇
{
    // 释放之前的内存（如果存在）
    FreeSnake();
    
    snake.length = INITIAL_SNAKE_LENGTH;
    snake.speed = 250;
    snake.pendingGrowth = 0;
    now_Direction = RIGHT;

    // 创建蛇头
    snake.head = (SnakeNode*)malloc(sizeof(SnakeNode));
    snake.head->x = MAP_WIDTH / 2 - 1;
    snake.head->y = MAP_HEIGHT / 2 - 1;
    snake.head->prev = NULL;
    snake.head->next = NULL;
    snake.tail = snake.head;

    GotoXY(snake.head->x, snake.head->y);
    printf("%c", SNAKE_HEAD_CHAR);

    // 创建初始蛇身
    for (int i = 1; i < snake.length; i++) {
        SnakeNode *newNode = (SnakeNode*)malloc(sizeof(SnakeNode));
        newNode->x = snake.tail->x - 1;
        newNode->y = snake.tail->y;
        
        newNode->prev = snake.tail;
        newNode->next = NULL;
        snake.tail->next = newNode;
        snake.tail = newNode;

        GotoXY(newNode->x, newNode->y);
        printf("%c", SNAKE_BODY_CHAR);
    }
}
void GenerateFood() // 定义函数用于生成食物
{
    int x, y;
    int valid = 0;
    while (!valid)
    {
        x = rand() % (MAP_WIDTH - 2) + 1;  // 生成随机的x坐标，范围在地图内
        y = rand() % (MAP_HEIGHT - 2) + 1; // 生成随机的y坐标，范围在地图内
        // 检查(x, y)是否与蛇身体或障碍重叠
        valid = 1;
        SnakeNode *curr = snake.head;
        while (curr != NULL) {
            if (x == curr->x && y == curr->y) {
                valid = 0; // 与蛇身体重叠，重新生成
                break;
            }
            curr = curr->next;
        }
        // 跳出后再检查障碍
        if (valid) {
            for (int i = 0; i < OBSTACLE_COUNT; i++) {
                if (x == obstacles[i].x && y == obstacles[i].y) {
                    valid = 0;
                    break;
                }
            }
        }
    }
    food.x = x;              // 设置食物的x坐标
    food.y = y;              // 设置食物的y坐标
    // 随机决定是否为特殊食物（10%概率）
    food.special = (rand() % 10 == 0) ? 1 : 0;
    GotoXY(food.x, food.y);  // 设置光标位置
    printf("%c", food.special ? SPECIAL_FOOD_CHAR : FOOD_CHAR); // 显示食物
}

// 随机布置障碍物，确保不和蛇或互相重叠
void GenerateObstacles()
{
    int i = 0;
    while (i < OBSTACLE_COUNT)
    {
        int x = rand() % (MAP_WIDTH - 2) + 1;
        int y = rand() % (MAP_HEIGHT - 2) + 1;
        // 不允许放在蛇原点附近（蛇尚未初始化时，head可能为空）
        int conflict = 0;
        // 检查与已有障碍重叠
        for (int j = 0; j < i; j++) {
            if (obstacles[j].x == x && obstacles[j].y == y) {
                conflict = 1;
                break;
            }
        }
        if (conflict) continue;
        // 检查是否在蛇身上（如果蛇已初始化）
        SnakeNode *curr = snake.head;
        while (curr != NULL) {
            if (curr->x == x && curr->y == y) {
                conflict = 1;
                break;
            }
            curr = curr->next;
        }
        if (conflict) continue;
        // 位置有效，记录并绘制
        obstacles[i].x = x;
        obstacles[i].y = y;
        GotoXY(x, y);
        printf("%c", OBSTACLE_CHAR);
        i++;
    }
}
int MoveSnake()
{
    fflush(stdout);
    
    // 1. 获取输入（同原逻辑）
    if (_kbhit()) {
        direction = getch();
        switch (direction)
        {
        case UP:
            if (now_Direction != DOWN)     // 如果蛇头向下移动时，用户输入向上移动的方向，则不更新当前方向，防止蛇直接反向移动
                now_Direction = direction; // 更新当前方向
            break;
        case DOWN:
            if (now_Direction != UP)       // 如果蛇头向上移动时，用户输入向下移动的方向，则不更新当前方向，防止蛇直接反向移动
                now_Direction = direction; // 更新当前方向
            break;
        case LEFT:
            if (now_Direction != RIGHT)    // 如果蛇头向右移动时，用户输入向左移动的方向，则不更新当前方向，防止蛇直接反向移动
                now_Direction = direction; // 更新当前方向
            break;
        case RIGHT:
            if (now_Direction != LEFT)     // 如果蛇头向左移动时，用户输入向右移动的方向，则不更新当前方向，防止蛇直接反向移动
                now_Direction = direction; // 更新当前方向
            break;
        }
    }

    // 2. 创建新头节点
    SnakeNode *newHead = (SnakeNode*)malloc(sizeof(SnakeNode));
    newHead->x = snake.head->x;
    newHead->y = snake.head->y;
    
    switch (now_Direction) {
        case UP:    newHead->y--; break;
        case DOWN:  newHead->y++; break;
        case LEFT:  newHead->x--; break;
        case RIGHT: newHead->x++; break;
    }

    // 将旧头改为身体符号
    GotoXY(snake.head->x, snake.head->y);
    printf("%c", SNAKE_BODY_CHAR);

    // 插入新头
    newHead->next = snake.head;
    newHead->prev = NULL;
    snake.head->prev = newHead;
    snake.head = newHead;

    GotoXY(snake.head->x, snake.head->y);
    printf("%c", SNAKE_HEAD_CHAR);

    // 3. 检查吃到食物
    if (snake.head->x == food.x && snake.head->y == food.y) {
        if (food.special) {
            // 特殊食物，增长两节
            snake.length += 2;
            snake.pendingGrowth = 1; // 下一次移动也不去尾部
        } else {
            snake.length++;
        }
        GenerateFood();
        GotoXY(50, 5);
        printf("得分：%d", snake.length - INITIAL_SNAKE_LENGTH);
    } else {
        // 没吃到食物：检查是否仍有挂起增长
        if (snake.pendingGrowth > 0) {
            snake.pendingGrowth--;
        } else {
            SnakeNode *oldTail = snake.tail;
            GotoXY(oldTail->x, oldTail->y);
            printf(" "); // 清除屏幕上的尾巴
            
            snake.tail = oldTail->prev;
            snake.tail->next = NULL;
            free(oldTail); // 释放内存
        }
    }

    // 4. 检查碰撞
    SnakeNode* collisionNode = CheckCollision();
    if (collisionNode == (SnakeNode*)-1) {
        // 墙碰撞，结束
        GotoXY(45, 14);
        printf("Game Over! Score: %d", snake.length - INITIAL_SNAKE_LENGTH);
        GotoXY(45, 16);
        printf("GAME OVER!");
        getch(); // 等待按键
        system("cls");
        return 0;
    } else if (collisionNode != NULL) {
        // 自撞后，截断从collisionNode到tail
        SnakeNode* newTail = collisionNode->prev;  // 保存新的tail
        SnakeNode* curr = collisionNode;
        while (curr != NULL) {
            SnakeNode* next = curr->next;
            GotoXY(curr->x, curr->y);
            printf(" ");
            free(curr);
            snake.length--;
            curr = next;
        }
        // 更新tail
        snake.tail = newTail;
        if (snake.tail) snake.tail->next = NULL;
        // 检查长度
        if (snake.length <= 1) {
            GotoXY(45, 14);
            printf("Game Over! Score: %d", snake.length - INITIAL_SNAKE_LENGTH);
            GotoXY(45, 16);
            printf("GAME OVER!");
            getch(); // 等待按键
            system("cls");
            return 0;
        }
    }

    SpeedControl();
    Sleep(snake.speed);
    return 1;
}
SnakeNode* CheckCollision()
{
    // 碰墙或障碍
    if (snake.head->x <= 0 || snake.head->x >= MAP_WIDTH - 1 || 
        snake.head->y <= 0 || snake.head->y >= MAP_HEIGHT - 1) {
        return (SnakeNode*)-1; // 特殊值表示墙碰撞
    }
    // 障碍
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        if (snake.head->x == obstacles[i].x && snake.head->y == obstacles[i].y) {
            return (SnakeNode*)-1; // 将障碍当作墙处理
        }
    }
    // 碰自己
    SnakeNode *curr = snake.head->next;
    while (curr != NULL) {
        if (snake.head->x == curr->x && snake.head->y == curr->y)
            return curr; // 返回碰撞的节点
        curr = curr->next;
    }
    return NULL; // 没有碰撞
}

// 检查给定坐标是否已被障碍或蛇身占用
int IsPositionBlocked(int x, int y)
{
    // 墙
    if (x <= 0 || x >= MAP_WIDTH - 1 || y <= 0 || y >= MAP_HEIGHT - 1)
        return 1;
    // 障碍
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        if (x == obstacles[i].x && y == obstacles[i].y)
            return 1;
    }
    // 蛇身
    SnakeNode* curr = snake.head;
    while (curr) {
        if (x == curr->x && y == curr->y)
            return 1;
        curr = curr->next;
    }
    return 0;
}

void SpeedControl()
{
    switch (snake.length)
    {
    case 6:
        snake.speed = 200;
        break;
    case 9:
        snake.speed = 180;
        break;
    case 12:
        snake.speed = 160;
        break;
    case 15:
        snake.speed = 140;
        break;
    case 18:
        snake.speed = 120;
        break;
    case 21:
        snake.speed = 100;
        break;
    case 24:
        snake.speed = 80;
        break;
    case 27:
        snake.speed = 60;
        break;
    case 30:

    
        snake.speed = 40;
        break;
    default:
        snake.speed = 200;
        break;
    }
}

//  增加内存释放函数
void FreeSnake()
{
    SnakeNode *curr = snake.head;
    while (curr != NULL) {
        SnakeNode *next = curr->next;
        free(curr);
        curr = next;
    }
    snake.head = snake.tail = NULL;
}