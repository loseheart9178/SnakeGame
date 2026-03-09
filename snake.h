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
#define FOOD_CHAR '$'                             // 定义食物的显示字符
#define SNAKE_HEAD_CHAR '@'                       // 定义蛇头的显示字符
#define SNAKE_BODY_CHAR 'o'                       // 定义蛇身的显示字符
#define MAP_CHAR '|'                              // 定义地图的显示字符`

// 定义游戏相关的结构体
typedef struct SnakeNode
{
    int x;
    int y;
    struct SnakeNode *prev;
    struct SnakeNode *next;
} SnakeNode;

typedef struct
{
    int x;
    int y;
} Food;

typedef struct
{
    SnakeNode *head;        // 指向蛇头的指针
    SnakeNode *tail;        // 指向蛇尾的指针
    int length;             // 蛇的长度
    int speed;              // 蛇的速度
} Snake;


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
SnakeNode* CheckCollision();      // 定义函数用于检查碰撞
void SpeedControl();       // 定义函数用于控制蛇的速度
void FreeSnake();          // 定义函数用于释放蛇的内存
