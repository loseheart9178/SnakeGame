#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

// 定义游戏相关的常量
#define MAP_HEIGHT 20                             // 定义地图高度
#define MAP_WIDTH 40                              // 定义地图宽度
#define UP 'w'                                    // 定义向上移动的按键
#define DOWN 's'                                  // 定义向下移动的按键
#define LEFT 'a'                                  // 定义向左移动的按键
#define RIGHT 'd'                                 // 定义向右移动的按键
#define INITIAL_SNAKE_LENGTH 3                    // 定义初始蛇的长度
#define Max_SNAKE_LENGTH (MAP_HEIGHT * MAP_WIDTH) // 定义蛇的最大长度为地图面积
#define FOOD_CHAR 'O'                             // 定义食物的显示字符
#define SNAKE_CHAR 'X'                            // 定义蛇身的显示字符

// 定义游戏相关的结构体
typedef struct
{
    int x;         // 蛇头的x坐标
    int y;         // 蛇头的y坐标
} Food, SnakeNode; // 定义食物和蛇节点的结构体

typedef struct
{
    SnakeNode body[MAP_HEIGHT * MAP_WIDTH]; // 蛇身体的数组，最大长度为地图面积
    int length;                             // 蛇的长度
    int speed;                              // 蛇的速度
} Snake;                                    // 定义蛇的结构体

// 定义游戏相关的函数
void GotoXY(int x, int y); // 定义函数用于设置光标位置
void HideCursor();         // 定义函数用于隐藏光标
int InitMenu();            // 定义函数用于显示菜单并获取用户选择
void Helper();             // 定义函数用于显示帮助信息
void About();              // 定义函数用于显示关于信息
void InitMap();            // 定义函数用于绘制游戏地图
void InitSnake();          // 定义函数用于初始化蛇
int MoveSnake();           // 定义函数用于移动蛇
void GenerateFood();       // 定义函数用于生成食物
int CheckCollision();      // 定义函数用于检查碰撞
void SpeedControl();       // 定义函数用于控制蛇的速度
