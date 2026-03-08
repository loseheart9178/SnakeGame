#include "snake.h"

Snake snake;                // 定义全局变量蛇
Food food;                  // 定义全局变量食物
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
    printf("3. 碰到墙或自己会游戏结束");
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

    //生成初始食物
    GenerateFood();

    // 显示初始得分
    GotoXY(50, 5);
    printf("得分：0");
}
void InitSnake() // 定义函数用于初始化蛇
{
    snake.length = INITIAL_SNAKE_LENGTH; // 设置蛇的初始长度
    snake.speed = 250;                   // 设置蛇的初始速度
    now_Direction = RIGHT;               // 设置蛇的初始移动方向
    // 设置蛇头位置在地图中心
    snake.body[0].x = MAP_WIDTH / 2 - 1;      // 设置蛇头的x坐标
    snake.body[0].y = MAP_HEIGHT / 2 - 1;     // 设置蛇头的y坐标
    GotoXY(snake.body[0].x, snake.body[0].y); // 设置光标位置`
    printf("%c", SNAKE_HEAD_CHAR);            // 显示蛇头
    // 设置蛇身的位置
    for (int i = 1; i < snake.length; i++)
    {
        snake.body[i].x = snake.body[i - 1].x - 1; // 设置蛇身的x坐标
        snake.body[i].y = snake.body[i - 1].y;     // 设置蛇身的y坐标
        GotoXY(snake.body[i].x, snake.body[i].y);
        printf("%c", SNAKE_BODY_CHAR); // 显示蛇身
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
        // 检查(x, y)是否与蛇身体重叠
        valid = 1;
        for (int i = 0; i < snake.length; i++)
        {
            if (x == snake.body[i].x && y == snake.body[i].y)
            {
                valid = 0; // 与蛇身体重叠，重新生成
                break;
            }
        }
    }
    food.x = x;              // 设置食物的x坐标
    food.y = y;              // 设置食物的y坐标
    GotoXY(food.x, food.y);  // 设置光标位置
    printf("%c", FOOD_CHAR); // 显示食物
}
int MoveSnake()
{
    fflush(stdout);
    SnakeNode temp = snake.body[snake.length - 1]; // 保存蛇尾的位置
    // 移动蛇身
    for (int i = snake.length - 1; i > 0; i--)
        snake.body[i] = snake.body[i - 1];    // 将蛇身的每个节点移动到前一个节点的位置
    GotoXY(snake.body[1].x, snake.body[1].y); // 设置光标位置
    printf("%c", SNAKE_BODY_CHAR);            // 在原蛇头位置显示蛇身
    // 根据键盘输入更新蛇头位置
    if (_kbhit())
    {
        direction = getch(); // 获取用户输入的方向
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
    // 根据当前方向更新蛇头位置
    switch (now_Direction)
    {
    case UP:
        snake.body[0].y--; // 向上移动，y坐标减1
        break;
    case DOWN:
        snake.body[0].y++; // 向下移动，y坐标加1
        break;
    case LEFT:
        snake.body[0].x--; // 向左移动，x坐标减1
        break;
    case RIGHT:
        snake.body[0].x++; // 向右移动，x坐标加1
        break;
    }
    // 显示蛇头
    GotoXY(snake.body[0].x, snake.body[0].y);
    printf("%c", SNAKE_HEAD_CHAR); // 显示蛇头
    // 检查是否吃到食物
    if (snake.body[0].x == food.x && snake.body[0].y == food.y)
    {
        snake.body[snake.length] = temp; // 新增的节点初始化为旧蛇尾位置
        snake.length++;                                          // 增加蛇的长度
        if (snake.length > Max_SNAKE_LENGTH)                     // 如果蛇的长度超过最大长度，则游戏结束
            return 0;                                            // 返回0表示游戏结束
        GenerateFood();                                          // 生成新的食物
        GotoXY(50, 5);                                           // 设置光标位置
        printf("得分：%d", snake.length - INITIAL_SNAKE_LENGTH); // 显示当前得分，得分等于蛇的长度减去初始长度
    }
    else
    {
        // 清除蛇尾
        GotoXY(temp.x, temp.y);
        printf(" "); // 在原蛇尾位置显示空格，清除蛇尾
    }
    // 检查碰撞
    if (!CheckCollision())
    {
        system("cls");                              // 可以保留或去掉
        GotoXY(45, 14);
        printf("你的得分: %d", snake.length - INITIAL_SNAKE_LENGTH);
        GotoXY(45, 16);
        printf("GAME OVER!");
        GotoXY(45, 18);
        printf("按任意键返回主菜单");
        getch();                                    // 等待玩家
        system("cls");                              // 再清屏
        return 0;
    }
    // 控制蛇的速度
    SpeedControl();
    Sleep(snake.speed); // 根据蛇的速度暂停一段时间，控制蛇的移动速度
    return 1;          // 返回1表示游戏继续
}
int CheckCollision()
{
    // 检查蛇头是否碰到墙壁
    if (snake.body[0].x <= 0 || snake.body[0].x >= MAP_WIDTH - 1 || snake.body[0].y <= 0 || snake.body[0].y >= MAP_HEIGHT - 1)
        return 0; // 返回0表示没有发生碰撞
    // 检查蛇头是否碰到自己
    for (int i = 1; i < snake.length; i++)
    {
        if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
            return 0; // 返回0表示发生碰撞
    }
    return 1; // 返回1表示没有发生碰撞
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