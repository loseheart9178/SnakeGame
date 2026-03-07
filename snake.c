#include "snake.h"

Snake snake;               // 定义全局变量蛇
Food food;                 // 定义全局变量食物
char now_Directio = RIGHT; // 定义全局变量当前方向
char direction = RIGHT;    // 定义全局变量用户输入的方向

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
    SetConsoleCursorInfo(hOut, &cursorInfo);  //asd
         // 设置新的光标信息//
         //test
}