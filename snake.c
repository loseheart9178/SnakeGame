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
    printf("任意键退出游戏");       // 显示菜单选项5
    HideCursor();                   // 隐藏光标
    printf("请输入您的选择：");
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